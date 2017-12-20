#include "BeginScene.h"
#include "../GameControllers/SceneManager.h"
#include "../Scenes/Scene1.h"

BeginScene::BeginScene()
{
	LoadContent();
}

BeginScene::~BeginScene()
{

}

void BeginScene::LoadContent()
{
	//set mau backcolor cho scene o day la mau xanh
	mBackColor = D3DCOLOR_XRGB(0, 0, 0);

	//Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/AGMusicEndCredits.wav", "AGMusicEndCredits");
	//Sound::getInstance()->play("AGMusicEndCredits", true, 0);

	mCurrentImage = new Animation("Resources/BeginScene/1.PNG", 1, 1, 1, 0.0f);
	hinh = 1;
	timeTranslate = 0.5f;
	timeTranslateImage = 0;
}

void BeginScene::Update(float dt)
{
	timeTranslate += dt;
	timeTranslateImage += dt;
	if (timeTranslateImage > 1.5f && hinh != 1)
		OnKeyDown(VK_RETURN);
	mCurrentImage->Update(dt);

	if (hinh == 11 && timeTranslate > 0.5f)
	{
		delete mCurrentImage;
		mCurrentImage = nullptr;
		SceneManager::GetInstance()->ReplaceScene(new Scene1());
	}
}

void BeginScene::Draw()
{
	if (timeTranslate > 0.5f)
	{
		mCurrentImage->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
		mCurrentImage->Draw();
	}
}

void BeginScene::OnKeyDown(int keyCode)
{
	keys[keyCode] = true;

	if (timeTranslate > 0.5f)
	{
		if (keyCode == VK_RETURN)
		{
			timeTranslateImage = 0;
			switch (hinh)
			{
			case 1:
				delete mCurrentImage;
				mCurrentImage = new Animation("Resources/BeginScene/2.PNG", 1, 1, 1, 0.0f);
				timeTranslate = 0;
				hinh = 2;
				break;
			case 2:
				delete mCurrentImage;
				mCurrentImage = new Animation("Resources/BeginScene/3.PNG", 1, 1, 1, 0.0f);
				hinh = 3;
				break;
			case 3:
				delete mCurrentImage;
				mCurrentImage = new Animation("Resources/BeginScene/4.PNG", 1, 1, 1, 0.0f);
				timeTranslate = 0;
				hinh = 4;
				break;
			case 4:
				delete mCurrentImage;
				mCurrentImage = new Animation("Resources/BeginScene/5.PNG", 1, 1, 1, 0.0f);
				hinh = 5;
				break;
			case 5:
				delete mCurrentImage;
				mCurrentImage = new Animation("Resources/BeginScene/6.PNG", 1, 1, 1, 0.0f);
				hinh = 6;
				break;
			case 6:
				delete mCurrentImage;
				mCurrentImage = new Animation("Resources/BeginScene/7.PNG", 1, 1, 1, 0.0f);
				hinh = 7;
				break;
			case 7:
				delete mCurrentImage;
				mCurrentImage = new Animation("Resources/BeginScene/8.PNG", 1, 1, 1, 0.0f);
				hinh = 8;
				break;
			case 8:
				delete mCurrentImage;
				mCurrentImage = new Animation("Resources/BeginScene/9.PNG", 1, 1, 1, 0.0f);
				hinh = 9;
				break;
			case 9:
				delete mCurrentImage;
				mCurrentImage = new Animation("Resources/BeginScene/10.PNG", 1, 1, 1, 0.0f);
				timeTranslate = 0;
				hinh = 10;
				break;
			case 10:
				timeTranslate = 0;
				hinh = 11;
				break;
			default:
				break;
			}
		}
	}
}

void BeginScene::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;
}

void BeginScene::OnMouseDown(float x, float y)
{

}

