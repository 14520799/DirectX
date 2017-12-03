#include "Scene1.h"
#include "../GameDefines/GameDefine.h"

Scene1::Scene1()
{
	LoadContent();
}

void Scene1::LoadContent()
{
	//set mau backcolor cho scene o day la mau xanh
	mBackColor = 0x54acd2;

	mMap = new GameMap("Resources/Scene_1.tmx");

	mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	mCamera->SetPosition(GameGlobal::GetWidth() / 2,
		mMap->GetHeight() - mCamera->GetHeight());

	mMap->SetCamera(mCamera);

	mPlayer = new Player();
	mPlayer->mOriginPosition = D3DXVECTOR3(GameGlobal::GetWidth() / 4, 1035, 0);
	mPlayer->SetPosition(mPlayer->mOriginPosition);
	mPlayer->SetCamera(mCamera);
	mPlayer->SetMap(mMap);

	mMap->SetPlayer(mPlayer);
}

void Scene1::Update(float dt)
{
	checkCollision();

	mMap->Update(dt);

	mPlayer->HandleKeyboard(keys);

	mPlayer->Update(dt);

	CheckCameraAndWorldMap();
}

void Scene1::Draw()
{
	mMap->Draw();
}

void Scene1::OnKeyDown(int keyCode)
{
	keys[keyCode] = true;

	mPlayer->OnKeyPressed(keyCode);
}

void Scene1::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;

	mPlayer->OnKeyUp(keyCode);
}

void Scene1::OnMouseDown(float x, float y)
{

}

void Scene1::CheckCameraAndWorldMap()
{
	if (mPlayer->onKeyUpPressing)
		mCamera->SetPosition(mPlayer->GetPosition() + D3DXVECTOR3(0, -250, 0));
	else
		mCamera->SetPosition(mPlayer->GetPosition());

	if (mCamera->GetBound().left < 0)
	{
		//vi position cua camera ma chinh giua camera
		//luc nay o vi tri goc ben trai cua the gioi thuc
		mCamera->SetPosition(mCamera->GetWidth() / 2, mCamera->GetPosition().y);
	}

	if (mCamera->GetBound().right > mMap->GetWidth())
	{
		//luc nay cham goc ben phai cua the gioi thuc
		mCamera->SetPosition(mMap->GetWidth() - mCamera->GetWidth() / 2,
			mCamera->GetPosition().y);
	}

	if (mCamera->GetBound().top < 0)
	{
		//luc nay cham goc tren the gioi thuc
		mCamera->SetPosition(mCamera->GetPosition().x, mCamera->GetHeight() / 2);
	}

	if (mCamera->GetBound().bottom > mMap->GetHeight())
	{
		//luc nay cham day cua the gioi thuc
		mCamera->SetPosition(mCamera->GetPosition().x,
			mMap->GetHeight() - mCamera->GetHeight() / 2);
	}
}

