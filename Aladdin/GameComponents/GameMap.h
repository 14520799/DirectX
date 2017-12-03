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
	void createApple(std::vector<MapObject*> &entitiesOut, D3DXVECTOR3 position, int soTang);
	void createItem(std::vector<MapObject*> &entitiesOut, D3DXVECTOR3 position, int MapObjectId);
	void createOroku(std::vector<Oroku*> &entitiesOut, D3DXVECTOR3 position, int orokuId);

    bool IsBoundLeft(); //kiem tra luc nay Camera o vi bien ben trai so voi WorldMap
    bool IsBoundRight(); // kiem tra xem co o vi tri bien ben phai worldmap khong
    bool IsBoundTop(); // kiem tra xem co o vi tri bien ben trai worldmap khong
    bool IsBoundBottom(); // kiem tra xem co o vi tri bien ben phai worldmap khong
    ~GameMap();

	std::vector<Oroku*> GetListOroku();
	std::vector<Oroku*> GetListOrokuSupport();
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
	float timeDelayRevitalization;
private:
    void LoadMap(char* filePath);

    Tmx::Map                        *mMap;
    std::map<int, Sprite*>          mListTileset;
    LPD3DXSPRITE                    mSpriteHandler;
    Camera                          *mCamera;
	Player							*mPlayer;
    QuadTree                        *mQuadTree;
    std::vector<MapObject*>			mListMapObjects;
	std::vector<MapObject*>			mListItemEffects; //luu 1 mang cac effect khi player va cham voi item
	std::vector<Oroku*>             mListOrokus;
	std::vector<Oroku*>				mListOrokusSupport;
	std::vector<Entity*>			mListUpStairs;
	std::vector<Entity*>			mListDownStairs;

	MapObject *itemEffect;
};

#endif

