#include "GameMap.h"
#include "../GameDefines/GameDefine.h"
#include "../GameObjects/MapObjects/Items/AppleItem.h"
#include "../GameObjects/MapObjects/Items/RevitalizationDefault.h"
#include "../GameObjects/MapObjects/Items/RevitalizationAction.h"
#include "../GameObjects/MapObjects/Items/RevitalizationActionStop.h"
#include "../GameObjects/MapObjects/Items/Lamp.h"
#include "../GameObjects/MapObjects/Items/AppleGod.h"
#include "../GameObjects/MapObjects/Items/HeadGenie.h"
#include "../GameObjects/MapObjects/Items/Heart.h"
#include "../GameObjects/MapObjects/Items/Life.h"
#include "../GameObjects/MapObjects/Items/ItemEffect.h"
#include "../GameObjects/Orokus/Guards/ThinGuard.h"
#include "../GameObjects/Orokus/Guards/FatGuard.h"
#include "../GameObjects/Orokus/Guards/StrongGuard.h"
#include "../GameObjects/Orokus/Camel/Camel.h"
#include "../GameObjects/Orokus/Civilians/CivilianWindow.h"
#include "../GameObjects/Orokus/Civilians/CivilianCircus.h"

GameMap::GameMap(char* filePath)
{
	mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	LoadMap(filePath);
}

