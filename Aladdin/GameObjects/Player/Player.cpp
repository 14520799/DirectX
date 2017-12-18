#include "Player.h"
#include "PlayerDeathState.h"
#include "PlayerDefaultState.h"
#include "PlayerRunningState.h"
#include "PlayerRunningStopState.h"
#include "PlayerFallingState.h"
#include "PlayerFallingStopState.h"
#include "PlayerStandingState.h"
#include "PlayerStandingUpState.h"
#include "PlayerStandingUpStopState.h"
#include "PlayerSittingState.h"
#include "PlayerPushingState.h"
#include "PlayerVerticalClimbingState.h"
#include "PlayerVerticalClimbingDefaultState.h"
#include "PlayerVerticalClimbingJumpState.h"
#include "PlayerHorizontalClimbingState.h"
#include "PlayerHorizontalClimbingDefaultState.h"
#include "PlayerStandingJumpState.h"
#include "PlayerRunningJumpState.h"
#include "PlayerStandingAttackState.h"
#include "PlayerSittingAttackState.h"
#include "PlayerJumpingAttackState.h"
#include "PlayerClimbingAttackState.h"
#include "PlayerStandingThrowAppleState.h"
#include "PlayerSittingThrowAppleState.h"
#include "PlayerJumpingThrowAppleState.h"
#include "PlayerClimbingThrowAppleState.h"
#include "PlayerRevivalState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"
#include "../../GameObjects/MapObjects/Weapons/AppleWeaponEffect.h"
#include "../../GameObjects/MapObjects/Weapons/AppleWeaponEffectBoss.h"
#include "../../GameComponents/Sound.h"

