#pragma once

#include <math.h>
#include <vector>
#include <d3dx9.h>
#include <d3d9.h>

#include "../GameComponents/Scene.h"
#include "../GameComponents/Sprite.h"
#include "../GameComponents/Animation.h"
#include "../GameComponents/Sound.h"
#include "../GameObjects/Player/Player.h"

class GameOverScene : public Scene
{
public:
	//GameOverScene(Player *player);
	GameOverScene();
	~GameOverScene();

	void Update(float dt);
	//void LoadContent(Player *player);
	void LoadContent();
	void Draw();

	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	void OnMouseDown(float x, float y);

protected:
	//Player *mPlayer;

	Animation *mCurrentImage;

	float timeTranslate;//khi chuyen hinh thi se co 1 time man hinh den

	std::map<int, bool> keys;
};