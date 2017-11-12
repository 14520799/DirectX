#include "StrongGuard.h"
#include "StrongGuardStandingState.h"
#include "StrongGuardRunningState.h"
#include "StrongGuardHurtingState.h"
#include "StrongGuardAttackState.h"
#include "../../../GameDefines/GameDefine.h"

StrongGuard::StrongGuard(D3DXVECTOR3 position)
{
	mAnimationStanding = new Animation("Resources/Orokus/Guards/StrongGuardStanding_1.png", 6, 1, 6, 0.1f);
	mAnimationRunning = new Animation("Resources/Orokus/Guards/StrongGuardRunning.png", 8, 1, 8, 0.1f);
	mAnimationHurting = new Animation("Resources/Orokus/Guards/StrongGuardHurting.png", 9, 1, 9, 0.1f);
	mAnimationAttack = new Animation("Resources/Orokus/Guards/StrongGuardAttack_2.png", 5, 1, 5, 0.05f);

	this->mOriginPosition = position;
	this->SetPosition(mOriginPosition);

	this->mOrokuData = new OrokuData();
	this->mOrokuData->strongGuard = this;
	this->vx = 0;
	this->vy = 0;

	this->SetState(new StrongGuardStandingState(this->mOrokuData));

	Mode = RunMode::None;

	if (!mPlayer)
	{
		settedPlayer = false;
	}
}

StrongGuard::~StrongGuard()
{

}

void StrongGuard::Update(float dt)
{
	mCurrentAnimation->Update(dt);

	if (this->mOrokuData->state)
	{
		this->mOrokuData->state->Update(dt);
	}

	this->Entity::Update(dt);

#pragma region OROKU RUN TO ATTACK PLAYER
	// khi co khoang cach voi player -30 < player < 200 thi oroku se chay toi tan cong player
	if (this->GetPosition().x - this->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN &&
		this->GetPosition().x - this->mPlayer->GetPosition().x <= Define::DANGEROUS_AREA_MAX && !settingAttack)
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

		if (runningFire)
		{
			this->SetState(new StrongGuardHurtingState(this->mOrokuData));
		}
		else
		{
			this->SetState(new StrongGuardRunningState(this->mOrokuData));
		}
	}
	else if ((this->GetPosition().x - this->mPlayer->GetPosition().x) > -Define::DANGEROUS_AREA_MAX &&
			 (this->GetPosition().x - this->mPlayer->GetPosition().x) < Define::DANGEROUS_AREA_MIN && !settingAttack)
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

		if (runningFire)
		{
			this->SetState(new StrongGuardHurtingState(this->mOrokuData));
		}
		else
		{
			this->SetState(new StrongGuardRunningState(this->mOrokuData));
		}				
	}
#pragma endregion

#pragma region OROKU RUN COMEBACK
	// khi co khoang cach voi player -600 --> 600 thi oroku se quay ve cho cu
	else if ((this->GetPosition().x - this->mPlayer->GetPosition().x < (-Define::DANGEROUS_AREA_MAX * 2) ||
			  this->GetPosition().x - this->mPlayer->GetPosition().x >(Define::DANGEROUS_AREA_MAX * 2)) &&
			  Mode == Oroku::RunMode::RunAttack)
	{
		Mode = Oroku::RunMode::RunComeback;
		mSettingRightRun = false;
		mSettingLeftRun = false;
		if (runningFire)
		{
			this->SetState(new StrongGuardHurtingState(this->mOrokuData));
		}
		else
		{
			this->SetState(new StrongGuardRunningState(this->mOrokuData));
		}
	}
#pragma endregion
}

void StrongGuard::SetState(OrokuState *newState)
{
	delete this->mOrokuData->state;

	this->mOrokuData->state = newState;

	this->changeAnimation(newState->GetState());

	mCurrentState = newState->GetState();
}

void StrongGuard::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}

void StrongGuard::SetPlayer(Player *player)
{
	this->mPlayer = player;
}

RECT StrongGuard::GetBound()
{
	RECT rect;
	rect.left = this->posX - mCurrentAnimation->GetWidth() / 2;
	rect.right = rect.left + mCurrentAnimation->GetWidth();
	rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
	rect.bottom = rect.top + mCurrentAnimation->GetHeight();

	return rect;
}

void StrongGuard::Draw(D3DXVECTOR2 trans)
{
	mCurrentAnimation->FlipVertical(this->mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), trans);
}

void StrongGuard::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	this->mOrokuData->state->OnCollision(impactor, side, data);
}

void StrongGuard::changeAnimation(OrokuState::StateName state)
{
	switch (state)
	{
	case OrokuState::StrongGuardStanding:
		mCurrentAnimation = mAnimationStanding;
		break;

	case OrokuState::StrongGuardRunning:
		mCurrentAnimation = mAnimationRunning;
		break;

	case OrokuState::StrongGuardHurting:
		mCurrentAnimation = mAnimationHurting;
		break;

	case OrokuState::StrongGuardAttack:
		mCurrentAnimation = mAnimationAttack;
		break;

	default:
		break;
	}

	this->width = mCurrentAnimation->GetWidth();
	this->height = mCurrentAnimation->GetHeight();
}

OrokuState::StateName StrongGuard::getState()
{
	return mCurrentState;
}