Player::Player()
{
	mAnimationDefault = new Animation("Resources/Aladdin/Default/Default.png", 1, 1, 1, 0.0f);
	mAnimationStandingUpStop = new Animation("Resources/Aladdin/Standing/StandingUpStop.png", 1, 1, 1, 0.0f);
	mAnimationFalling = new Animation("Resources/Aladdin/Falling/Falling.png", 1, 1, 1, 0.0f);
	mAnimationSitting = new Animation("Resources/Aladdin/Sitting/Sitting.png", 1, 1, 1, 0.0f);
	mAnimationVerticalClimbingDefault = new Animation("Resources/Aladdin/Climbing/VerticalClimbing/VerticalClimbingDefault.png", 1, 1, 1, 0.0f);

	AppleInfo = new Animation("Resources/AladdinInfo/AppleInfo.png", 1, 1, 1, 0.0f);
	AppleInfoPos = D3DXVECTOR3(GameGlobal::GetWidth() / 2 - 30, GameGlobal::GetHeight() / 2 - 30, 0);
	RubyInfo = new Animation("Resources/AladdinInfo/RubyInfo.png", 1, 1, 1, 0.0f);
	RubyInfoPos = D3DXVECTOR3(GameGlobal::GetWidth() / 2 - 80, GameGlobal::GetHeight() / 2 - 30, 0);
	LifeInfo = new Animation("Resources/AladdinInfo/LifeInfo.png", 1, 1, 1, 0.0f);
	LifeInfoPos = D3DXVECTOR3(40, GameGlobal::GetHeight() / 2 - 30, 0);

	mLifePlayer = 3;
	mScorePlayer = 0;
	mRubyPlayer = 0;

	TxtScore = new Text(L"0", 50, 200, 50, false, D3DCOLOR_XRGB(202, 229, 232));
	TxtApple = new Text(L"0", 30, 90, 30, false, D3DCOLOR_XRGB(202, 229, 232));
	TxtRuby = new Text(L"0", 30, 60, 30, false, D3DCOLOR_XRGB(202, 229, 232));
	TxtLife = new Text(L"0", 40, 80, 40, false, D3DCOLOR_XRGB(202, 229, 232));

	this->Tag = Entity::EntityTypes::Aladdin;
	this->CurrentMoveStairs = Entity::EntityCurrentMoveStairs::CurrentGround;

	this->mPlayerData = new PlayerData();
	this->mPlayerData->player = this;

	InitPlayer();
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	if (this->mCurrentState == PlayerState::Revival || this->mCurrentState == PlayerState::Death)
	{
		mCurrentAnimation->Update(dt);
		if (this->mPlayerData->state)
		{
			this->mPlayerData->state->Update(dt);
			return;
		}
	}

	//xu ly player bi mat mau va chuyen sang state bi thuong
	if (this->preBloodOfEntity != this->bloodOfEntity && this->bloodOfEntity >= 0)
	{
		Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/AladdinHurt.wav", "AladdinHurt");
		Sound::getInstance()->play("AladdinHurt", false, 1);
		this->preBloodOfEntity = this->bloodOfEntity;
		allowImunity = true;
		demHurting = 0;
		switch (bloodOfEntity)
		{
		case 9:
			delete BloodInfo;
			BloodInfo = new Animation("Resources/AladdinInfo/BloodInfo_9.png", 4, 1, 4, 0.1f);
			break;
		case 8:
			delete BloodInfo;
			BloodInfo = new Animation("Resources/AladdinInfo/BloodInfo_8.png", 4, 1, 4, 0.1f);
			break;
		case 7:
			delete BloodInfo;
			BloodInfo = new Animation("Resources/AladdinInfo/BloodInfo_7.png", 4, 1, 4, 0.1f);
			break;
		case 6:
			delete BloodInfo;
			BloodInfo = new Animation("Resources/AladdinInfo/BloodInfo_6.png", 4, 1, 4, 0.1f);
			break;
		case 5:
			delete BloodInfo;
			BloodInfo = new Animation("Resources/AladdinInfo/BloodInfo_5.png", 4, 1, 4, 0.1f);
			break;
		case 4:
			delete BloodInfo;
			BloodInfo = new Animation("Resources/AladdinInfo/BloodInfo_4.png", 4, 1, 4, 0.1f);
			break;
		case 3:
			delete BloodInfo;
			BloodInfo = new Animation("Resources/AladdinInfo/BloodInfo_3.png", 4, 1, 4, 0.1f);
			break;
		case 2:
			delete BloodInfo;
			BloodInfo = new Animation("Resources/AladdinInfo/BloodInfo_2.png", 4, 1, 4, 0.1f);
			break;
		case 1:
			delete BloodInfo;
			BloodInfo = new Animation("Resources/AladdinInfo/BloodInfo_1.png", 4, 1, 4, 0.1f);
			break;
		case 0:
			delete BloodInfo;
			BloodInfo = new Animation("Resources/AladdinInfo/BloodInfo_0.png", 4, 1, 4, 0.1f);
			break;
		default:
			break;
		}
	}

	//animation cua player chay
	BloodInfo->Update(dt);
	mCurrentAnimation->Update(dt);

	//them toc do cho player tuy vao state
	if (this->mPlayerData->state)
	{
		this->mPlayerData->state->Update(dt);
	}

	//player di chuyen sau khi tang toc do
	this->Entity::Update(dt);

	//neu qua tao bay trung vao oroku thi qua tao se bien mat
	if (mListAppleFly.size() > 0)
	{
		for (size_t i = 0; i < mListAppleFly.size(); i++)
		{
			if (mListAppleFly.at(i)->collisionWithOroku || mListAppleFly.at(i)->weaponCollided)
			{
				//them hieu ung apple effect vao list tai vi tri qua tao trung oroku
				appleEffect = new AppleWeaponEffect(mListAppleFly.at(i)->GetPosition());
				mListAppleEffect.push_back(appleEffect);
				delete mListAppleFly.at(i);
				mListAppleFly.at(i) = nullptr;
				mListAppleFly.erase(mListAppleFly.begin() + i);
				if (mListAppleFly.size() == 0)
					break;
				i--;
			}
			else if (mListAppleFly.at(i)->collisionWithBoss)
			{
				//them hieu ung apple effect vao list tai vi tri qua tao trung oroku
				appleEffect = new AppleWeaponEffectBoss(mListAppleFly.at(i)->GetPosition());
				mListAppleEffect.push_back(appleEffect);
				delete mListAppleFly.at(i);
				mListAppleFly.at(i) = nullptr;
				mListAppleFly.erase(mListAppleFly.begin() + i);
				if (mListAppleFly.size() == 0)
					break;
				i--;
			}
		}
	}

	//chay animation cua effect apple roi tu huy
	for (size_t i = 0; i < mListAppleEffect.size(); i++)
	{
		mListAppleEffect.at(i)->Update(dt);
		mListAppleEffect.at(i)->timeDelayWeaponEffect += dt;
		if (mListAppleEffect.at(i)->timeDelayWeaponEffect > 0.5f)
		{
			delete mListAppleEffect.at(i);
			mListAppleEffect.at(i) = nullptr;
			mListAppleEffect.erase(mListAppleEffect.begin() + i);
			if (mListAppleEffect.size() == 0)
				break;
			i--;
		}

	}

	// neu list co qua tao dang duoc nem di thi set toc do cho qua tao
	if (mListAppleFly.size() > 0)
	{
		for (size_t i = 0; i < mListAppleFly.size(); i++)
		{
			if (mCurrentState == PlayerState::ClimbingThrowApple)
			{
				if (!mCurrentReverse)
				{
					//bay sang ben trai
					SetAppleFlyLeft(mListAppleFly, mListAppleFly.at(i), i, dt);
				}
				else
				{
					//bay sang ben phai
					SetAppleFlyRight(mListAppleFly, mListAppleFly.at(i), i, dt);
				}
			}
			else
			{
				//khi qua tao bay theo huong nao thi no se bay theo huong do, no se khong doi huong theo huong cua player nua
				//vd: khi player huong sang ben trai nem tao thi qua tao se bay sang ben trai cho du sau do minh co doi huong cua player sang ben phai
				if (mCurrentReverse)
				{
					//bay sang ben trai
					SetAppleFlyLeft(mListAppleFly, mListAppleFly.at(i), i, dt);
				}
				else
				{
					//bay sang ben phai
					SetAppleFlyRight(mListAppleFly, mListAppleFly.at(i), i, dt);
				}
			}
		}
	}

	//state phai duoc thuc hien xong moi chuyen sang state khac sau khi tha phim ra
	if (allowDelayState)
	{
		switch (mCurrentState)
		{
		case PlayerState::Default:
			timeDelayStates += dt;
			if (timeDelayStates > 2.0f)
				this->SetState(new PlayerStandingState(this->mPlayerData));
			break;

		case PlayerState::StandingAttack:
			timeDelayStates += dt;
			if (timeDelayStates > 0.15f)
				this->SetState(new PlayerDefaultState(this->mPlayerData));
			break;

		case PlayerState::SittingAttack:
			timeDelayStates += dt;
			if (timeDelayStates > 0.2f)
				this->SetState(new PlayerSittingState(this->mPlayerData));
			break;

		case PlayerState::JumpingAttack:
			timeDelayStates += dt;
			if (timeDelayStates > 0.19f)
				this->SetState(new PlayerFallingState(this->mPlayerData));
			break;

		case PlayerState::ClimbingAttack:
			timeDelayStates += dt;
			if (timeDelayStates > 0.2f)
				//xem state truoc dang la leo day ngang hay doc de tro ve state default
				if (mPreCurrentState == PlayerState::VerticalClimbing || mPreCurrentState == PlayerState::VerticalClimbingDefault)
					this->SetState(new PlayerVerticalClimbingDefaultState(this->mPlayerData));
				else if (mPreCurrentState == PlayerState::HorizontalClimbing || mPreCurrentState == PlayerState::HorizontalClimbingDefault)
					this->SetState(new PlayerHorizontalClimbingDefaultState(this->mPlayerData));
			break;

		case PlayerState::StandingThrowApple:
			timeDelayStates += dt;
			if (timeDelayStates > 0.2f)
				this->SetState(new PlayerDefaultState(this->mPlayerData));
			break;

		case PlayerState::SittingThrowApple:
			timeDelayStates += dt;
			if (timeDelayStates > 0.17f)
				this->SetState(new PlayerSittingState(this->mPlayerData));
			break;

		case PlayerState::JumpingThrowApple:
			timeDelayStates += dt;
			if (timeDelayStates > 0.17f)
				this->SetState(new PlayerFallingState(this->mPlayerData));
			break;

		case PlayerState::ClimbingThrowApple:
			timeDelayStates += dt;
			if (timeDelayStates > 0.2f)
				if (mPreCurrentState == PlayerState::VerticalClimbing || mPreCurrentState == PlayerState::VerticalClimbingDefault)
					this->SetState(new PlayerVerticalClimbingDefaultState(this->mPlayerData));
				else if (mPreCurrentState == PlayerState::HorizontalClimbing || mPreCurrentState == PlayerState::HorizontalClimbingDefault)
					this->SetState(new PlayerHorizontalClimbingDefaultState(this->mPlayerData));
			break;

		default:
			break;
		}
	}

	//duoc mien sat thuong sau khi bi trung don
	if (allowImunity)
	{
		timeImunity += dt;

		if (timeImunity > 2.0f)
		{
			allowImunity = false;
			timeImunity = 0;
		}
	}

	//hoi sinh player
	if (bloodOfEntity < 0 && mLifePlayer > 0)
	{
		mLifePlayer--;
		this->SetState(new PlayerDeathState(this->mPlayerData));
	}

	//ve text
	TxtScore->SetString(mScorePlayer);
	TxtRuby->SetString(mRubyPlayer);
	TxtLife->SetString(mLifePlayer);
	TxtApple->SetString(mListApplePlayer.size());

}

