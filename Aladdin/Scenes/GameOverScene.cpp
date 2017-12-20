#include "GameOverScene.h"
#include "../GameControllers/SceneManager.h"
#include "../Scenes/BeginScene.h"

GameOverScene::GameOverScene()
{
	LoadContent();
}

GameOverScene::~GameOverScene()
{

}

void GameOverScene::LoadContent()
{
	//set mau backcolor cho scene o day la mau xanh
	mBackColor = D3DCOLOR_XRGB(0, 0, 0);

	//Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/AGMusicEndCredits.wav", "AGMusicEndCredits");
	//Sound::getInstance()->play("AGMusicEndCredits", true, 0);

	mCurrentImage = new Animation("Resources/GameOverScene/1.PNG", 1, 1, 1, 0.0f);
	timeTranslate = 0;
}

void GameOverScene::Update(float dt)
{
	timeTranslate += dt;
	mCurrentImage->Update(dt);
}

void GameOverScene::Draw()
{
	if (timeTranslate > 0.5f)
	{
		mCurrentImage->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
		mCurrentImage->Draw();
	}
}

void GameOverScene::OnKeyDown(int keyCode)
{
	keys[keyCode] = true;

	if (keyCode == VK_LEFT || keyCode == VK_RIGHT)
	{
		delete mCurrentImage;
		mCurrentImage = nullptr;
		SceneManager::GetInstance()->ReplaceScene(new BeginScene());
	}
}

void GameOverScene::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;
}

void GameOverScene::OnMouseDown(float x, float y)
{

}