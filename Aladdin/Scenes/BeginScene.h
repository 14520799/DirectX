#pragma once

#include <math.h>
#include <vector>
#include <d3dx9.h>
#include <d3d9.h>

#include "../GameComponents/Scene.h"
#include "../GameComponents/Sprite.h"
#include "../GameComponents/Animation.h"
#include "../GameComponents/Sound.h"

class BeginScene : public Scene
{
public:
	BeginScene();
	~BeginScene();

	void Update(float dt);
	void LoadContent();
	void Draw();

	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	void OnMouseDown(float x, float y);

protected:
	Animation *mCurrentImage;
	int hinh;

	float timeTranslateImage; //time tu chuyen hinh
	float timeTranslate;//khi chuyen hinh thi se co 1 time man hinh den

	std::map<int, bool> keys;
};