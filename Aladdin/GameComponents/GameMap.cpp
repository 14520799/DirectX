#include "GameMap.h"
#include "../GameDefines/GameDefine.h"
#include "../GameObjects/MapObjects/Items/AppleItem.h"
#include "../GameObjects/MapObjects/Items/RevitalizationDefault.h"
#include "../GameObjects/MapObjects/Items/RevitalizationAction.h"
#include "../GameObjects/MapObjects/Items/RevitalizationActionStop.h"
#include "../GameObjects/MapObjects/Items/FeddlerStanding.h"
#include "../GameObjects/MapObjects/Items/FeddlerMagic.h"
#include "../GameObjects/MapObjects/Items/FeddlerMagicStop.h"
#include "../GameObjects/MapObjects/Items/Lamp.h"
#include "../GameObjects/MapObjects/Items/Ruby.h"
#include "../GameObjects/MapObjects/Items/HeadGenie.h"
#include "../GameObjects/MapObjects/Items/Heart.h"
#include "../GameObjects/MapObjects/Items/Life.h"
#include "../GameObjects/MapObjects/Items/ItemEffect_1.h"
#include "../GameObjects/MapObjects/Items/ItemEffect_2.h"
#include "../GameObjects/MapObjects/Weapons/FireEffect.h"
#include "../GameObjects/MapObjects/Items/LampEffect.h"
#include "../GameObjects/MapObjects/Items/LampAttack.h"
#include "../GameObjects/MapObjects/Items/OrokuEffect.h"
#include "../GameObjects/MapObjects/ObjectsMap/Stairs.h"
#include "../GameObjects/MapObjects/ObjectsMap/Spring.h"
#include "../GameObjects/MapObjects/ObjectsMap/Bin.h"
#include "../GameObjects/MapObjects/ObjectsMap/SpringAction.h"
#include "../GameObjects/MapObjects/ObjectsMap/Cloud1_Scene1.h"
#include "../GameObjects/MapObjects/ObjectsMap/Cloud2_Scene1.h"
#include "../GameObjects/MapObjects/ObjectsMap/Cloud1_Scene2.h"
#include "../GameObjects/MapObjects/ObjectsMap/Cloud2_Scene2.h"
#include "../GameObjects/Orokus/BossJafar/Jafar.h"
#include "../GameObjects/Orokus/Guards/ThinGuard.h"
#include "../GameObjects/Orokus/Guards/FatGuard.h"
#include "../GameObjects/Orokus/Guards/StrongGuard.h"
#include "../GameObjects/Orokus/Camel/Camel.h"
#include "../GameObjects/Orokus/Civilians/CivilianWindow.h"
#include "../GameObjects/Orokus/Civilians/CivilianCircus.h"
#include "../GameObjects/Orokus/Civilians/CivilianBasket.h"

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

	for (size_t i = 0; i < mListUpStairs.size(); i++)
	{
		if (mListUpStairs[i])
			delete mListUpStairs[i];
	}
	mListUpStairs.clear();

	for (size_t i = 0; i < mListDownStairs.size(); i++)
	{
		if (mListDownStairs[i])
			delete mListDownStairs[i];
	}
	mListDownStairs.clear();

	for (size_t i = 0; i < mListClouds.size(); i++)
	{
		if (mListClouds[i])
			delete mListClouds[i];
	}
	mListClouds.clear();

	for (size_t i = 0; i < mListOrokus.size(); i++)
	{
		if (mListOrokus[i])
			delete mListOrokus[i];
	}
	mListOrokus.clear();

	for (size_t i = 0; i < mListPlayerSupport.size(); i++)
	{
		if (mListPlayerSupport[i])
			delete mListPlayerSupport[i];
	}
	mListPlayerSupport.clear();

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
			else if (object->GetName() == "VerticalRopeControl")
			{
				entity->Tag = Entity::EntityTypes::VerticalRopeControl;
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
			else if (object->GetName() == "OrokuControl")
			{
				entity->Tag = Entity::EntityTypes::OrokuControl;

			}
			else if (object->GetName() == "TranslateScene")
			{
				entity->Tag = Entity::EntityTypes::TranslateScene;
			}
			else
			{
				entity->Tag = Entity::EntityTypes::Static;
			}

			mQuadTree->insertEntity(entity);
		}
	}