void Player::InitPlayer()
{
	if(collisionRevitalization)
		this->SetPosition(this->mRevivalPosition);
	else
		this->SetPosition(this->mOriginPosition);

	this->bloodOfEntity = Define::ALADDIN_BLOOD;
	this->preBloodOfEntity = this->bloodOfEntity;
	delete BloodInfo;
	BloodInfo = new Animation("Resources/AladdinInfo/BloodInfo_10.png", 4, 1, 4, 0.1f);
	BloodInfoPos = D3DXVECTOR3(90, 20, 0);
	this->vx = 0;
	this->vy = 0;
	this->SetState(new PlayerDefaultState(this->mPlayerData));

	allowJump = true;
	allowDelayState = true;
	timeImunity = 0;
	timeDelayStates = 0;
	timeDelayForFalling = 0;
	demHurting = 0;
}

void Player::SetAppleFlyLeft(std::vector<MapObject*> &listAppleFly, MapObject *item, int i, float dt)
{
	//khi di chuyen player sang trai ma apple da duoc nem sang phai thi no se van bay sang phai
	if (item->mSettingRightItem)
	{
		item->AddVx(Define::ITEM_SPEED_X);
		if (item->GetVy() <= Define::ITEM_MIN_VELOCITY || item->DirectionDown)
		{
			item->AddVy(Define::ITEM_SPEED_Y);
			item->DirectionDown = true;
		}
		else if(item->GetVy() > Define::ITEM_MIN_VELOCITY)
			item->AddVy(-Define::ITEM_SPEED_Y);
		item->Entity::Update(dt);
		return;
	}
	item->mSettingLeftItem = true;
	item->AddVx(-Define::ITEM_SPEED_X);
	if (item->GetVy() <= Define::ITEM_MIN_VELOCITY || item->DirectionDown)
	{
		item->AddVy(Define::ITEM_SPEED_Y);
		item->DirectionDown = true;
	}
	else if (item->GetVy() > Define::ITEM_MIN_VELOCITY)
		item->AddVy(-Define::ITEM_SPEED_Y);
	item->Entity::Update(dt);
}

