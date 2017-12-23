#include "CompleteScene.h"
#include "../GameControllers/SceneManager.h"
#include "Scene2.h"
#include "VictoryScene.h"

CompleteScene::CompleteScene(Player *player, int scene)
{
	LoadContent(player, scene);
}

CompleteScene::~CompleteScene()
{

}

void CompleteScene::LoadContent(Player *player, int scene)
{
	//set mau backcolor cho scene o day la mau xanh
	mBackColor = D3DCOLOR_XRGB(0, 0, 0);

	Sound::getInstance()->loadSound("Resources/Sounds/MusicScene/LevelComplete.wav", "LevelComplete");
	Sound::getInstance()->play("LevelComplete", true, 0);
	Sound::getInstance()->setVolume(100, "LevelComplete");

	mPlayer = player;
	delete mPlayer->mCamera;
	mPlayer->mCamera = nullptr;
	mScene = scene;

	mPlayer->mLevelComplete = true;
	mPlayer->SetPosition(800, 420);

	mCurrentImage = new Animation("Resources/CompleteScene/1.PNG", 1, 1, 1, 0.0f);
	timeTranslate = 0.5f;
	timeTranslateImage = 0;
}

void CompleteScene::Update(float dt)
{
	timeTranslate += dt;
	timeTranslateImage += dt;
	mCurrentImage->Update(dt);
	mPlayer->Update(dt);
	if (timeTranslateImage > 5.0f)
	{
		timeTranslate = 0;
		timeTranslateImage = 0;
		nextScene = true;
	}

	if (mScene == 1)
	{
		if (timeTranslate > 0.5f && nextScene)
		{
			delete mCurrentImage;
			mCurrentImage = nullptr;
			Sound::getInstance()->stop("LevelComplete");
			SceneManager::GetInstance()->ReplaceScene(new Scene2(mPlayer));
		}
	}
	else if (mScene == 2)
	{
		if (timeTranslate > 0.5f && nextScene)
		{
			delete mCurrentImage;
			mCurrentImage = nullptr;
			Sound::getInstance()->stop("LevelComplete");
			SceneManager::GetInstance()->ReplaceScene(new VictoryScene(mPlayer));
		}
	}
}

void CompleteScene::Draw()
{
	if (timeTranslate > 0.5f)
	{
		mCurrentImage->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
		mCurrentImage->Draw();
		mPlayer->Draw();
	}
}

void CompleteScene::OnKeyDown(int keyCode)
{
	keys[keyCode] = true;
}

void CompleteScene::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;
}

void CompleteScene::OnMouseDown(float x, float y)
{

}