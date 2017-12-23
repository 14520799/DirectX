#include "VictoryScene.h"
#include "../GameControllers/SceneManager.h"
#include "../Scenes/BeginScene.h"

VictoryScene::VictoryScene(Player *player)
{
	LoadContent(player);
}

VictoryScene::~VictoryScene()
{

}

void VictoryScene::LoadContent(Player *player)
{
	//set mau backcolor cho scene o day la mau xanh
	mBackColor = D3DCOLOR_XRGB(0, 0, 0);

	Sound::getInstance()->loadSound("Resources/Sounds/MusicScene/BeginEndGame.wav", "BeginEndGame");
	Sound::getInstance()->play("BeginEndGame", true, 0);
	Sound::getInstance()->setVolume(100, "BeginEndGame");

	mPlayer = player;
	mPlayer->SetPosition(0, 220);

	mMoonImage = new Animation("Resources/VictoryScene/1.PNG", 1, 1, 1, 0.0f);
	mTheEndImage = new Animation("Resources/VictoryScene/2.PNG", 1, 1, 1, 0.0f);
	timeTranslate = 0.5f;
}

void VictoryScene::Update(float dt)
{
	timeTranslate += dt;
	if (mPlayer->mCurrentState == PlayerState::MoveMoon)
		mMoonImage->Update(dt);
	else if (mPlayer->allowShowTheEnd)
	{
		if (mMoonImage != nullptr)
		{
			delete mMoonImage;
			mMoonImage = nullptr;
		}
		mTheEndImage->Update(dt);
	}
	mPlayer->Update(dt);
}

void VictoryScene::Draw()
{
	if (timeTranslate > 0.5f)
	{
		if (mPlayer->mCurrentState == PlayerState::MoveMoon)
		{
			mMoonImage->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
			mMoonImage->Draw();
			mPlayer->Draw(mPlayer->GetPosition());
		}
		else if (mPlayer->mCurrentState == PlayerState::Scene18Plus || mPlayer->mCurrentState == PlayerState::Scene18PlusStop)
		{
			if (mPlayer->allowShowTheEnd)
			{
				mTheEndImage->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
				mTheEndImage->Draw();
			}
			mPlayer->SetPosition(495, 245);
			mPlayer->Draw(mPlayer->GetPosition());
		}
	}

	if(timeTranslate > 8 && mPlayer->mCurrentState != PlayerState::Scene18PlusStop)
		timeTranslate = 0;
}

void VictoryScene::OnKeyDown(int keyCode)
{
	keys[keyCode] = true;
}

void VictoryScene::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;
}

void VictoryScene::OnMouseDown(float x, float y)
{

}