void Player::SetAppleFlyRight(std::vector<MapObject*> &listAppleFly, MapObject *item, int i, float dt)
{
	//khi di chuyen player sang phai ma apple da duoc nem sang trai thi no se van bay sang trai
	if (item->mSettingLeftItem)
	{
		item->AddVx(-Define::ITEM_SPEED_X);
		if (item->GetVy() <= Define::ITEM_MIN_VELOCITY || item->DirectionDown)
		{
			item->AddVy(Define::ITEM_SPEED_Y);
			item->DirectionDown = true;
		}
		else if (item->GetVy() > Define::ITEM_MIN_VELOCITY)
			item->AddVy(-Define::ITEM_SPEED_Y);
		item->Entity::Update(dt);
		return;
	}
	item->mSettingRightItem = true;
	item->AddVx(Define::ITEM_SPEED_X);
	if (item->GetVy() <= Define::ITEM_MIN_VELOCITY || item->DirectionDown)
	{
		item->AddVy(Define::ITEM_SPEED_Y);
		item->DirectionDown = true;
	}
	else if (item->GetVy() > Define::ITEM_MIN_VELOCITY)
		item->AddVy(-Define::ITEM_SPEED_Y);
	item->Entity::Update(dt);
}

std::vector<MapObject*> Player::GetListAppleFly()
{
	return mListAppleFly;
}

void Player::HandleKeyboard(std::map<int, bool> keys)
{
	if (this->mPlayerData->state)
	{
		this->mPlayerData->state->HandleKeyboard(keys);
	}
}

void Player::OnKeyPressed(int key)
{
	if (key == VK_SPACE)
	{
		if (allowJump)
		{
			if (mCurrentState == PlayerState::Standing || mCurrentState == PlayerState::Sitting || mCurrentState == PlayerState::Default ||
				mCurrentState == PlayerState::StandingAttack || mCurrentState == PlayerState::SittingAttack ||
				mCurrentState == PlayerState::StandingThrowApple || mCurrentState == PlayerState::SittingThrowApple ||
				mCurrentState == PlayerState::Pushing ||
				mCurrentState == PlayerState::Falling || mCurrentState == PlayerState::FallingStop ||
				mCurrentState == PlayerState::HorizontalClimbing || mCurrentState == PlayerState::HorizontalClimbingDefault)
			{
				this->SetState(new PlayerStandingJumpState(this->mPlayerData));
			}
			else if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::RunningStop)
			{
				this->SetState(new PlayerRunningJumpState(this->mPlayerData));
			}
			else if (mCurrentState == PlayerState::VerticalClimbingDefault || mCurrentState == PlayerState::VerticalClimbing)
			{
				this->SetState(new PlayerVerticalClimbingJumpState(this->mPlayerData));
			}
			allowJump = false;
		}
	}
	else if (key == VK_DOWN)
	{
		if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::RunningStop || mCurrentState == PlayerState::Default ||
			mCurrentState == PlayerState::Standing || mCurrentState == PlayerState::StandingAttack || mCurrentState == PlayerState::StandingThrowApple ||
			mCurrentState == PlayerState::Pushing)
		{
			this->SetState(new PlayerSittingState(this->mPlayerData));
		}
		if (mCurrentState == PlayerState::HorizontalClimbingDefault || mCurrentState == PlayerState::HorizontalClimbing)
		{
			this->onKeyDownPressing = true;
			this->SetState(new PlayerHorizontalClimbingDefaultState(this->mPlayerData));
		}
	}
	else if (key == VK_UP)
	{
		if (mCurrentState == PlayerState::Default || mCurrentState == PlayerState::Standing)
		{
			this->onKeyUpPressing = true;
			this->SetState(new PlayerStandingUpState(this->mPlayerData));
		}
		else if (mCurrentState == PlayerState::HorizontalClimbingDefault || mCurrentState == PlayerState::HorizontalClimbing)
		{
			this->onKeyUpPressing = true;
			this->SetState(new PlayerHorizontalClimbingDefaultState(this->mPlayerData));
		}
	}
	else if (key == 0x41) //tan cong bang phim A
	{
		Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/LowSword.wav", "LowSword");
		Sound::getInstance()->play("LowSword", false, 1);
		if (mCurrentState == PlayerState::Standing || mCurrentState == PlayerState::Running || mCurrentState == PlayerState::RunningStop ||
			mCurrentState == PlayerState::Default || mCurrentState == PlayerState::StandingThrowApple || mCurrentState == PlayerState::Pushing)
		{
			this->SetState(new PlayerStandingAttackState(this->mPlayerData));
		}
		else if (mCurrentState == PlayerState::Sitting || mCurrentState == PlayerState::SittingThrowApple)
		{
			this->SetState(new PlayerSittingAttackState(this->mPlayerData));
		}
		else if (mCurrentState == PlayerState::StandingJump || mCurrentState == PlayerState::RunningJump ||
			mCurrentState == PlayerState::JumpingThrowApple || mCurrentState == PlayerState::Falling ||
			mCurrentState == PlayerState::VerticalClimbingJump)
		{
			this->SetState(new PlayerJumpingAttackState(this->mPlayerData));
		}
		else if (mCurrentState == PlayerState::HorizontalClimbingDefault || mCurrentState == PlayerState::HorizontalClimbing ||
			mCurrentState == PlayerState::VerticalClimbingDefault || mCurrentState == PlayerState::VerticalClimbing)
		{
			this->SetState(new PlayerClimbingAttackState(this->mPlayerData));
		}
	}
	else if (key == 0x53) //tan cong bang phim S
	{
		//khi an phim s thi qua tao se bay ra
		if (mListApplePlayer.size() > 0)
		{
			apple = mListApplePlayer.at(mListApplePlayer.size() - 1);

			if (mCurrentState == PlayerState::Standing || mCurrentState == PlayerState::StandingAttack ||
				mCurrentState == PlayerState::Default || mCurrentState == PlayerState::Running || mCurrentState == PlayerState::RunningStop)
			{
				//set vi tri bay cua qua tao
				this->SetState(new PlayerStandingThrowAppleState(this->mPlayerData));
				if (mCurrentReverse)
					apple->SetPosition(this->GetPosition().x - this->GetWidth() / 2, this->GetPosition().y - this->GetHeight() / 2);
				else
					apple->SetPosition(this->GetPosition().x + this->GetWidth() / 2, this->GetPosition().y - this->GetHeight() / 2);
				mListAppleFly.push_back(apple); //lay ra qua tao trong player roi dua vao listapple quan ly viec bay ra ngoai
				mListApplePlayer.pop_back(); //lay qua tao ra khoi listapple cua player sau khi nem ra ngoai
			}
			else if (mCurrentState == PlayerState::Sitting || mCurrentState == PlayerState::SittingAttack)
			{
				this->SetState(new PlayerSittingThrowAppleState(this->mPlayerData));
				if (mCurrentReverse)
					apple->SetPosition(this->GetPosition().x, this->GetPosition().y - this->GetHeight() / 4);
				else
					apple->SetPosition(this->GetPosition().x, this->GetPosition().y - this->GetHeight() / 4);
				mListAppleFly.push_back(apple); //lay ra qua tao trong player roi dua vao listapple quan ly viec bay ra ngoai
				mListApplePlayer.pop_back(); //lay qua tao ra khoi listapple cua player sau khi nem ra ngoai
			}
			else if (mCurrentState == PlayerState::StandingJump || mCurrentState == PlayerState::RunningJump ||
				mCurrentState == PlayerState::JumpingAttack || mCurrentState == PlayerState::Falling ||
				mCurrentState == PlayerState::VerticalClimbingJump)
			{
				this->SetState(new PlayerJumpingThrowAppleState(this->mPlayerData));
				if (mCurrentReverse)
					apple->SetPosition(this->GetPosition().x - this->GetWidth(), this->GetPosition().y - this->GetHeight() / 2 + 10);
				else
					apple->SetPosition(this->GetPosition().x + this->GetWidth(), this->GetPosition().y - this->GetHeight() / 2 + 10);
				mListAppleFly.push_back(apple); //lay ra qua tao trong player roi dua vao listapple quan ly viec bay ra ngoai
				mListApplePlayer.pop_back(); //lay qua tao ra khoi listapple cua player sau khi nem ra ngoai
			}
			else if (mCurrentState == PlayerState::HorizontalClimbingDefault || mCurrentState == PlayerState::HorizontalClimbing ||
				mCurrentState == PlayerState::VerticalClimbingDefault || mCurrentState == PlayerState::VerticalClimbing)
			{
				this->SetState(new PlayerClimbingThrowAppleState(this->mPlayerData));
				apple->SetPosition(this->GetPosition());
				mListAppleFly.push_back(apple); //lay ra qua tao trong player roi dua vao listapple quan ly viec bay ra ngoai
				mListApplePlayer.pop_back(); //lay qua tao ra khoi listapple cua player sau khi nem ra ngoai
			}

			apple->SetVy(0);
			apple->Tag = Entity::EntityTypes::AppleWeapon;
		}
	}
}

