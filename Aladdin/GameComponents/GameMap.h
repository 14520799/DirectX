#pragma once
#ifndef __GAME_MAP__
#define __GAME_MAP__

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "../GameComponents/Sprite.h"
#include "../MapReader/Tmx.h.in"
#include "Camera.h"
#include "GameGlobal.h"
#include "GameCollision.h"
#include "QuadTree.h"
#include "../GameObjects/MapObjects/Brick.h"
#include "../GameObjects/Boss/Boss.h"

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
	void createApple(std::vector<Brick*> &entitiesOut, D3DXVECTOR3 position, int soTang);
	void createGuard(std::vector<Boss*> &entitiesOut, D3DXVECTOR3 position, int guardType);
    bool IsBoundLeft(); //kiem tra luc nay Camera o vi bien ben trai so voi WorldMap
    bool IsBoundRight(); // kiem tra xem co o vi tri bien ben phai worldmap khong
    bool IsBoundTop(); // kiem tra xem co o vi tri bien ben trai worldmap khong
    bool IsBoundBottom(); // kiem tra xem co o vi tri bien ben phai worldmap khong
    ~GameMap();

	void SetListBrick(std::vector<Brick*> listBricks);
    std::vector<Brick*> GetListBrick();

	void SetListGuard(std::vector<Boss*> listGuards);
	std::vector<Boss*> GetListGuard();

	Brick* GetBrick(std::vector<Brick*> entitiesIn, Brick *brick);
	Boss* GetBoss(std::vector<Boss*> entitiesIn, Boss *boss);
	std::vector<Brick*> RemoveBrick(std::vector<Brick*> &entitiesIn, Brick *brick);

    QuadTree* GetQuadTree();

private:
    void LoadMap(char* filePath);

    Tmx::Map                        *mMap;
    std::map<int, Sprite*>          mListTileset;
    LPD3DXSPRITE                    mSpriteHandler;
    Camera                          *mCamera;
    QuadTree                        *mQuadTree;
    std::vector<Brick*>             mListBricks;
	std::vector<Boss*>              mListGuards;

    Sprite                          *mSpriteBricks, *mSpriteBrickGold;
};

#endif

