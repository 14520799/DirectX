#include "Scene1.h"
#include "CompleteScene.h"
#include "../GameObjects/MapObjects/Weapons/AppleWeapon.h"
#include "../GameControllers/SceneManager.h"
#include "../GameDefines/GameDefine.h"

Scene1::Scene1()
{
	LoadContent();
}

Scene1::~Scene1()
{
	delete mMap;

	delete mCamera;
}

void Scene1::LoadContent()
{
	//set mau backcolor cho scene o day la mau xanh
	mBackColor = D3DCOLOR_XRGB(0, 0, 0);

	//Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/AGMusicBossBattle.wav", "AGMusicBossBattle");
	//Sound::getInstance()->play("AGMusicBossBattle", true, 0);

	mMap = new GameMap("Resources/Scene_1/Scene_1.tmx");
	mMap->LoadMapCloudsScene1("Resources/Scene_1/CloudsPosition.txt");
	mMap->LoadMapItems("Resources/Scene_1/ItemsPosition.txt");
	mMap->LoadMapOrokus("Resources/Scene_1/OrokusPosition.txt");

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

	for (size_t i = 0; i < 10; i++)
	{
		MapObject *apple = new AppleWeapon();
		mPlayer->mListApplePlayer.push_back(apple);
	}
}

void Scene1::Update(float dt)
{
	if (mPlayer->allowTranslateScene)
	{
		SceneManager::GetInstance()->ReplaceScene(new CompleteScene(mPlayer, 1));
		return;
	}

	if (mPlayer->mCurrentState == PlayerState::Revival || mPlayer->mCurrentState == PlayerState::Death ||
		mPlayer->mCurrentState == PlayerState::GameOver)
	{
		mPlayer->Update(dt);
	}
	else
	{
		checkCollision();

		mMap->Update(dt);

		mPlayer->HandleKeyboard(keys);

		mPlayer->Update(dt);

		CheckCameraAndWorldMap();
	}
}

void Scene1::Draw()
{
	if (mPlayer->mCurrentState == PlayerState::Revival || mPlayer->mCurrentState == PlayerState::Death ||
		mPlayer->mCurrentState == PlayerState::GameOver)
		mPlayer->Draw();
	else
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
	else if (mPlayer->onKeyDownPressing)
		mCamera->SetPosition(mPlayer->GetPosition() + D3DXVECTOR3(0, 250, 0));
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
	vector<Entity*> listCollisionPlayerSupport;
	vector<Entity*> listCollisionApple;

	mCameraExpand.left = mCamera->GetBound().left - 100;
	mCameraExpand.right = mCamera->GetBound().right + 100;
	mCameraExpand.top = mCamera->GetBound().top - 50;
	mCameraExpand.bottom = mCamera->GetBound().bottom;

#pragma region --PLAYER--
	mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionPlayer, mPlayer);

	for (size_t i = 0; i < listCollisionPlayer.size(); i++)
	{
		if (listCollisionPlayer.at(i)->Id == Entity::EntityId::LampAttack)
			continue;

		if (listCollisionPlayer.at(i)->Tag == Entity::EntityTypes::Item &&
			!GameCollision::RecteAndRect(listCollisionPlayer.at(i)->GetBound(), mCameraExpand).IsCollided)
			continue;

		//mCollidable.push_back(listCollisionPlayer.at(i));

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
		}
	}

	//Neu player dung ngoai mep thi luc nay cho player rot xuong duoi dat    
	if (widthBottomPlayer < Define::PLAYER_BOTTOM_RANGE_FALLING)
		mPlayer->OnNoCollisionWithBottom();
#pragma endregion

#pragma region --PLAYER SUPPORT--
	for (auto child : mMap->GetListPlayerSupport())
	{
		if (GameCollision::RecteAndRect(child->GetBound(), mCameraExpand).IsCollided)
		{
			if (child->Id == Entity::EntityId::Camel)
			{
				Entity::CollisionReturn r = GameCollision::RecteAndRect(child->GetBound(), mPlayer->GetBound());
				if (r.IsCollided)
				{
					Entity::SideCollisions sideOroku = GameCollision::getSideCollision(child, r);

					Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(mPlayer, r);

					//goi den ham xu ly collision cua StrongOroku va Entity
					child->OnCollision(mPlayer, r, sideOroku);
					mPlayer->OnCollision(child, r, sideImpactor);
				}
			}
		}

		for (auto childO : mMap->GetListOroku())
		{
			if (!GameCollision::RecteAndRect(childO->GetBound(), mCameraExpand).IsCollided ||
				childO->Id == Entity::EntityId::Camel)
				continue;

			Entity::CollisionReturn R = GameCollision::RecteAndRect(child->GetBound(), childO->GetBound());
			if (R.IsCollided)
			{
				//lay phia va cham cua Entity so voi StrongOroku
				Entity::SideCollisions sideOroku = GameCollision::getSideCollision(child, R);

				//lay phia va cham cua StrongOroku so voi Entity
				Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(childO, R);

				//goi den ham xu ly collision cua StrongOroku va Entity
				child->OnCollision(childO, R, sideOroku);
				childO->OnCollision(child, R, sideImpactor);

				if (child->collisionWithOroku)
				{
					childO->bloodOfEntity--;
					childO->allowImunity = true;
					child->collisionWithOroku = false;
					if (childO->bloodOfEntity <= 0)
					{
						mPlayer->allowOrokuEffect = true;
						mPlayer->mOriginPositionItem = childO->GetPosition();
						mMap->RemoveOroku(childO);//xoa oroku khoi listoroku trong map
						if (childO->weapon != nullptr)
						{
							delete childO->weapon;
							childO->weapon = nullptr;
						}
						delete childO;
						childO = nullptr;
						break;
					}
				}
			}
		}
	}