void Player::OnKeyUp(int key)
{
	if (key == VK_SPACE)
	{
		allowJump = true;
	}
	else if (key == VK_DOWN)
	{
		if (mCurrentState == PlayerState::Sitting || mCurrentState == PlayerState::SittingAttack || mCurrentState == PlayerState::SittingThrowApple)
			this->SetState(new PlayerDefaultState(this->mPlayerData));
		else if (this->onKeyDownPressing)
			this->onKeyDownPressing = false;
	}
	else if (key == VK_UP)
	{
		if (mCurrentState == PlayerState::StandingUp || mCurrentState == PlayerState::StandingUpStop)
		{
			if (this->onKeyUpPressing)
			{
				this->onKeyUpPressing = false;
				this->SetState(new PlayerDefaultState(this->mPlayerData));
			}
		}
		else if (mCurrentState == PlayerState::HorizontalClimbingDefault)
		{
			if (this->onKeyUpPressing)
				this->onKeyUpPressing = false;
		}
	}
	else if (key == 0x41 || key == 0x53)
	{
		if (mCurrentState == PlayerState::SittingAttack || mCurrentState == PlayerState::StandingAttack || mCurrentState == PlayerState::ClimbingAttack || mCurrentState == PlayerState::JumpingAttack ||
			mCurrentState == PlayerState::StandingThrowApple || mCurrentState == PlayerState::SittingThrowApple || mCurrentState == PlayerState::JumpingThrowApple || mCurrentState == PlayerState::ClimbingThrowApple)
		{
			allowDelayState = true;
		}
	}
}

void Player::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}

void Player::SetCamera(Camera *camera)
{
	this->mCamera = camera;
}

void Player::SetMap(GameMap *map)
{
	this->mMap = map;
}

