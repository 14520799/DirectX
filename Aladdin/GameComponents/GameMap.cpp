#include "GameMap.h"
#include "../GameDefines/GameDefine.h"
#include "../GameObjects/MapObjects/AppleItem.h"
#include "../GameObjects/Orokus/Guards/ThinGuard.h"
#include "../GameObjects/Orokus/Guards/FatGuard.h"
#include "../GameObjects/Orokus/Guards/StrongGuard.h"

GameMap::GameMap(char* filePath)
{
	mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	LoadMap(filePath);
}

GameMap::~GameMap()
{
	delete mMap;

	for (size_t i = 0; i < mListItems.size(); i++)
	{
		if (mListItems[i])
			delete mListItems[i];
	}
	mListItems.clear();

	for (size_t i = 0; i < mListOrokus.size(); i++)
	{
		if (mListOrokus[i])
			delete mListOrokus[i];
	}
	mListOrokus.clear();

	for (size_t i = 0; i < mListTileset.size(); i++)
	{
		if (mListTileset[i])
			delete mListTileset[i];
	}
	mListTileset.clear();

	delete mQuadTree;
}

void GameMap::LoadMap(char* filePath)
{
	mMap = new Tmx::Map();
	mMap->ParseFile(filePath);

	mQuadTree = new QuadTree(1, this->GetWorldMapBound());

	for (size_t i = 0; i < mMap->GetNumTilesets(); i++)
	{
		const Tmx::Tileset *tileset = mMap->GetTileset(i);

		Sprite *sprite = new Sprite(tileset->GetImage()->GetSource().c_str());
		mListTileset.insert(pair<int, Sprite*>(i, sprite));
	}

	//tao oject cho map
#pragma region -OBJECTGROUP, STATIC OBJECT-

	for (size_t i = 0; i < mMap->GetNumObjectGroups(); i++)
	{
		const Tmx::ObjectGroup *objectGroup = mMap->GetObjectGroup(i);

		for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
		{
			//lay object group chu khong phai layer
			//object group se chua nhung body
			Tmx::Object *object = objectGroup->GetObjects().at(j);

			if (!object->IsVisible())
				continue;

			Entity *entity = new Entity();
			entity->SetPosition(object->GetX() + object->GetWidth() / 2,
				object->GetY() + object->GetHeight() / 2);
			entity->SetWidth(object->GetWidth());
			entity->SetHeight(object->GetHeight());

			if (object->GetName() == "VerticalRope")
			{
				entity->Tag = Entity::EntityTypes::VerticalRope;
			}
			else if (object->GetName() == "HorizontalRope")
			{
				entity->Tag = Entity::EntityTypes::HorizontalRope;
			}
			else if (object->GetName() == "Fire")
			{
				entity->Tag = Entity::EntityTypes::Fire;
			}
			else if (object->GetName() == "Stairs")
			{
				entity->Tag = Entity::EntityTypes::Stairs;
			}
			else if (object->GetName() == "UpStairs")
			{
				entity->Tag = Entity::EntityTypes::UpStairs;
				mListUpStairs.push_back(entity);
				continue;
			}
			else if (object->GetName() == "UpStairsControl")
			{
				entity->Tag = Entity::EntityTypes::UpStairsControl;
			}
			else if (object->GetName() == "CenterStairs")
			{
				entity->Tag = Entity::EntityTypes::CenterStairs;
				mListDownStairs.push_back(entity);
				continue;
			}
			else if (object->GetName() == "DownStairs")
			{
				entity->Tag = Entity::EntityTypes::DownStairs;
				mListDownStairs.push_back(entity);
				continue;
			}
			else if (object->GetName() == "DownStairsControl")
			{
				entity->Tag = Entity::EntityTypes::DownStairsControl;
			}
			else if (object->GetName() == "GroundControl")
			{
				entity->Tag = Entity::EntityTypes::GroundControl;
			}
			else if (object->GetName() == "FallControl")
			{
				entity->Tag = Entity::EntityTypes::FallControl;
			}
			else
			{
				entity->Tag = Entity::EntityTypes::Static;
			}

			mQuadTree->insertEntity(entity);
		}
	}
#pragma endregion

	//khoi tao nhung tang qua tao
#pragma region -APPLE LAYER-
	createApple(mListItems, D3DXVECTOR3(820, 880, 0), 3);
	createApple(mListItems, D3DXVECTOR3(1400, 880, 0), 2);
	createApple(mListItems, D3DXVECTOR3(1680, 880, 0), 2);

	for (auto child : mListItems)
	{
		mQuadTree->insertEntity(child);
	}
#pragma endregion

	//tao oroku
#pragma region -OROKU-
	//createOroku(mListOrokus, D3DXVECTOR3(576, 632, 0), 1);
	//createOroku(mListOrokus, D3DXVECTOR3(1230, 665, 0), 1);
	createOroku(mListOrokus, D3DXVECTOR3(1230, 985, 0), 2);
	//createOroku(mListOrokus, D3DXVECTOR3(776, 630.5f, 0), 3);

	for (auto child : mListOrokus)
	{
		mQuadTree->insertEntity(child);
	}
#pragma endregion
}