void Scene1::checkCollision()
{
	/*su dung de kiem tra xem khi nao mario khong dung tren 1 object hoac
	dung qua sat mep trai hoac phai cua object do thi se chuyen state la falling*/
	int widthBottomPlayer = 0;
	int WidthBottomOroku = 0;

	vector<Entity*> listCollisionPlayer;
	vector<Entity*> listCollisionOrokus;
	vector<Entity*> listCollisionWeapon;
	vector<Entity*> listCollisionOrokusSupport;
	vector<Entity*> listCollisionApple;
#pragma region --PLAYER--
	mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionPlayer, mPlayer);

	for (size_t i = 0; i < listCollisionPlayer.size(); i++)
	{
		Entity::CollisionReturn r = GameCollision::RecteAndRect(mPlayer->GetBound(), listCollisionPlayer.at(i)->GetBound());

		if (r.IsCollided)
		{
			//lay phia va cham cua Entity so voi Player
			Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(mPlayer, r);

			//lay phia va cham cua Player so voi Entity
			Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollisionPlayer.at(i), r);

			//goi den ham xu ly collision cua Player va Entity
			mPlayer->OnCollision(listCollisionPlayer.at(i), r, sidePlayer);
			listCollisionPlayer.at(i)->OnCollision(mPlayer, r, sideImpactor);

#pragma region Xu ly di xuong cau thang
			//xac dinh player co dang va cham voi cau thang hay khong
			if (listCollisionPlayer.at(i)->Tag == Entity::EntityTypes::Stairs || listCollisionPlayer.at(i)->Tag == Entity::EntityTypes::UpStairs ||
				listCollisionPlayer.at(i)->Tag == Entity::EntityTypes::CenterStairs || listCollisionPlayer.at(i)->Tag == Entity::EntityTypes::DownStairs)
			{
				mPlayer->collisionStairs = true;
				mPlayer->allowFalling = false;
			}
			//xac dinh player co dang di den cuoi cau thang de roi xuong hay chua
			else if (listCollisionPlayer.at(i)->Tag == Entity::EntityTypes::FallControl)
			{
				mPlayer->collisionStairs = false;
				mPlayer->allowFalling = true;
				break;
			}
			//xu ly khi cham quai vat tren cau thang
			if (listCollisionPlayer.at(i)->Tag == Entity::EntityTypes::Oroku && mPlayer->collisionStairs && !mPlayer->allowFalling)
			{
				mPlayer->OnNoCollisionWithBottom();
			}

#pragma endregion

			//kiem tra neu va cham voi phia duoi cua Player 
			if ((sidePlayer == Entity::Bottom || sidePlayer == Entity::BottomLeft
				|| sidePlayer == Entity::BottomRight) && listCollisionPlayer.at(i)->Id != Entity::EntityId::CivilianCircus)
			{
				//kiem cha do dai ma player tiep xuc phia duoi day
				int bot = r.RegionCollision.right - r.RegionCollision.left;

				if (bot > widthBottomPlayer)
				{
					widthBottomPlayer = bot;
				}
			}

			if (mPlayer->collisionItem)
			{
				MapObject* item = (MapObject*)listCollisionPlayer.at(i);
				mMap->RemoveMapObject(item);
				mMap->GetQuadTree()->removeEntity(item); //clear Item khoi QuadTree
				mPlayer->collisionItem = false;
				break;
			}
			if (mPlayer->collisionWithOroku)
			{
				Oroku *oroku = (Oroku*)listCollisionPlayer.at(i);
				oroku->bloodOfEntity--;
				oroku->allowImunity = true;
				mPlayer->collisionWithOroku = false;
				if (oroku->bloodOfEntity <= 0)
				{
					oroku->SetPosition(oroku->mOriginPosition);
					mMap->RemoveOroku(oroku);//xoa oroku khoi listoroku trong map
					mMap->GetQuadTree()->removeEntity(oroku); //xoa oroku ra khoi quadtree
					if (oroku->weapon != nullptr)
					{
						delete oroku->weapon;
						oroku->weapon = nullptr;
					}
					delete oroku;
					oroku = nullptr;
					break;
				}
			}
		}
	}

	//Neu player dung ngoai mep thi luc nay cho player rot xuong duoi dat    
	if (widthBottomPlayer < Define::PLAYER_BOTTOM_RANGE_FALLING)
		mPlayer->OnNoCollisionWithBottom();
#pragma endregion

#pragma region --OROKU--
	for (auto child : mMap->GetListOroku())
	{
		listCollisionOrokus.clear();
		mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionOrokus, child);
		for (size_t i = 0; i < listCollisionOrokus.size(); i++)
		{
			if (listCollisionOrokus.at(i)->Id == Entity::EntityId::Camel)
				break;

			Entity::CollisionReturn r = GameCollision::RecteAndRect(child->GetBound(), listCollisionOrokus.at(i)->GetBound());
			if (r.IsCollided)
			{
				Entity::SideCollisions sideOroku = GameCollision::getSideCollision(child, r);
				Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollisionOrokus.at(i), r);

				//goi den ham xu ly collision cua Oroku va Entity				
				child->OnCollision(listCollisionOrokus.at(i), r, sideOroku);
				listCollisionOrokus.at(i)->OnCollision(child, r, sideImpactor);
			}
		}

		Entity::CollisionReturn R = GameCollision::RecteAndRect(child->GetBound(), mPlayer->GetBound());
		if (R.IsCollided)
		{
			//lay phia va cham cua Entity so voi StrongOroku
			Entity::SideCollisions sideOroku = GameCollision::getSideCollision(child, R);

			//lay phia va cham cua StrongOroku so voi Entity
			Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(mPlayer, R);

			//goi den ham xu ly collision cua StrongOroku va Entity
			child->OnCollision(mPlayer, R, sideOroku);
			mPlayer->OnCollision(child, R, sideImpactor);

			if (child->collisionWithPlayer)
			{
				mPlayer->bloodOfEntity--;
				child->collisionWithPlayer = false;
			}
		}

		if (child->weapon != nullptr)
		{
			listCollisionWeapon.clear();
			mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionWeapon, child->weapon);
			for (size_t i = 0; i < listCollisionWeapon.size(); i++)
			{
				Entity::CollisionReturn r = GameCollision::RecteAndRect(child->weapon->GetBound(), listCollisionWeapon.at(i)->GetBound());
				if (r.IsCollided)
				{
					//lay phia va cham cua Entity so voi StrongOroku
					Entity::SideCollisions sideWeapon = GameCollision::getSideCollision(child->weapon, r);

					//lay phia va cham cua StrongOroku so voi Entity
					Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollisionWeapon.at(i), r);

					//goi den ham xu ly collision cua StrongOroku va Entity
					child->weapon->OnCollision(listCollisionWeapon.at(i), r, sideWeapon);
					listCollisionWeapon.at(i)->OnCollision(child->weapon, r, sideImpactor);
				}
			}

			Entity::CollisionReturn R = GameCollision::RecteAndRect(child->weapon->GetBound(), mPlayer->GetBound());
			if (R.IsCollided)
			{
				//lay phia va cham cua Entity so voi StrongOroku
				Entity::SideCollisions sideWeapon = GameCollision::getSideCollision(child->weapon, R);

				//lay phia va cham cua StrongOroku so voi Entity
				Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(mPlayer, R);

				//goi den ham xu ly collision cua StrongOroku va Entity
				child->weapon->OnCollision(mPlayer, R, sideWeapon);
				mPlayer->OnCollision(child->weapon, R, sideImpactor);
			}
		}
	}