void Player::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mCurrentAnimation->FlipVertical(mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());

	if (mCamera)
	{
		D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
			GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);
		//xu ly player bi trung don
		if(allowImunity && timeImunity <= 1.0f)
		{
			if(demHurting % 2 == 0)
			{ }
			else
				mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
			demHurting++;
		}
		else
			//ve player theo state
			mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
		//ve qua tao bay ra
		if (mListAppleFly.size() > 0)
		{
			for (size_t i = 0; i < mListAppleFly.size(); i++)
			{
				mListAppleFly.at(i)->Draw(D3DXVECTOR3(mListAppleFly.at(i)->posX, mListAppleFly.at(i)->posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
			}
		}
		//ve apple effect
		if (mListAppleEffect.size() > 0)
		{
			for (size_t i = 0; i < mListAppleEffect.size(); i++)
			{
				mListAppleEffect.at(i)->Draw(D3DXVECTOR3(mListAppleEffect.at(i)->posX, mListAppleEffect.at(i)->posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
			}
		}

	}
	else
	{
		if (allowImunity && timeImunity <= 1.0f)
		{
			if (demHurting % 2 == 0)
			{
			}
			else
				mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0));
			demHurting++;
		}
		else
			mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0));

		if (mListAppleFly.size() > 0)
		{
			for (size_t i = 0; i < mListAppleFly.size(); i++)
			{
				mListAppleFly.at(i)->Draw(D3DXVECTOR3(mListAppleFly.at(i)->posX, mListAppleFly.at(i)->posY, 0));
			}
		}
		if (mListAppleEffect.size() > 0)
		{
			for (size_t i = 0; i < mListAppleEffect.size(); i++)
			{
				mListAppleEffect.at(i)->Draw(D3DXVECTOR3(mListAppleEffect.at(i)->posX, mListAppleEffect.at(i)->posY, 0));
			}
		}

		BloodInfo->Draw(BloodInfoPos);
		AppleInfo->Draw(AppleInfoPos);
		RubyInfo->Draw(RubyInfoPos);
		LifeInfo->Draw(LifeInfoPos);
	}
}

void Player::SetState(PlayerState *newState)
{
	allowMoveLeft = true;
	allowMoveRight = true;
	allowMoveUp = true;
	allowDelayState = false;
	timeDelayStates = 0;

	delete this->mPlayerData->state;

	this->mPlayerData->state = newState;

	mPreCurrentAnimation = mCurrentAnimation;
	this->changeAnimation(newState->GetState());

	mPreCurrentState = mCurrentState;
	mCurrentState = newState->GetState();

	if (mPreCurrentAnimation != nullptr && mPreCurrentState != PlayerState::HorizontalClimbingDefault)
		this->posY += (mPreCurrentAnimation->GetHeight() - mCurrentAnimation->GetHeight()) / 2;

	if (mCurrentState == PlayerState::Default)
		allowDelayState = true;
}

void Player::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions size)
{
	if (impactor->Tag == Entity::EntityTypes::TranslateScene)
		this->allowTranslateScene = true;

#pragma region TANG SCORE
	if (impactor->Id == Entity::EntityId::AppleItem)
	{
		Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/AppleCollect.wav", "AppleCollect");
		Sound::getInstance()->play("AppleCollect", false, 1);
		mScorePlayer += 15;
	}
	else if (impactor->Id == Entity::EntityId::Ruby)
	{
		Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/AppleCollect.wav", "AppleCollect");
		Sound::getInstance()->play("AppleCollect", false, 1);
		mScorePlayer += 25;
		mRubyPlayer++;
	}
	else if (impactor->Id == Entity::EntityId::HeadGenie)
	{
		Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/Wow!.wav", "Wow!");
		Sound::getInstance()->play("Wow!", false, 1);
		mScorePlayer += 200;
	}
	else if (impactor->Id == Entity::EntityId::Heart)
	{
		Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/Yeah.wav", "Yeah");
		Sound::getInstance()->play("Yeah", false, 1);
		mScorePlayer += 200;
		bloodOfEntity++;
	}
	else if (impactor->Id == Entity::EntityId::Life)
	{
		Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/GemCollect.wav", "GemCollect");
		Sound::getInstance()->play("GemCollect", false, 1);
		mScorePlayer += 100;
		mLifePlayer++;
	}
	else if (impactor->Id == Entity::EntityId::Lamp)
	{
		Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/CloudPoof.wav", "CloudPoof");
		Sound::getInstance()->play("CloudPoof", false, 1);
		mScorePlayer += 50;
	}
	else if (impactor->Id == Entity::EntityId::Revitalization_Default)
		mScorePlayer += 125;
	else if (impactor->Id == Entity::EntityId::Feddler_Standing)
	{
		Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/PeddlerShop.wav", "PeddlerShop");
		Sound::getInstance()->play("PeddlerShop", false, 1);
		mScorePlayer += 500;
	}
#pragma endregion

	if (impactor->Tag == Entity::EntityTypes::Fire)
	{
		Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/FireFromCoal.wav", "FireFromCoal");
		Sound::getInstance()->play("FireFromCoal", false, 1);
		this->mPlayerData->player->effectFire = true;
		this->mPlayerData->player->mOriginPositionItem = D3DXVECTOR3(
			this->mPlayerData->player->GetPosition().x, impactor->GetPosition().y - 55, 0);
	}

	if (impactor->Tag == Entity::EntityTypes::StarWeapon)
	{
		this->mPlayerData->player->collisionStarWeapon = true;
	}
	else if (impactor->Tag == Entity::EntityTypes::FireWeapon)
	{
		this->mPlayerData->player->collisionFireWeapon = true;
	}
	else
		this->mPlayerData->state->OnCollision(impactor, size, data);
}