#pragma endregion
}

void GameMap::LoadMapItems(char* filepath)
{
	FILE *file;
	file = fopen(filepath, "r");

	if (file)
	{
		while (!feof(file))
		{
			char name[100];
			char info[1000];
			fgets(info, 100, file);
			float x, y;
			fscanf(file, "%s %f %f", &name, &x, &y);
			D3DXVECTOR3 position = D3DXVECTOR3(x, y, 0);
			MapObject *item = nullptr;
			char chr = name[strlen(name) - 1];
			switch (chr)
			{
			case 'A':
				item = new AppleItem(position);
				break;
			case 'R':
				item = new Ruby(position);
				break;
			case 'r':
				item = new RevitalizationDefault(position);
				break;
			case 'H':
				item = new HeadGenie(position);
				break;
			case 'h':
				item = new Heart(position);
				break;
			case 'L':
				item = new Lamp(position);
				break;
			case 'l':
				item = new Life(position);
				break;
			case 'S':
				item = new Stairs(position);
				break;
			case 's':
				item = new Spring(position);
				break;
			case 'F':
				item = new FeddlerStanding(position);
				break;
			case 'B':
				item = new Bin(position);
				break;
			default:
				break;
			}
			item->originPos = position;
			mListMapObjects.push_back(item);
			if (item->Tag == Entity::EntityTypes::Bin)
				continue;
			mQuadTree->insertEntity(item);
		}
	}
	fclose(file);
}

void GameMap::LoadMapOrokus(char* filepath)
{
	FILE *file;
	file = fopen(filepath, "r");

	if (file)
	{
		while (!feof(file))
		{
			int id;
			char info[1000];
			fgets(info, 100, file);
			float x, y;
			fscanf(file, "%d %f %f", &id, &x, &y);
			D3DXVECTOR3 position = D3DXVECTOR3(x, y, 0);
			Oroku *oroku = nullptr;
			switch (id)
			{
			case 0:
				mBoss = new Jafar(position);
				mBoss->Tag = Entity::EntityTypes::Oroku;
				mBoss->bloodOfEntity = Define::BOSS_BLOOD;
				break;
			case 1:
				oroku = new ThinGuard(position);
				break;
			case 2:
				oroku = new FatGuard(position);
				break;
			case 3:
				oroku = new StrongGuard(position);
				break;
			case 4:
				oroku = new Camel(position);
				mListPlayerSupport.push_back(oroku);
				break;
			case 5:
				oroku = new CivilianWindow(position);
				break;
			case 6:
				oroku = new CivilianCircus(position);
				break;
			case 7:
				oroku = new CivilianBasket(position);
				break;
			default:
				break;
			}
			if (id != 0)
			{
				oroku->Tag = Entity::EntityTypes::Oroku;
				oroku->bloodOfEntity = Define::OROKU_BLOOD;
				mListOrokus.push_back(oroku);
			}
		}
	}
	fclose(file);
}

void GameMap::LoadMapCloudsScene1(char* filepath)
{
	FILE *file;
	file = fopen(filepath, "r");

	if (file)
	{
		while (!feof(file))
		{
			int id;
			char info[1000];
			fgets(info, 100, file);
			float x, y;
			fscanf(file, "%d %f %f", &id, &x, &y);
			D3DXVECTOR3 position = D3DXVECTOR3(x, y, 0);
			MapObject *cloud = nullptr;
			switch (id)
			{
			case 1:
				cloud = new Cloud1_Scene1(position);
				break;
			case 2:
				cloud = new Cloud2_Scene1(position);
				break;		
			default:
				break;
			}
			cloud->originPos = cloud->GetPosition();
			mListClouds.push_back(cloud);
		}
	}
	fclose(file);
}