#pragma endregion

#pragma region --OROKU SUPPORT--
	for (auto child : mMap->GetListOrokuSupport())
	{
		listCollisionOrokusSupport.clear();
		mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionOrokusSupport, child);

		for (size_t i = 0; i < listCollisionOrokusSupport.size(); i++)
		{
			Entity::CollisionReturn r = GameCollision::RecteAndRect(child->GetBound(),
				listCollisionOrokusSupport.at(i)->GetBound());

			if (r.IsCollided)
			{
				Entity::SideCollisions sideOroku = GameCollision::getSideCollision(child, r);
				Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollisionOrokusSupport.at(i), r);

				//goi den ham xu ly collision cua Oroku va Entity		
				child->OnCollision(listCollisionOrokusSupport.at(i), r, sideOroku);
				listCollisionOrokusSupport.at(i)->OnCollision(child, r, sideImpactor);

				if (child->collisionWithOroku)
				{
					Oroku *oroku = (Oroku*)listCollisionOrokusSupport.at(i);
					oroku->SetPosition(oroku->mOriginPosition);
					mMap->RemoveOroku(oroku);//xoa oroku khoi listoroku trong map
					mMap->GetQuadTree()->removeEntity(oroku); //xoa oroku ra khoi quadtree
					if (oroku->weapon != nullptr)
					{
						delete oroku->weapon;
						oroku->weapon = nullptr;
					}
					delete oroku;
					oroku = nullptr;
					child->collisionWithOroku = false;
					break;
				}
			}
		}
	}

#pragma endregion

#pragma region --APPLE--
	for (auto child : mPlayer->GetListAppleFly())
	{
		if (child != nullptr)
		{
			listCollisionApple.clear();
			mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionApple, child);
			for (size_t i = 0; i < listCollisionApple.size(); i++)
			{
				Entity::CollisionReturn r = GameCollision::RecteAndRect(child->GetBound(),
					listCollisionApple.at(i)->GetBound());

				if (r.IsCollided)
				{
					Entity::SideCollisions sideApple = GameCollision::getSideCollision(child, r);
					Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollisionApple.at(i), r);

					child->OnCollision(listCollisionApple.at(i), r, sideApple);
					listCollisionApple.at(i)->OnCollision(child, r, sideImpactor);
				}

				if (child->collisionWithOroku)
				{
					Oroku *oroku = (Oroku*)listCollisionApple.at(i);
					oroku->bloodOfEntity--;
					oroku->allowImunity = true;
					if (oroku->bloodOfEntity <= 0)
					{
						oroku->SetPosition(oroku->mOriginPosition);
						mMap->RemoveOroku(oroku);//xoa oroku khoi listoroku trong map
						mMap->GetQuadTree()->removeEntity(oroku); //xoa oroku ra khoi quadtree
						if (oroku->weapon != nullptr)
						{
							delete oroku->weapon;
							oroku->weapon = nullptr;
						}
						delete oroku;
						oroku = nullptr;
						break;
					}
					return;
				}
			}
		}
	}
#pragma endregion
}