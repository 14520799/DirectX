#pragma once

#include <math.h>
#include <vector>
#include <d3dx9.h>
#include <d3d9.h>

#include "../GameComponents/Scene.h"
#include "../GameComponents/Sprite.h"
#include "../GameComponents/Animation.h"
#include "../GameComponents/GameMap.h"
#include "../GameComponents/Camera.h"
#include "../GameObjects/Player/Player.h"
#include "../GameObjects/Orokus/Oroku.h"
#include "../GameComponents/Sound.h"

class Scene1 : public Scene
{
public:
	Scene1();
	~Scene1();

    void Update(float dt);
    void LoadContent();
    void Draw();

    void OnKeyDown(int keyCode);
    void OnKeyUp(int keyCode);
    void OnMouseDown(float x, float y);

protected:
    void checkCollision();
    void CheckCameraAndWorldMap();

    GameMap *mMap;
    Camera	*mCamera;
    Player	*mPlayer;

    std::map<int, bool> keys;
	std::vector<Entity*> mCollidable;

	RECT mCameraExpand;
};