void GameMap::LoadMapCloudsScene2(char* filepath)
{
	FILE *file;
	file = fopen(filepath, "r");

	if (file)
	{
		while (!feof(file))
		{
			int id;
			char info[1000];
			fgets(info, 100, file);
			float x, y;
			fscanf(file, "%d %f %f", &id, &x, &y);
			D3DXVECTOR3 position = D3DXVECTOR3(x, y, 0);
			MapObject *cloud = nullptr;
			switch (id)
			{
			case 1:
				cloud = new Cloud1_Scene2(position);
				break;
			case 2:
				cloud = new Cloud2_Scene2(position);
				break;
			default:
				break;
			}
			cloud->originPos = cloud->GetPosition();
			mListClouds.push_back(cloud);
		}
	}
	fclose(file);
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
	for (size_t i = 0; i < mListClouds.size(); i++)
	{
		mListClouds.at(i)->SetVx(-Define::CLOUD_SPEED_X);
		mListClouds.at(i)->Update(dt);
		mListClouds.at(i)->Entity::Update(dt);
		if (mListClouds.at(i)->GetPosition().x - mListClouds.at(i)->originPos.x > 500)
			mListClouds.at(i)->SetPosition(mListClouds.at(i)->originPos);
	}

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
			mPlayer->mRevivalPosition = mPlayer->GetPosition();
			mPlayer->collisionRevitalization = true;
		}
		else if (mListMapObjects[i]->Id == Entity::EntityId::Revitalization_Action)
		{
			timeDelayStateItem += dt;
			if (timeDelayStateItem > 1.0f)
			{
				D3DXVECTOR3 pos = mListMapObjects[i]->GetPosition();
				delete mListMapObjects[i];
				mListMapObjects[i] = new RevitalizationActionStop(pos);
				mListMapObjects[i]->Id = Entity::EntityId::Revitalization_ActionStop;
				timeDelayStateItem = 0;
			}
		}
#pragma endregion

#pragma region Feddler
		if (mListMapObjects[i]->Id == Entity::EntityId::Feddler_Standing && mPlayer->collisionFeddler)
		{
			D3DXVECTOR3 pos = mListMapObjects[i]->GetPosition();
			mQuadTree->removeEntity(mListMapObjects[i]);
			delete mListMapObjects[i];
			mListMapObjects[i] = new FeddlerMagic(pos);
			mListMapObjects[i]->Id = Entity::EntityId::Feddler_Magic;
		}
		else if (mListMapObjects[i]->Id == Entity::EntityId::Feddler_Magic)
		{
			timeDelayStateItem += dt;
			if (timeDelayStateItem > 1.1f)
			{
				D3DXVECTOR3 pos = mListMapObjects[i]->GetPosition();
				delete mListMapObjects[i];
				mListMapObjects[i] = new FeddlerMagicStop(pos);
				mListMapObjects[i]->Id = Entity::EntityId::Feddler_MagicStop;
				timeDelayStateItem = 0;
			}
		}
#pragma endregion

#pragma region Spring
		if (mPlayer->collisionSpring)
		{
			if (mListMapObjects.at(i)->GetPosition() == mPlayer->mOriginPositionItem)
			{
				mPlayer->collisionSpring = false;
				delete mListMapObjects.at(i);
				mListMapObjects.at(i) = new SpringAction(mPlayer->mOriginPositionItem);
			}
		}

		if (mListMapObjects.at(i)->Tag == Entity::EntityTypes::SpringAction)
		{
			mListMapObjects.at(i)->timeDelaySpringAction += dt;
			if (mListMapObjects.at(i)->timeDelaySpringAction > 0.2f)
			{
				D3DXVECTOR3 temp = mListMapObjects.at(i)->GetPosition();
				delete mListMapObjects.at(i);
				mListMapObjects.at(i) = new Spring(temp);
			}
		}