void GameMap::createApple(std::vector<Item*> &entitiesOut, D3DXVECTOR3 position, int soTang)
{
	if (soTang < 1 || soTang > 3)
	{
		return;
	}

	Item *Item = nullptr;

	for (size_t i = 1; i <= soTang; i++)
	{
		switch (i)
		{
		case 1:
			Item = new AppleItem(position);
			entitiesOut.push_back(Item);
			break;

		case 2:
			Item = new AppleItem(D3DXVECTOR3(position.x - 50, position.y + 40, 0));
			entitiesOut.push_back(Item);
			Item = new AppleItem(D3DXVECTOR3(position.x + 50, position.y + 40, 0));
			entitiesOut.push_back(Item);
			break;

		case 3:
			Item = new AppleItem(D3DXVECTOR3(position.x - 100, position.y + 80, 0));
			entitiesOut.push_back(Item);
			Item = new AppleItem(D3DXVECTOR3(position.x + 100, position.y + 80, 0));
			entitiesOut.push_back(Item);
			break;

		default:
			break;
		}
	}

	for (auto child : entitiesOut)
	{
		child->Tag = Entity::EntityTypes::AppleItem;
	}
}

void GameMap::createOroku(std::vector<Oroku*> &entitiesOut, D3DXVECTOR3 position, int orokuType)
{
	Oroku *oroku = nullptr;

	switch (orokuType)
	{
	case 1:
		oroku = new ThinGuard(position);
		oroku->Tag = Entity::EntityTypes::Guard;
		entitiesOut.push_back(oroku);
		break;
	case 2:
		oroku = new FatGuard(position);
		oroku->Tag = Entity::EntityTypes::Guard;
		oroku->SetQuadTree(this->GetQuadTree());
		entitiesOut.push_back(oroku);
		break;
	case 3:
		oroku = new StrongGuard(position);
		oroku->Tag = Entity::EntityTypes::Guard;
		entitiesOut.push_back(oroku);
		break;

	default:
		break;
	}

	oroku->bloodOfEntity = Define::GUARD_BLOOD;
}

void GameMap::SetCamera(Camera* camera)
{
	mCamera = camera;
}

Tmx::Map* GameMap::GetMap()
{
	return mMap;
}

RECT GameMap::GetWorldMapBound()
{
	RECT bound;
	bound.left = bound.top = 0;
	bound.right = mMap->GetWidth() * mMap->GetTileWidth();
	bound.bottom = mMap->GetHeight() * mMap->GetTileHeight();

	return bound;
}

int GameMap::GetWidth()
{
	return mMap->GetWidth() * mMap->GetTileWidth();
}

int GameMap::GetHeight()
{
	return mMap->GetHeight() * mMap->GetTileHeight();
}

int GameMap::GetTileWidth()
{
	return mMap->GetTileWidth();
}

int GameMap::GetTileHeight()
{
	return mMap->GetTileHeight();
}

bool GameMap::IsBoundLeft()
{
	return (mCamera->GetBound().left == 0);
}

bool GameMap::IsBoundRight()
{
	return (mCamera->GetBound().right == this->GetWidth());
}

bool GameMap::IsBoundTop()
{
	return (mCamera->GetBound().top == 0);
}

bool GameMap::IsBoundBottom()
{
	return (mCamera->GetBound().bottom == this->GetHeight());
}

void GameMap::Update(float dt)
{
	for (size_t i = 0; i < mListItems.size(); i++)
	{
		mListItems[i]->Update(dt);
	}

	for (size_t i = 0; i < mListOrokus.size(); i++)
	{
		/*neu oroku chua set player thi se set player
		set player duoc dat o update vi khi khoi tao thi map duoc khoi tao truoc roi moi toi player
		nen chung ta k the set player cho oroku luc khoi tao vi luc do player == NULL
		va chung ta can set player cho oroku truoc khi oroku goi update*/
		if (!mListOrokus[i]->settedPlayer)
		{
			mListOrokus[i]->SetPlayer(this->GetPlayer());
			mListOrokus[i]->settedPlayer = true;
		}
		mListOrokus[i]->Update(dt);
	}
}