RECT Player::GetBound()
{
	RECT rect;

	if (mCurrentState == PlayerState::StandingAttack || mCurrentState == PlayerState::ClimbingAttack ||
		mCurrentState == PlayerState::JumpingAttack || mCurrentState == PlayerState::SittingAttack)
	{
		rect.left = this->posX - mCurrentAnimation->GetWidth() / 4;
		rect.right = this->posX + mCurrentAnimation->GetWidth() / 2;
		rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
		rect.bottom = this->posY + mCurrentAnimation->GetHeight() / 2;
	}
	else if (mCurrentState == PlayerState::Sitting || mCurrentState == PlayerState::SittingThrowApple)
	{
		rect.left = this->posX - mCurrentAnimation->GetWidth() / 4;
		rect.right = this->posX + mCurrentAnimation->GetWidth() / 10;
		rect.top = this->posY + mCurrentAnimation->GetHeight() / 4;
		rect.bottom = this->posY + mCurrentAnimation->GetHeight() / 2;
	}
	else if (mCurrentState == PlayerState::RunningJump || mCurrentState == PlayerState::StandingJump || mCurrentState == PlayerState::JumpingThrowApple)
	{
		rect.left = this->posX - mCurrentAnimation->GetWidth() / 4;
		rect.right = this->posX + mCurrentAnimation->GetWidth() / 4;
		rect.top = this->posY - mCurrentAnimation->GetHeight() / 4;
		rect.bottom = this->posY + mCurrentAnimation->GetHeight() / 2;
	}
	else
	{
		rect.left = this->posX - mCurrentAnimation->GetWidth() / 4;
		rect.right = this->posX + mCurrentAnimation->GetWidth() / 4;
		rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;;
		rect.bottom = this->posY + mCurrentAnimation->GetHeight() / 2;
	}

	return rect;
}

bool Player::GetReverse()
{
	return mCurrentReverse;
}

void Player::changeAnimation(PlayerState::StateName state)
{
	switch (state)
	{
	case PlayerState::Default:
		mCurrentAnimation = mAnimationDefault;
		break;

	case PlayerState::Running:
		delete mAnimationRunning;
		mAnimationRunning = new Animation("Resources/Aladdin/Running/Running.png", 13, 1, 13, 0.02f);
		mCurrentAnimation = mAnimationRunning;
		break;

	case PlayerState::RunningStop:
		delete mAnimationRunningStop;
		mAnimationRunningStop = new Animation("Resources/Aladdin/Running/RunningStop.png", 9, 1, 9, 0.02f);
		mCurrentAnimation = mAnimationRunningStop;
		break;

	case PlayerState::RunningJump:
		delete mAnimationRunningJump;
		mAnimationRunningJump = new Animation("Resources/Aladdin/Jumping/RunningJump.png", 4, 1, 4, 0.25f);
		mCurrentAnimation = mAnimationRunningJump;
		break;

	case PlayerState::Somersault:
		delete mAnimationSomersault;
		mAnimationSomersault = new Animation("Resources/Aladdin/Jumping/Somersault.png", 8, 1, 8, 0.1f);
		mCurrentAnimation = mAnimationSomersault;
		break;

	case PlayerState::Standing:
		delete mAnimationStanding;
		mAnimationStanding = new Animation("Resources/Aladdin/Standing/Standing.png", 32, 2, 16, 0.05f);
		mCurrentAnimation = mAnimationStanding;
		break;

	case PlayerState::StandingUp:
		delete mAnimationStandingUp;
		mAnimationStandingUp = new Animation("Resources/Aladdin/Standing/StandingUp.png", 3, 1, 3, 0.1f);
		mCurrentAnimation = mAnimationStandingUp;
		break;

	case PlayerState::StandingUpStop:
		mCurrentAnimation = mAnimationStandingUpStop;
		break;

	case PlayerState::StandingJump:
		delete mAnimationStandingJump;
		mAnimationStandingJump = new Animation("Resources/Aladdin/Jumping/StandingJump.png", 9, 1, 9, 0.2f);
		mCurrentAnimation = mAnimationStandingJump;
		break;

	case PlayerState::Falling:
		mCurrentAnimation = mAnimationFalling;
		break;

	case PlayerState::FallingStop:
		delete mAnimationFallingStop;
		mAnimationFallingStop = new Animation("Resources/Aladdin/Falling/FallingStop.png", 11, 1, 11, 0.02f);
		mCurrentAnimation = mAnimationFallingStop;
		break;

	case PlayerState::Sitting:
		mCurrentAnimation = mAnimationSitting;
		break;

	case PlayerState::Pushing:
		delete mAnimationPushing;
		mAnimationPushing = new Animation("Resources/Aladdin/Pushing/Pushing.png", 9, 1, 9, 0.02f);
		mCurrentAnimation = mAnimationPushing;
		break;

	case PlayerState::VerticalClimbing:
		delete mAnimationVerticalClimbing;
		mAnimationVerticalClimbing = new Animation("Resources/Aladdin/Climbing/VerticalClimbing/VerticalClimbing.png", 10, 1, 10, 0.05f);
		mCurrentAnimation = mAnimationVerticalClimbing;
		break;

	case PlayerState::VerticalClimbingDefault:
		mCurrentAnimation = mAnimationVerticalClimbingDefault;
		break;

	case PlayerState::VerticalClimbingJump:
		delete mAnimationVerticalClimbingJump;
		mAnimationVerticalClimbingJump = new Animation("Resources/Aladdin/Climbing/VerticalClimbing/VerticalClimbingJump.png", 7, 1, 7, 0.2f);
		mCurrentAnimation = mAnimationVerticalClimbingJump;
		break;

	case PlayerState::HorizontalClimbing:
		delete mAnimationHorizontalClimbing;
		mAnimationHorizontalClimbing = new Animation("Resources/Aladdin/Climbing/HorizontalClimbing/HorizontalClimbing.png", 10, 1, 10, 0.05f);
		mCurrentAnimation = mAnimationHorizontalClimbing;
		break;

	case PlayerState::HorizontalClimbingDefault:
		delete mAnimationHorizontalClimbingDefault;
		mAnimationHorizontalClimbingDefault = new Animation("Resources/Aladdin/Climbing/HorizontalClimbing/HorizontalClimbingDefault.png", 5, 1, 5, 0.5f);
		mCurrentAnimation = mAnimationHorizontalClimbingDefault;
		break;

	case PlayerState::StandingAttack:
		delete mAnimationStandingAttack;
		mAnimationStandingAttack = new Animation("Resources/Aladdin/Standing/StandingAttack.png", 5, 1, 5, 0.03f);
		mCurrentAnimation = mAnimationStandingAttack;
		break;

	case PlayerState::SittingAttack:
		delete mAnimationSittingAttack;
		mAnimationSittingAttack = new Animation("Resources/Aladdin/Sitting/SittingAttack.png", 6, 1, 6, 0.02f);
		mCurrentAnimation = mAnimationSittingAttack;
		break;

	case PlayerState::JumpingAttack:
		delete mAnimationJumpingAttack;
		mAnimationJumpingAttack = new Animation("Resources/Aladdin/Jumping/JumpingAttack.png", 5, 1, 5, 0.02f);
		mCurrentAnimation = mAnimationJumpingAttack;
		break;

	case PlayerState::ClimbingAttack:
		delete mAnimationClimbingAttack;
		mAnimationClimbingAttack = new Animation("Resources/Aladdin/Climbing/ClimbingAttack.png", 7, 1, 7, 0.02f);
		mCurrentAnimation = mAnimationClimbingAttack;
		break;

	case PlayerState::StandingThrowApple:
		delete mAnimationStandingThrowApple;
		mAnimationStandingThrowApple = new Animation("Resources/Aladdin/Standing/StandingThrowApple.png", 6, 1, 6, 0.02f);
		mCurrentAnimation = mAnimationStandingThrowApple;
		break;

	case PlayerState::SittingThrowApple:
		delete mAnimationSittingThrowApple;
		mAnimationSittingThrowApple = new Animation("Resources/Aladdin/Sitting/SittingThrowApple.png", 5, 1, 5, 0.03f);
		mCurrentAnimation = mAnimationSittingThrowApple;
		break;

	case PlayerState::JumpingThrowApple:
		delete mAnimationJumpingThrowApple;
		mAnimationJumpingThrowApple = new Animation("Resources/Aladdin/Jumping/JumpingThrowApple.png", 5, 1, 5, 0.03f);
		mCurrentAnimation = mAnimationJumpingThrowApple;
		break;

	case PlayerState::ClimbingThrowApple:
		delete mAnimationClimbingThrowApple;
		mAnimationClimbingThrowApple = new Animation("Resources/Aladdin/Climbing/ClimbingThrowApple.png", 5, 1, 5, 0.03f);
		mCurrentAnimation = mAnimationClimbingThrowApple;
		break;

	case PlayerState::Death:
		delete mAnimationDeath;
		mAnimationDeath = new Animation("Resources/Aladdin/Death/Death.png", 15, 1, 15, 0.2f);
		mCurrentAnimation = mAnimationDeath;
		break;

	case PlayerState::Revival:
		delete mAnimationRevival;
		mAnimationRevival = new Animation("Resources/Aladdin/Revival/Revival.png", 14, 1, 14, 0.1f);
		mCurrentAnimation = mAnimationRevival;
		break;

	default:
		break;
	}

	this->width = mCurrentAnimation->GetWidth();
	this->height = mCurrentAnimation->GetHeight();
}