#pragma endregion

		mListMapObjects[i]->Update(dt);

		//xu ly cau thang roi xuong
		if (mListMapObjects[i]->Tag == Entity::EntityTypes::ObjStairs)
		{
			if (mListMapObjects[i]->collisionWithPlayer)
			{
				mListMapObjects[i]->AddVy(Define::ITEM_SPEED_Y / 2);
				mListMapObjects[i]->Entity::Update(dt);
				mPlayer->AddPosition(0, 3);
				if (mListMapObjects[i]->GetPosition().y - mListMapObjects[i]->originPos.y > Define::STAIRS_FALL)
				{
					mListMapObjects[i]->SetPosition(mListMapObjects[i]->originPos);
					mListMapObjects[i]->SetVy(0);
					mListMapObjects[i]->collisionWithPlayer = false;
				}
			}
		}
	}

#pragma region CREATE ItemEffect
	//tao ra effect cho item truoc khi bi huy
	if (mPlayer->allowItemEffect)
	{
		if (mPlayer->effectLamp)
		{
			itemEffect = new LampEffect(mPlayer->mOriginPositionItem + D3DXVECTOR3(0, -70, 0));
			for (size_t i = 0; i < 4; i++)
			{
				itemAttackEffect = new LampAttack(mPlayer->mOriginPositionItem);
				itemAttackEffect->originPos = itemAttackEffect->GetPosition();
				mListItemAttackEffects.push_back(itemAttackEffect);
				mListPlayerSupport.push_back(itemAttackEffect);
			}
		}
		else if (mPlayer->effectSpecial)
			itemEffect = new ItemEffect_2(mPlayer->mOriginPositionItem);
		else
			itemEffect = new ItemEffect_1(mPlayer->mOriginPositionItem);
		mListItemEffects.push_back(itemEffect);
		mPlayer->allowItemEffect = false;
		mPlayer->effectLamp = false;
		mPlayer->effectSpecial = false;
	}
	if (mPlayer->allowOrokuEffect)
	{
		itemEffect = new OrokuEffect(mPlayer->mOriginPositionItem);
		mListItemEffects.push_back(itemEffect);
		mPlayer->allowOrokuEffect = false;
	}
	if (mPlayer->allowBossEffect)
	{
		itemEffect = new LampEffect(mPlayer->mOriginPositionItem);
		mListItemEffects.push_back(itemEffect);
		mPlayer->allowBossEffect = false;
	}
	if (mPlayer->effectFire)
	{
		timeDelayCreateFireEffectPlayer += dt;
		if (timeDelayCreateFireEffectPlayer > 0.1f)
		{
			itemEffect = new FireEffect(mPlayer->mOriginPositionItem);
			mListItemEffects.push_back(itemEffect);
			timeDelayCreateFireEffectPlayer = 0;
		}
		mPlayer->effectFire = false;
	}
	if (mPlayer->collisionFireWeapon)
	{
		timeDelayCreateFireEffectPlayer += dt;
		if (timeDelayCreateFireEffectPlayer > 0.5f)
		{
			itemEffect = new FireEffect(D3DXVECTOR3(mPlayer->GetPosition().x, mBoss->GetPosition().y + mBoss->GetHeight() / 2 - 55, 0));
			this->mBoss->mListWeaponEffect.push_back(itemEffect);
			timeDelayCreateFireEffectPlayer = 0;
		}
		mPlayer->collisionFireWeapon = false;
	}
