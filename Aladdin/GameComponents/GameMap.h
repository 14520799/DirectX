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
#include "../GameObjects/MapObjects/Item.h"

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
	void createApple(std::vector<Item*> &entitiesOut, D3DXVECTOR3 position, int soTang);
	void createOroku(std::vector<Oroku*> &entitiesOut, D3DXVECTOR3 position, int orokuType, int orokuId);

    bool IsBoundLeft(); //kiem tra luc nay Camera o vi bien ben trai so voi WorldMap
    bool IsBoundRight(); // kiem tra xem co o vi tri bien ben phai worldmap khong
    bool IsBoundTop(); // kiem tra xem co o vi tri bien ben trai worldmap khong
    bool IsBoundBottom(); // kiem tra xem co o vi tri bien ben phai worldmap khong
    ~GameMap();

	void SetListItem(std::vector<Item*> listItems);
    std::vector<Item*> GetListItem();

	void SetListOroku(std::vector<Oroku*> listOrokus);
	std::vector<Oroku*> GetListOroku();

	Item* GetItem(std::vector<Item*> entitiesIn, Item *item);
	Oroku* GetOroku(std::vector<Oroku*> entitiesIn, Oroku *oroku);

	std::vector<Item*> RemoveItem(std::vector<Item*> &entitiesIn, Item *item);
	std::vector<Oroku*> RemoveOroku(std::vector<Oroku*> &entitiesIn, Oroku *oroku);

	void SetPlayer(Player* player);
	Player* GetPlayer();

	void InsertUpStairs();
	void InsertDownStairs();
	void RemoveUpStairs();
	void RemoveDownStairs();

    QuadTree* GetQuadTree();

private:
    void LoadMap(char* filePath);

    Tmx::Map                        *mMap;
    std::map<int, Sprite*>          mListTileset;
    LPD3DXSPRITE                    mSpriteHandler;
    Camera                          *mCamera;
	Player							*mPlayer;
    QuadTree                        *mQuadTree;
    std::vector<Item*>				mListItems;
	std::vector<Oroku*>             mListOrokus;
	std::vector<Entity*>			mListUpStairs;
	std::vector<Entity*>			mListDownStairs;
};

#endif