Player::MoveDirection Player::getMoveDirection()
{
	if (this->vx > 0)
	{
		return MoveDirection::MoveToRight;
	}
	else if (this->vx < 0)
	{
		return MoveDirection::MoveToLeft;
	}

	return MoveDirection::None;
}

void Player::OnNoCollisionWithBottom()
{
	if (this->collisionStairs && mCurrentState == PlayerState::Running)
	{
		this->AddVy(10);
		return;
	}

	timeDelayForFalling += 0.1f;

	if (mCurrentState != PlayerState::StandingJump && mCurrentState != PlayerState::RunningJump && mCurrentState != PlayerState::VerticalClimbingJump &&
		mCurrentState != PlayerState::VerticalClimbing && mCurrentState != PlayerState::VerticalClimbingDefault && mCurrentState != PlayerState::Somersault &&
		mCurrentState != PlayerState::JumpingAttack && mCurrentState != PlayerState::JumpingThrowApple &&
		mCurrentState != PlayerState::HorizontalClimbing && mCurrentState != PlayerState::HorizontalClimbingDefault &&
		mCurrentState != PlayerState::ClimbingAttack && mCurrentState != PlayerState::ClimbingThrowApple &&
		mCurrentState != PlayerState::VerticalClimbing && allowFalling && timeDelayForFalling > 0.5f)
	{
		timeDelayForFalling = 0;
		if (mCurrentReverse)
			this->AddPosition(D3DXVECTOR3(-5, 0, 0));
		else
			this->AddPosition(D3DXVECTOR3(5, 0, 0));

		this->SetState(new PlayerFallingState(this->mPlayerData));
	}
}

PlayerState::StateName Player::getState()
{
	return mCurrentState;
}