#pragma endregion

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
		//tao hieu ung lua dot cho strongguard
		if (mListOrokus[i]->Id == Entity::EntityId::Guard)
		{
			if (mListOrokus[i]->effectFire)
			{
				timeDelayCreateFireEffectGuard += dt;
				if (timeDelayCreateFireEffectGuard > 0.4f)
				{
					itemEffect = new FireEffect(mListOrokus[i]->mOriginPositionItem);
					mListItemEffects.push_back(itemEffect);
					timeDelayCreateFireEffectGuard = 0;
				}
				mPlayer->effectFire = false;
			}
		}
		mListOrokus[i]->Update(dt);
	}

	if (mBoss != nullptr)
	{
		if (!mBoss->settedPlayer)
		{
			mBoss->SetPlayer(this->GetPlayer());
			mBoss->settedPlayer = true;
		}
		mBoss->Update(dt);
	}

#pragma region Update Aniamation Effect
	//chay animation cho effect roi huy
	if (mListItemEffects.size() != 0)
	{
		for (size_t i = 0; i < mListItemEffects.size(); i++)
		{
			mListItemEffects.at(i)->Update(dt);
			mListItemEffects.at(i)->timeDelayItemEffect += dt;
			if (mListItemEffects.at(i)->Id == Entity::EntityId::ItemEffect_2)
			{
				if (mListItemEffects.at(i)->timeDelayItemEffect > 0.5f)
				{
					delete mListItemEffects.at(i);
					mListItemEffects.at(i) = nullptr;
					mListItemEffects.erase(mListItemEffects.begin() + i);
					if (mListItemEffects.size() == 0)
						break;
					i--;
				}
			}
			else if (mListItemEffects.at(i)->Id == Entity::EntityId::FireEffect)
			{
				if (mListItemEffects.at(i)->timeDelayItemEffect > 0.5f)
				{
					delete mListItemEffects.at(i);
					mListItemEffects.at(i) = nullptr;
					mListItemEffects.erase(mListItemEffects.begin() + i);
					if (mListItemEffects.size() == 0)
						break;
					i--;
				}
			}
			else
			{
				if (mListItemEffects.at(i)->timeDelayItemEffect > 0.4f)
				{
					delete mListItemEffects.at(i);
					mListItemEffects.at(i) = nullptr;
					mListItemEffects.erase(mListItemEffects.begin() + i);
					if (mListItemEffects.size() == 0)
						break;
					i--;
				}
			}
		}
	}
	//xy ly nhung effect cua item khi attack
	if (mListItemAttackEffects.size() != 0)
	{
		for (size_t i = 0; i < mListItemAttackEffects.size(); i++)
		{
			mListItemAttackEffects.at(i)->Update(dt);
			if (i == 0)
			{
				mListItemAttackEffects.at(i)->AddVx(-4);
				mListItemAttackEffects.at(i)->AddVy(-2);
			}
			else if (i == 1)
			{
				mListItemAttackEffects.at(i)->AddVx(-4);
				mListItemAttackEffects.at(i)->AddVy(-8);
			}
			else if (i == 2)
			{
				mListItemAttackEffects.at(i)->AddVx(4);
				mListItemAttackEffects.at(i)->AddVy(-8);
			}
			else if (i == 3)
			{
				mListItemAttackEffects.at(i)->AddVx(4);
				mListItemAttackEffects.at(i)->AddVy(-2);
			}

			mListItemAttackEffects.at(i)->Entity::Update(dt);
			mListItemAttackEffects.at(i)->timeDelayItemEffect += dt;
			if (mListItemAttackEffects.at(i)->timeDelayItemEffect > 1.0f)
			{
				mListItemAttackEffects.at(i)->SetPosition(mListItemAttackEffects.at(i)->originPos);
				for (size_t j = 0; j < mListPlayerSupport.size(); j++)
				{
					if (mListPlayerSupport.at(j)->GetPosition() == mListItemAttackEffects.at(i)->GetPosition())
					{
						mListPlayerSupport.erase(mListPlayerSupport.begin() + j);
						break;
					}
				}
				delete mListItemAttackEffects.at(i);
				mListItemAttackEffects.at(i) = nullptr;
				mListItemAttackEffects.erase(mListItemAttackEffects.begin() + i);
				i--;
			}
		}
	}