#pragma endregion

#pragma region --APPLE--
	for (auto child : mPlayer->GetListAppleFly())
	{
		listCollisionApple.clear();
		mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionApple, child);
		for (size_t i = 0; i < listCollisionApple.size(); i++)
		{
			if (listCollisionApple.at(i)->Tag == Entity::EntityTypes::Item ||
				listCollisionApple.at(i)->Tag == Entity::EntityTypes::FallControl ||
				listCollisionApple.at(i)->Tag == Entity::EntityTypes::OrokuControl)
				continue;

			Entity::CollisionReturn r = GameCollision::RecteAndRect(child->GetBound(), listCollisionApple.at(i)->GetBound());
			if (r.IsCollided)
			{
				Entity::SideCollisions sideApple = GameCollision::getSideCollision(child, r);
				Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollisionApple.at(i), r);

				child->OnCollision(listCollisionApple.at(i), r, sideApple);
				listCollisionApple.at(i)->OnCollision(child, r, sideImpactor);
			}
		}
	}
#pragma endregion

#pragma region --OROKU--
	for (auto child : mMap->GetListOroku())
	{
		if (child->Id == Entity::EntityId::Camel)
			continue;

		if (child->Id == Entity::EntityId::CivilianCircus || child->Id == Entity::EntityId::CivilianWindow)
		{
			if (GameCollision::RecteAndRect(child->GetBound(), mCameraExpand).IsCollided)
			{
				//oroku vs apple
				for (auto childA : mPlayer->GetListAppleFly())
				{
					Entity::CollisionReturn R = GameCollision::RecteAndRect(child->GetBound(), childA->GetBound());
					if (R.IsCollided)
					{
						//lay phia va cham cua Entity so voi StrongOroku
						Entity::SideCollisions sideOroku = GameCollision::getSideCollision(child, R);

						//lay phia va cham cua StrongOroku so voi Entity
						Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(childA, R);

						//goi den ham xu ly collision cua StrongOroku va Entity
						child->OnCollision(childA, R, sideOroku);
						childA->OnCollision(child, R, sideImpactor);

						if (childA->collisionWithOroku)
						{
							child->bloodOfEntity--;
							child->collisionAppleWeapon = true;
							if (child->bloodOfEntity <= 0)
							{
								Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/StartGun.wav", "StartGun");
								Sound::getInstance()->play("StartGun", false, 1);
								mPlayer->mScorePlayer += 30;
								mPlayer->allowOrokuEffect = true;
								mPlayer->mOriginPositionItem = child->GetPosition();
								mMap->RemoveOroku(child);//xoa oroku khoi listoroku trong map
								if (child->weapon != nullptr)
								{
									delete child->weapon;
									child->weapon = nullptr;
								}
								delete child;
								child = nullptr;
								return;
							}
						}
					}
				}

				//oroku vs player
				Entity::CollisionReturn R = GameCollision::RecteAndRect(child->GetBound(), mPlayer->GetBound());
				if (R.IsCollided)
				{
					//lay phia va cham cua Entity so voi Oroku
					Entity::SideCollisions sideOroku = GameCollision::getSideCollision(child, R);

					//lay phia va cham cua Oroku so voi Entity
					Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(mPlayer, R);

					//goi den ham xu ly collision cua Oroku va Entity
					child->OnCollision(mPlayer, R, sideOroku);
					mPlayer->OnCollision(child, R, sideImpactor);

					if (mPlayer->collisionWithOroku)
					{
						child->bloodOfEntity--;
						child->allowImunity = true;
						mPlayer->collisionWithOroku = false;
						if (child->bloodOfEntity <= 0)
						{
							Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/StartGun.wav", "StartGun");
							Sound::getInstance()->play("StartGun", false, 1);
							mPlayer->mScorePlayer += 30;
							mPlayer->allowOrokuEffect = true;
							mPlayer->mOriginPositionItem = child->GetPosition();
							mMap->RemoveOroku(child);//xoa oroku khoi listoroku trong map
							if (child->weapon != nullptr)
							{
								delete child->weapon;
								child->weapon = nullptr;
							}
							delete child;
							child = nullptr;
							break;
						}
					}
				}
			}
			
			//vu khi cua oroku
			if (child->Id == Entity::EntityId::CivilianCircus)
			{
				if (child->weapon != nullptr)
				{
					listCollisionWeapon.clear();
					mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionWeapon, child->weapon);
					for (size_t i = 0; i < listCollisionWeapon.size(); i++)
					{
						if (listCollisionWeapon.at(i)->Id == Entity::EntityId::Camel ||
							listCollisionWeapon.at(i)->Tag == Entity::EntityTypes::Item ||
							listCollisionWeapon.at(i)->Tag == Entity::EntityTypes::FallControl ||
							listCollisionWeapon.at(i)->Tag == Entity::EntityTypes::OrokuControl)
							continue;

						Entity::CollisionReturn r = GameCollision::RecteAndRect(child->weapon->GetBound(), listCollisionWeapon.at(i)->GetBound());
						if (r.IsCollided)
						{
							Entity::SideCollisions sideOroku = GameCollision::getSideCollision(child->weapon, r);
							Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollisionWeapon.at(i), r);

							//goi den ham xu ly collision cua Oroku va Entity				
							child->weapon->OnCollision(listCollisionWeapon.at(i), r, sideOroku);
							listCollisionWeapon.at(i)->OnCollision(child->weapon, r, sideImpactor);
						}
					}

					Entity::CollisionReturn R = GameCollision::RecteAndRect(child->weapon->GetBound(), mPlayer->GetBound());
					if (R.IsCollided)
					{
						//lay phia va cham cua Weapon so voi Player 
						Entity::SideCollisions sideWeapon = GameCollision::getSideCollision(child->weapon, R);

						//lay phia va cham cua Player so voi Weapon
						Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(mPlayer, R);

						//goi den ham xu ly collision cua Weapon va Player
						child->weapon->OnCollision(mPlayer, R, sideWeapon);
						mPlayer->OnCollision(child->weapon, R, sideImpactor);
					}
				}
			}
			else if (child->Id == Entity::EntityId::CivilianWindow)
			{
				if (child->weapon != nullptr)
				{
					if (GameCollision::RecteAndRect(child->weapon->GetBound(), mCameraExpand).IsCollided)
					{
						listCollisionWeapon.clear();
						mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionWeapon, child->weapon);
						for (size_t i = 0; i < listCollisionWeapon.size(); i++)
						{
							if (listCollisionWeapon.at(i)->Tag != Entity::EntityTypes::Ground)
								continue;

							Entity::CollisionReturn r = GameCollision::RecteAndRect(child->weapon->GetBound(), listCollisionWeapon.at(i)->GetBound());
							if (r.IsCollided)
							{
								Entity::SideCollisions sideOroku = GameCollision::getSideCollision(child->weapon, r);
								Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollisionWeapon.at(i), r);

								//goi den ham xu ly collision cua Oroku va Entity				
								child->weapon->OnCollision(listCollisionWeapon.at(i), r, sideOroku);
								listCollisionWeapon.at(i)->OnCollision(child->weapon, r, sideImpactor);
							}
						}
					}

					Entity::CollisionReturn R = GameCollision::RecteAndRect(child->weapon->GetBound(), mPlayer->GetBound());
					if (R.IsCollided)
					{
						//lay phia va cham cua Weapon so voi Player 
						Entity::SideCollisions sideWeapon = GameCollision::getSideCollision(child->weapon, R);

						//lay phia va cham cua Player so voi Weapon
						Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(mPlayer, R);

						//goi den ham xu ly collision cua Weapon va Player
						child->weapon->OnCollision(mPlayer, R, sideWeapon);
						mPlayer->OnCollision(child->weapon, R, sideImpactor);
					}
				}
			}
		}
		else
		{
			if (GameCollision::RecteAndRect(child->GetBound(), mCameraExpand).IsCollided)
			{
				//oroku vs apple
				for (auto childA : mPlayer->GetListAppleFly())
				{
					Entity::CollisionReturn R = GameCollision::RecteAndRect(child->GetBound(), childA->GetBound());
					if (R.IsCollided)
					{
						//lay phia va cham cua Entity so voi Oroku
						Entity::SideCollisions sideOroku = GameCollision::getSideCollision(child, R);

						//lay phia va cham cua Oroku so voi Entity
						Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(childA, R);

						//goi den ham xu ly collision cua StrongOroku va Entity
						childA->OnCollision(child, R, sideImpactor);

						if (childA->collisionWithOroku)
						{
							child->bloodOfEntity--;
							child->collisionAppleWeapon = true;
							if (child->bloodOfEntity <= 0)
							{
								Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/StartGun.wav", "StartGun");
								Sound::getInstance()->play("StartGun", false, 1);
								mPlayer->mScorePlayer += 20;
								mPlayer->allowOrokuEffect = true;
								mPlayer->mOriginPositionItem = child->GetPosition();
								mMap->RemoveOroku(child);//xoa oroku khoi listoroku trong map
								if (child->weapon != nullptr)
								{
									delete child->weapon;
									child->weapon = nullptr;
								}
								delete child;
								child = nullptr;
								return;
							}
							if (child->Id == Entity::EntityId::Guard)
							{
								Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/Guard'sPants.wav", "Guard'sPants");
								Sound::getInstance()->play("Guard'sPants", false, 1);
							}
						}

						child->OnCollision(childA, R, sideOroku);
					}
				}

				//oroku vs player
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
					if (mPlayer->collisionWithOroku)
					{
						child->bloodOfEntity--;
						child->allowImunity = true;
						mPlayer->collisionWithOroku = false;
						if (child->bloodOfEntity <= 0)
						{
							Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/StartGun.wav", "StartGun");
							Sound::getInstance()->play("StartGun", false, 1);
							mPlayer->mScorePlayer += 20;
							mPlayer->allowOrokuEffect = true;
							mPlayer->mOriginPositionItem = child->GetPosition();
							mMap->RemoveOroku(child);//xoa oroku khoi listoroku trong map
							if (child->weapon != nullptr)
							{
								delete child->weapon;
								child->weapon = nullptr;
							}
							delete child;
							child = nullptr;
							break;
						}
						Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/Guard'sPants.wav", "Guard'sPants");
						Sound::getInstance()->play("Guard'sPants", false, 1);
					}
				}

				//oroku voi object
				listCollisionOrokus.clear();
				mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionOrokus, child);
				for (size_t i = 0; i < listCollisionOrokus.size(); i++)
				{
					if (listCollisionOrokus.at(i)->Tag == Entity::EntityTypes::OrokuControl ||
						listCollisionOrokus.at(i)->Tag == Entity::EntityTypes::Fire ||
						listCollisionOrokus.at(i)->Tag == Entity::EntityTypes::FireControl)
					{
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
				}
			}

			//vu khi cua oroku
			if (child->weapon != nullptr)
			{
				if (GameCollision::RecteAndRect(child->weapon->GetBound(), mCameraExpand).IsCollided)
				{
					listCollisionWeapon.clear();
					mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionWeapon, child->weapon);
					for (size_t i = 0; i < listCollisionWeapon.size(); i++)
					{
						if (listCollisionWeapon.at(i)->Id == Entity::EntityId::Camel ||
							listCollisionWeapon.at(i)->Tag == Entity::EntityTypes::Item ||
							listCollisionWeapon.at(i)->Tag == Entity::EntityTypes::FallControl ||
							listCollisionWeapon.at(i)->Tag == Entity::EntityTypes::OrokuControl)
							continue;

						Entity::CollisionReturn r = GameCollision::RecteAndRect(child->weapon->GetBound(), listCollisionWeapon.at(i)->GetBound());
						if (r.IsCollided)
						{
							Entity::SideCollisions sideOroku = GameCollision::getSideCollision(child->weapon, r);
							Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollisionWeapon.at(i), r);

							//goi den ham xu ly collision cua Oroku va Entity				
							child->weapon->OnCollision(listCollisionWeapon.at(i), r, sideOroku);
							listCollisionWeapon.at(i)->OnCollision(child->weapon, r, sideImpactor);
						}
					}
				}

				Entity::CollisionReturn R = GameCollision::RecteAndRect(child->weapon->GetBound(), mPlayer->GetBound());
				if (R.IsCollided)
				{
					//lay phia va cham cua Weapon so voi Player 
					Entity::SideCollisions sideWeapon = GameCollision::getSideCollision(child->weapon, R);

					//lay phia va cham cua Player so voi Weapon
					Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(mPlayer, R);

					//goi den ham xu ly collision cua Weapon va Player
					child->weapon->OnCollision(mPlayer, R, sideWeapon);
					mPlayer->OnCollision(child->weapon, R, sideImpactor);
				}
			}
		}

		if (GameCollision::RecteAndRect(child->GetBound(), mCameraExpand).IsCollided)
		{
			if (child->weapon != nullptr)
			{
				if (child->weapon->Tag == Entity::EntityTypes::Sword && child->weapon->weaponCollided)
				{
					Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/SwordChing.wav", "SwordChing");
					Sound::getInstance()->play("SwordChing", false, 1);
				}
			}
		}
	}
#pragma endregion
}