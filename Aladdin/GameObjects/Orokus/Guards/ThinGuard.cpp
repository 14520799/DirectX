#include "ThinGuard.h"
#include "ThinGuardDefaultState.h"
#include "ThinGuardRunningState.h"
#include "ThinGuardAttackState.h"
#include "ThinGuardHurtingState.h"
#include "../../Player/Player.h"
#include "../../../GameDefines/GameDefine.h"

ThinGuard::ThinGuard(D3DXVECTOR3 position)
{
	mAnimationDefault = new Animation("Resources/Orokus/Guards/ThinGuardDefault.png", 1, 1, 1, 0.0f);

	this->mOriginPosition = position;
	this->SetPosition(mOriginPosition);

	this->mOrokuData = new OrokuData();
	this->mOrokuData->thinGuard = this;
	this->vx = 0;
	this->vy = 0;

	this->SetState(new ThinGuardDefaultState(this->mOrokuData));

	Mode = RunMode::None;

	if (!mPlayer)
	{
		settedPlayer = false;
	}
}

ThinGuard::~ThinGuard()
{

}

void ThinGuard::Update(float dt)
{
	mCurrentAnimation->Update(dt);

	if (this->mOrokuData->state)
	{
		this->mOrokuData->state->Update(dt);
	}

	this->Entity::Update(dt);

	if (!allowDefault)
	{
#pragma region OROKU RUN TO ATTACK PLAYER
		// khi co khoang cach voi player 0 < player < 200 thi oroku se chay toi tan cong player
		if (this->GetPosition().x - this->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN_X &&
			this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX_X * 2 && !settingAttack)
		{
			Mode = RunMode::RunAttack;

			if (mSettingRightRun)
				mSettingRightRun = false;
			//neu oroku dang di sang ben trai thi return k can set state lai nua
			if (mSettingLeftRun)
			{
				return;
			}
			this->SetReverse(false);
			this->mSettingLeftRun = true;
			if (mPreCurrentReverse != mCurrentReverse || !collisionFire)
			{
				collisionFire = false;
				this->SetState(new ThinGuardRunningState(this->mOrokuData));
			}
		}
		else if ((this->GetPosition().x - this->mPlayer->GetPosition().x) > -Define::DANGEROUS_AREA_MAX_X * 2 &&
			(this->GetPosition().x - this->mPlayer->GetPosition().x) < Define::DANGEROUS_AREA_MIN_X && !settingAttack)
		{
			Mode = RunMode::RunAttack;

			if (mSettingLeftRun)
				mSettingLeftRun = false;
			//neu oroku dang di sang ben phai thi return k can set state lai nua
			if (mSettingRightRun)
			{
				return;
			}
			this->SetReverse(true);
			this->mSettingRightRun = true;
			if (mPreCurrentReverse != mCurrentReverse || !collisionFire)
			{
				collisionFire = false;
				this->SetState(new ThinGuardRunningState(this->mOrokuData));
			}
		}
#pragma endregion

#pragma region OROKU DEFAULT
		// khi co khoang cach voi player -600 --> 600 thi oroku se di xung quanh
		else if ((this->GetPosition().x - this->mPlayer->GetPosition().x > -Define::DANGEROUS_AREA_MAX_X * 3 &&
			this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX_X * 3) && !settingAttack &&
			Mode != Oroku::RunMode::RunComeback)
		{
			this->SetState(new ThinGuardDefaultState(this->mOrokuData));
		}
#pragma endregion

#pragma region OROKU RUN COMEBACK
		// khi co khoang cach voi player -600 --> 600 thi oroku se quay ve cho cu
		else if ((this->GetPosition().x - this->mPlayer->GetPosition().x < (-Define::DANGEROUS_AREA_MAX_X * 3) ||
			this->GetPosition().x - this->mPlayer->GetPosition().x >(Define::DANGEROUS_AREA_MAX_X * 3)) &&
			Mode == Oroku::RunMode::RunAttack)
		{
			Mode = Oroku::RunMode::RunComeback;
			mSettingRightRun = false;
			mSettingLeftRun = false;
			settingAttack = false;
			this->SetState(new ThinGuardRunningState(this->mOrokuData));
		}
#pragma endregion
	}
}

void ThinGuard::SetState(OrokuState *newState)
{
	delete this->mOrokuData->state;

	this->mOrokuData->state = newState;

	mPreCurrentAnimation = mCurrentAnimation;
	this->changeAnimation(newState->GetState());

	if (mPreCurrentAnimation != nullptr)
		this->posY += (mPreCurrentAnimation->GetHeight() - mCurrentAnimation->GetHeight()) / 2.0f;

	mCurrentState = newState->GetState();
}

void ThinGuard::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}

void ThinGuard::SetPlayer(Player *player)
{
	this->mPlayer = player;
}

RECT ThinGuard::GetBound()
{
	RECT rect;
	rect.left = this->posX - mCurrentAnimation->GetWidth() / 2;
	rect.right = rect.left + mCurrentAnimation->GetWidth();
	rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
	rect.bottom = rect.top + mCurrentAnimation->GetHeight();

	return rect;
}

void ThinGuard::Draw(D3DXVECTOR2 trans)
{
	mCurrentAnimation->FlipVertical(this->mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), trans);
}

void ThinGuard::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (impactor->Tag == Entity::EntityTypes::AppleWeapon)
	{
		this->mOrokuData->thinGuard->SetState(new ThinGuardHurtingState(this->mOrokuData));
		return;
	}
	this->mOrokuData->state->OnCollision(impactor, side, data);
}

void ThinGuard::changeAnimation(OrokuState::StateName state)
{
	switch (state)
	{
	case OrokuState::ThinGuardDefault:
		mCurrentAnimation = mAnimationDefault;
		break;

	case OrokuState::ThinGuardRunning:
		delete mAnimationRunning;
		mAnimationRunning = new Animation("Resources/Orokus/Guards/ThinGuardRunning.png", 8, 1, 8, 0.01f);
		mCurrentAnimation = mAnimationRunning;
		break;

	case OrokuState::ThinGuardAttack:
		delete mAnimationAttack;
		mAnimationAttack = new Animation("Resources/Orokus/Guards/ThinGuardAttack.png", 6, 1, 6, 0.01f);
		mCurrentAnimation = mAnimationAttack;
		break;

	case OrokuState::ThinGuardHurting:
		delete mAnimationHurting;
		mAnimationHurting = new Animation("Resources/Orokus/Guards/ThinGuardHurting.png", 9, 1, 9, 0.1f);
		mCurrentAnimation = mAnimationHurting;
		break;

	default:
		break;
	}

	this->width = mCurrentAnimation->GetWidth();
	this->height = mCurrentAnimation->GetHeight();
}

OrokuState::StateName ThinGuard::getState()
{
	return mCurrentState;
}