GameMap::~GameMap()
{
	delete mMap;

	for (size_t i = 0; i < mListMapObjects.size(); i++)
	{
		if (mListMapObjects[i])
			delete mListMapObjects[i];
	}
	mListMapObjects.clear();

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
			else if (object->GetName() == "FireControl")
			{
				entity->Tag = Entity::EntityTypes::FireControl;
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
			else if (object->GetName() == "Ground")
			{
				entity->Tag = Entity::EntityTypes::Ground;
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
	createApple(mListMapObjects, D3DXVECTOR3(820, 880, 0), 3);
	createApple(mListMapObjects, D3DXVECTOR3(1400, 880, 0), 2);
	createApple(mListMapObjects, D3DXVECTOR3(1680, 880, 0), 2);
	//1 - Revitalization, 2 - Lamp, 3 - AppleGod, 4 - HeadGenie, 5 - Heart, 6 - Life
	createItem(mListMapObjects, D3DXVECTOR3(2330, 877, 0), 1);
	//createItem(mListMapObjects, D3DXVECTOR3(1250, 900, 0), 2);
	//createItem(mListMapObjects, D3DXVECTOR3(3500, 950, 0), 3);
	//createItem(mListMapObjects, D3DXVECTOR3(3000, 950, 0), 4);
	//createItem(mListMapObjects, D3DXVECTOR3(2150, 800, 0), 5);
	//createItem(mListMapObjects, D3DXVECTOR3(2600, 700, 0), 6);

	for (auto child : mListMapObjects)
	{
		mQuadTree->insertEntity(child);
	}
#pragma endregion

	//tao oroku
#pragma region -OROKU-
	//1 - ThinGuard, 2 - FatGuard, 3 - StrongGuard, 4 - Camel, 5 - CivilianWindow, 6 - CivilianCircus
	createOroku(mListOrokus, D3DXVECTOR3(1065, 972.5f, 0), 1);
	createOroku(mListOrokus, D3DXVECTOR3(2900, 1035, 0), 2);
	createOroku(mListOrokus, D3DXVECTOR3(1545, 977.5f, 0), 3);
	createOroku(mListOrokusSupport, D3DXVECTOR3(2575, 1047.5f, 0), 4);
	createOroku(mListOrokus, D3DXVECTOR3(2848, 780, 0), 5);
	createOroku(mListOrokus, D3DXVECTOR3(2110, 850, 0), 6);

	for (auto child : mListOrokus)
	{
		mQuadTree->insertEntity(child);
	}
	for (auto child : mListOrokusSupport)
	{
		mQuadTree->insertEntity(child);
	}
#pragma endregion
}

void GameMap::createApple(std::vector<MapObject*> &entitiesOut, D3DXVECTOR3 position, int soTang)
{
	if (soTang < 1 || soTang > 3)
	{
		return;
	}

	MapObject *Item = nullptr;

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
		child->Tag = Entity::EntityTypes::Item;
		child->Id = Entity::EntityId::AppleItem;
	}
}

void GameMap::createItem(std::vector<MapObject*> &entitiesOut, D3DXVECTOR3 position, int itemId)
{
	MapObject *item = nullptr;

	switch (itemId)
	{
	case 1:
		item = new RevitalizationDefault(position);
		item->Tag = Entity::EntityTypes::Item;
		item->Id = Entity::EntityId::Revitalization_Default;
		entitiesOut.push_back(item);
		break;

	case 2:
		item = new Lamp(position);
		item->Tag = Entity::EntityTypes::Item;
		item->Id = Entity::EntityId::Lamp;
		entitiesOut.push_back(item);
		break;

	case 3:
		item = new AppleGod(position);
		item->Tag = Entity::EntityTypes::Item;
		item->Id = Entity::EntityId::AppleGod;
		entitiesOut.push_back(item);
		break;

	case 4:
		item = new HeadGenie(position);
		item->Tag = Entity::EntityTypes::Item;
		item->Id = Entity::EntityId::HeadGenie;
		entitiesOut.push_back(item);
		break;

	case 5:
		item = new Heart(position);
		item->Tag = Entity::EntityTypes::Item;
		item->Id = Entity::EntityId::Heart;
		entitiesOut.push_back(item);
		break;

	case 6:
		item = new Life(position);
		item->Tag = Entity::EntityTypes::Item;
		item->Id = Entity::EntityId::Life;
		entitiesOut.push_back(item);
		break;

	default:
		break;
	}
}

void GameMap::createOroku(std::vector<Oroku*> &entitiesOut, D3DXVECTOR3 position, int orokuId)
{
	Oroku *oroku = nullptr;

	switch (orokuId)
	{
	case 1:
		oroku = new ThinGuard(position);
		oroku->Tag = Entity::EntityTypes::Oroku;
		oroku->Id = Entity::EntityId::Guard;
		entitiesOut.push_back(oroku);
		break;
	case 2:
		oroku = new FatGuard(position);
		oroku->Tag = Entity::EntityTypes::Oroku;
		oroku->Id = Entity::EntityId::Guard;
		entitiesOut.push_back(oroku);
		break;
	case 3:
		oroku = new StrongGuard(position);
		oroku->Tag = Entity::EntityTypes::Oroku;
		oroku->Id = Entity::EntityId::Guard;
		entitiesOut.push_back(oroku);
		break;
	case 4:
		oroku = new Camel(position);
		oroku->Tag = Entity::EntityTypes::Oroku;
		oroku->Id = Entity::EntityId::Camel;
		entitiesOut.push_back(oroku);
		break;
	case 5:
		oroku = new CivilianWindow(position);
		oroku->Tag = Entity::EntityTypes::Oroku;
		oroku->Id = Entity::EntityId::CivilianWindow;
		entitiesOut.push_back(oroku);
		return;
		break;
	case 6:
		oroku = new CivilianCircus(position);
		oroku->Tag = Entity::EntityTypes::Oroku;
		oroku->Id = Entity::EntityId::CivilianCircus;
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
	for (size_t i = 0; i < mListMapObjects.size(); i++)
	{
#pragma region Revitalization
		if (mListMapObjects[i]->Id == Entity::EntityId::Revitalization_Default && mListMapObjects[i]->collisionWithPlayer)
		{
			D3DXVECTOR3 pos = mListMapObjects[i]->GetPosition();
			mQuadTree->removeEntity(mListMapObjects[i]);
			delete mListMapObjects[i];
			mListMapObjects[i] = new RevitalizationAction(pos);
			mListMapObjects[i]->Id = Entity::EntityId::Revitalization_Action;
			mPlayer->mOriginPosition = pos + D3DXVECTOR3(0, -15, 0);
		}
		if (mListMapObjects[i]->Id == Entity::EntityId::Revitalization_Action)
		{
			timeDelayRevitalization += dt;
			if (timeDelayRevitalization > 0.5f)
			{
				D3DXVECTOR3 pos = mListMapObjects[i]->GetPosition();
				delete mListMapObjects[i];
				mListMapObjects[i] = new RevitalizationActionStop(pos);
				mListMapObjects[i]->Id = Entity::EntityId::Revitalization_ActionStop;
			}
		}
#pragma endregion

		mListMapObjects[i]->Update(dt);

#pragma region ItemEffect
		if (mPlayer->allowEffect)
		{
			itemEffect = new ItemEffect(mPlayer->mOriginPositionItem);
			mListItemEffects.push_back(itemEffect);
			mPlayer->allowEffect = false;
		}
		for (size_t i = 0; i < mListItemEffects.size(); i++)
		{
			mListItemEffects.at(i)->Update(dt);
			mListItemEffects.at(i)->timeDelayItemEffect += dt;
			if (mListItemEffects.at(i)->timeDelayItemEffect > 1.0f)
			{
				delete mListItemEffects.at(i);
				mListItemEffects.at(i) = nullptr;
				mListItemEffects.erase(mListItemEffects.begin() + i);
				if (mListItemEffects.size() == 0)
					break;
				i--;
			}
		}
#pragma endregion

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
	for (size_t i = 0; i < mListOrokusSupport.size(); i++)
	{
		if (!mListOrokusSupport[i]->settedPlayer)
		{
			mListOrokusSupport[i]->SetPlayer(this->GetPlayer());
			mListOrokusSupport[i]->settedPlayer = true;
		}
		mListOrokusSupport[i]->Update(dt);
	}
}

void GameMap::Draw()
{
	D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
		GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);

	for (size_t i = 0; i < mMap->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer *layer = mMap->GetTileLayer(i);

		if (!layer->IsVisible())
		{
			continue;
		}

		if (layer->GetName() == "Tile Layer 3")
		{
			//draw player
			this->GetPlayer()->Draw();

#pragma region DRAW ITEM

			for (size_t i = 0; i < mListMapObjects.size(); i++)
			{
				mListMapObjects[i]->Draw(trans);
			}

#pragma endregion

			//ve apple effect
			if (mListItemEffects.size() > 0)
			{
				for (size_t i = 0; i < mListItemEffects.size(); i++)
				{
					mListItemEffects.at(i)->Draw(trans);
				}
			}

#pragma region DRAW OROKU
			for (size_t i = 0; i < mListOrokus.size(); i++)
			{
				mListOrokus[i]->Draw(trans);
			}
			for (size_t i = 0; i < mListOrokusSupport.size(); i++)
			{
				mListOrokusSupport[i]->Draw(trans);
			}
#pragma endregion
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

}

std::map<int, Sprite*> GameMap::GetListTileSet()
{
	return mListTileset;
}

void GameMap::RemoveMapObject(MapObject *mapObject)
{
	//lay ra vi tri cua Item o trong mang
	for (size_t i = 0; i < mListMapObjects.size(); i++)
	{
		if (mListMapObjects.at(i)->GetPosition() == mapObject->GetPosition())
		{
			//xoa Item khoi mang
			mListMapObjects.erase(mListMapObjects.begin() + i);
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

std::vector<Oroku*> GameMap::GetListOrokuSupport()
{
	return mListOrokusSupport;
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
