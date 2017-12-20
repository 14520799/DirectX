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

class CompleteScene : public Scene
{
public:
	CompleteScene(Player *player, int scene);
	~CompleteScene();

	void Update(float dt);
	void LoadContent(Player *player, int scene);
	void Draw();

	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	void OnMouseDown(float x, float y);

protected:
	Player *mPlayer;
	int mScene;//xac dinh xem aladdin da qua duoc scene nao

	Animation *mCurrentImage;

	float timeTranslateImage; //time tu chuyen hinh
	float timeTranslate;//khi chuyen hinh thi se co 1 time man hinh den

	bool nextScene;

	std::map<int, bool> keys;
};