void GameMap::Draw()
{
	D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
		GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);

#pragma region DRAW TILESET
	for (size_t i = 0; i < mMap->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer *layer = mMap->GetTileLayer(i);

		if (!layer->IsVisible())
		{
			continue;
		}

		if (layer->GetName() == "Tile Layer 3")
		{
			this->GetPlayer()->Draw();
		}

		for (size_t j = 0; j < mMap->GetNumTilesets(); j++)
		{
			const Tmx::Tileset *tileSet = mMap->GetTileset(j);

			RECT sourceRECT;

			int tileWidth = mMap->GetTileWidth();
			int tileHeight = mMap->GetTileHeight();

			int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
			int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

			for (size_t m = 0; m < layer->GetHeight(); m++)
			{
				for (size_t n = 0; n < layer->GetWidth(); n++)
				{
					if (layer->GetTileTilesetIndex(n, m) != -1)
					{
						int tileID = layer->GetTileId(n, m);

						int y = tileID / tileSetWidth;
						int x = tileID - y * tileSetWidth;

						sourceRECT.top = y * tileHeight;
						sourceRECT.bottom = sourceRECT.top + tileHeight;
						sourceRECT.left = x * tileWidth;
						sourceRECT.right = sourceRECT.left + tileWidth;

						Sprite* sprite = mListTileset[j];

						//tru tilewidth/2 va tileheight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
						//dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
						D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2, 0);

						if (mCamera != NULL)
						{
							RECT objRECT;
							objRECT.left = position.x - tileWidth / 2;
							objRECT.top = position.y - tileHeight / 2;
							objRECT.right = objRECT.left + tileWidth;
							objRECT.bottom = objRECT.top + tileHeight;

							if (!GameCollision::RecteAndRect(mCamera->GetBound(), objRECT).IsCollided)
								continue;
						}

						sprite->SetWidth(tileWidth);
						sprite->SetHeight(tileHeight);

						sprite->Draw(position, sourceRECT, D3DXVECTOR2(), trans);
					}
				}
			}
		}
	}
#pragma endregion

#pragma region DRAW Item

	for (size_t i = 0; i < mListItems.size(); i++)
	{
		mListItems[i]->Draw(trans);
	}

#pragma endregion

#pragma region DRAW OROKU
	for (size_t i = 0; i < mListOrokus.size(); i++)
	{
		mListOrokus[i]->Draw(trans);
	}
#pragma endregion
}

std::map<int, Sprite*> GameMap::GetListTileSet()
{
	return mListTileset;
}

void GameMap::RemoveItem(Item *item)
{
	//lay ra vi tri cua Item o trong mang
	for (size_t i = 0; i < mListItems.size(); i++)
	{
		if (mListItems.at(i)->GetPosition() == item->GetPosition())
		{
			//xoa Item khoi mang
			mListItems.erase(mListItems.begin() + i);
		}
	}
}

void GameMap::RemoveOroku(Oroku *oroku)
{
	//lay ra vi tri cua oroku o trong mang
	for (size_t i = 0; i < mListOrokus.size(); i++)
	{
		if (mListOrokus.at(i)->GetPosition() == oroku->GetPosition())
		{
			//xoa oroku khoi mang
			mListOrokus.erase(mListOrokus.begin() + i);
		}
	}

}

std::vector<Oroku*> GameMap::GetListOroku()
{
	return mListOrokus;
}

void GameMap::SetPlayer(Player* player)
{
	mPlayer = player;
}

Player* GameMap::GetPlayer()
{
	return mPlayer;
}

void GameMap::InsertUpStairs()
{
	for (auto child : mListUpStairs)
	{
		mQuadTree->insertEntity(child);
	}
}

void GameMap::InsertDownStairs()
{
	for (auto child : mListDownStairs)
	{
		mQuadTree->insertEntity(child);
	}
}

void GameMap::RemoveUpStairs()
{
	for (auto child : mListUpStairs)
	{
		mQuadTree->removeEntity(child);
	}
}

void GameMap::RemoveDownStairs()
{
	for (auto child : mListDownStairs)
	{
		//if (child->Tag == Entity::EntityTypes::CenterStairs)
		//	continue;
		mQuadTree->removeEntity(child);
	}
}

QuadTree * GameMap::GetQuadTree()
{
	return mQuadTree;
}