#pragma endregion
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

		if (layer->GetName() == "Tile Layer 2")
		{
			for (size_t i = 0; i < mListClouds.size(); i++)
			{
				mListClouds.at(i)->Draw(D3DXVECTOR3(mListClouds.at(i)->posX, mListClouds.at(i)->posY, 0), trans);
			}
		}
		else if (layer->GetName() == "Tile Layer 3")
		{
#pragma region DRAW ITEM

			for (size_t i = 0; i < mListMapObjects.size(); i++)
			{
				if (mListMapObjects[i]->Tag == Entity::EntityTypes::ObjStairs)
				{
					mListMapObjects[i]->Draw(D3DXVECTOR3(mListMapObjects[i]->posX, mListMapObjects[i]->posY, 0), trans);
					continue;
				}
				mListMapObjects[i]->Draw(trans);
			}

#pragma endregion

#pragma region DRAW ITEMEFFECT
			//ve item effect
			if (mListItemEffects.size() > 0)
			{
				for (size_t i = 0; i < mListItemEffects.size(); i++)
				{
					mListItemEffects.at(i)->Draw(trans);
				}
			}
			//ve item attack effect
			if (mListItemAttackEffects.size() > 0)
			{
				for (size_t i = 0; i < mListItemAttackEffects.size(); i++)
				{
					mListItemAttackEffects.at(i)->Draw(D3DXVECTOR3(mListItemAttackEffects.at(i)->posX, mListItemAttackEffects.at(i)->posY, 0), trans);
				}
			}
#pragma endregion

#pragma region DRAW OROKU
			for (size_t i = 0; i < mListOrokus.size(); i++)
			{
				mListOrokus[i]->Draw(trans);
			}
#pragma endregion

#pragma region DRAW PLAYERSUPPORT
			for (size_t i = 0; i < mListPlayerSupport.size(); i++)
			{
				mListPlayerSupport[i]->Draw(trans);
			}
#pragma endregion

			if (mBoss != nullptr)
				mBoss->Draw(trans);

			//draw player
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

#pragma region PLAYER INFO
	D3DXVECTOR2 transBloodInfo = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x + mCamera->GetBound().left + mPlayer->BloodInfoPos.x,
		GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y + mCamera->GetBound().top + mPlayer->BloodInfoPos.y);
	mPlayer->BloodInfo->Draw(mPlayer->BloodInfoPos, transBloodInfo);

	mPlayer->TxtScore->Draw(D3DXVECTOR3(550, 70, 0));

	D3DXVECTOR2 transAppleInfo = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x + mCamera->GetBound().left + mPlayer->AppleInfoPos.x,
		GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y + mCamera->GetBound().top + mPlayer->AppleInfoPos.y);
	mPlayer->AppleInfo->Draw(mPlayer->AppleInfoPos, transAppleInfo);

	mPlayer->TxtApple->Draw(D3DXVECTOR3(655, 450, 0));

	D3DXVECTOR2 transRubyInfo = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x + mCamera->GetBound().left + mPlayer->RubyInfoPos.x,
		GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y + mCamera->GetBound().top + mPlayer->RubyInfoPos.y);
	mPlayer->RubyInfo->Draw(mPlayer->RubyInfoPos, transRubyInfo);

	mPlayer->TxtRuby->Draw(D3DXVECTOR3(550, 450, 0));

	D3DXVECTOR2 transLifeInfo = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x + mCamera->GetBound().left + mPlayer->LifeInfoPos.x,
		GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y + mCamera->GetBound().top + mPlayer->LifeInfoPos.y);
	mPlayer->LifeInfo->Draw(mPlayer->LifeInfoPos, transLifeInfo);

	mPlayer->TxtLife->Draw(D3DXVECTOR3(150, 450, 0));
#pragma endregion
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

std::vector<Entity*> GameMap::GetListPlayerSupport()
{
	return mListPlayerSupport;
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
