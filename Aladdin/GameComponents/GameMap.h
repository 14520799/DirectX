#pragma once
#ifndef __GAME_MAP__
#define __GAME_MAP__

class Oroku;
class Player;

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "../GameComponents/Sprite.h"
#include "../MapReader/Tmx.h.in"
#include "Camera.h"
#include "GameGlobal.h"
#include "GameCollision.h"
#include "QuadTree.h"
#include "../GameObjects/MapObjects/MapObject.h"

class GameMap
{
public:
    GameMap(char* filePath);
	void LoadMapItems(char* filepath);
	void LoadMapOrokus(char* filepath);
    void SetCamera(Camera* camera);
    void Update(float dt);
    void Draw();
    Tmx::Map* GetMap();
    RECT GetWorldMapBound();
    int GetWidth();
    int GetHeight();
    int GetTileWidth();
    int GetTileHeight();
    std::map<int, Sprite*> GetListTileSet();

	//tao vat pham len map vd: tao, tien, ...
    bool IsBoundLeft(); //kiem tra luc nay Camera o vi bien ben trai so voi WorldMap
    bool IsBoundRight(); // kiem tra xem co o vi tri bien ben phai worldmap khong
    bool IsBoundTop(); // kiem tra xem co o vi tri bien ben trai worldmap khong
    bool IsBoundBottom(); // kiem tra xem co o vi tri bien ben phai worldmap khong
    ~GameMap();

	std::vector<Oroku*> GetListOroku();
	std::vector<Entity*> GetListPlayerSupport();
	void RemoveMapObject(MapObject *MapObject);
	void RemoveOroku(Oroku *oroku);

	void SetPlayer(Player* player);
	Player* GetPlayer();

	void InsertUpStairs();
	void InsertDownStairs();
	void RemoveUpStairs();
	void RemoveDownStairs();

    QuadTree* GetQuadTree();
	//delaytime de revitalization thuc hien xong state action
	float timeDelayStateItem;
	float timeDelayCreateFireEffect;

	Oroku *mBoss;
private:
    void LoadMap(char* filePath);

    Tmx::Map                        *mMap;
    std::map<int, Sprite*>          mListTileset;
    LPD3DXSPRITE                    mSpriteHandler;
    Camera                          *mCamera;
	Player							*mPlayer;
    QuadTree                        *mQuadTree;
    std::vector<MapObject*>			mListMapObjects;
	std::vector<MapObject*>			mListItemEffects; //luu 1 mang cac effect khi player va cham vao item
	std::vector<MapObject*>			mListItemAttackEffects; //luu 1 mang cac attack effect cua item khi player va cham vao item
	std::vector<Oroku*>             mListOrokus;
	std::vector<Entity*>			mListPlayerSupport;
	std::vector<Entity*>			mListUpStairs;
	std::vector<Entity*>			mListDownStairs;

	MapObject *itemEffect;
	MapObject *itemAttackEffect;
};

#endif

