#include "StrongGuard.h"
#include "StrongGuardStandingState.h"
#include "StrongGuardRunningState.h"
#include "StrongGuardRunningFireState.h"
#include "StrongGuardAttackState.h"
#include "StrongGuardHurtingState.h"
#include "../../../GameDefines/GameDefine.h"

StrongGuard::StrongGuard(D3DXVECTOR3 position)
{
	this->mOriginPosition = position;
	this->SetPosition(mOriginPosition);
	this->Id = Entity::EntityId::Guard;

	this->mOrokuData = new OrokuData();
	this->mOrokuData->strongGuard = this;
	this->vx = 0;
	this->vy = 0;
	this->allowRun = true;

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

	if (allowImunity)
	{
		timeImunity += dt;

		if (timeImunity > 0.5f)
		{
			allowImunity = false;
			timeImunity = 0;
		}
	}

	//xet khoach cach voi player theo truc y -150 -> 150
	if (this->GetPosition().y - this->mPlayer->GetPosition().y > -Define::DANGEROUS_AREA_MAX_Y &&
		this->GetPosition().y - this->mPlayer->GetPosition().y < Define::DANGEROUS_AREA_MAX_Y)
	{
		if (!allowDefault)
		{
#pragma region OROKU RUN TO ATTACK PLAYER
			// khi co khoang cach voi player 0 < player < 300 thi oroku se chay toi tan cong player
			if (this->GetPosition().x - this->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN_X &&
				this->GetPosition().x - this->mPlayer->GetPosition().x <= Define::DANGEROUS_AREA_MAX_X && !settingAttack)
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
					this->SetState(new StrongGuardRunningFireState(this->mOrokuData));
				}
				else
				{
					if (mPreCurrentReverse != mCurrentReverse || allowRun)
					{
						allowRun = true;
						this->SetState(new StrongGuardRunningState(this->mOrokuData));
					}
				}
			}
			else if ((this->GetPosition().x - this->mPlayer->GetPosition().x) > -Define::DANGEROUS_AREA_MAX_X &&
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

				if (runningFire)
				{
					this->SetState(new StrongGuardRunningFireState(this->mOrokuData));
				}
				else
				{
					if (mPreCurrentReverse != mCurrentReverse || allowRun)
					{
						allowRun = true;
						this->SetState(new StrongGuardRunningState(this->mOrokuData));
					}
				}
			}
#pragma endregion

#pragma region OROKU AROUSE
			else if (this->GetPosition().x - this->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN_X &&
				this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX_X * 3 && !settingAttack)
			{
				if (mCurrentState == OrokuState::StrongGuardStanding || runningFire)
					return;
				this->SetReverse(false);
				this->SetState(new StrongGuardStandingState(this->mOrokuData));
			}
			else if (this->GetPosition().x - this->mPlayer->GetPosition().x > -Define::DANGEROUS_AREA_MAX_X * 3 &&
				this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MIN_X && !settingAttack)
			{
				if (mCurrentState == OrokuState::StrongGuardStanding || runningFire)
					return;
				this->SetReverse(true);
				this->SetState(new StrongGuardStandingState(this->mOrokuData));
			}
#pragma endregion

#pragma region OROKU RUN COMEBACK
			// khi co khoang cach voi player -600 --> 600 thi oroku se quay ve cho cu
			else if ((this->GetPosition().x - this->mPlayer->GetPosition().x < -Define::DANGEROUS_AREA_MAX_X * 3 ||
				this->GetPosition().x - this->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MAX_X * 3) &&
				Mode == Oroku::RunMode::RunAttack)
			{
				Mode = Oroku::RunMode::RunComeback;
				mSettingRightRun = false;
				mSettingLeftRun = false;
				if (runningFire)
				{
					this->SetState(new StrongGuardRunningFireState(this->mOrokuData));
				}
				else
				{
					this->SetState(new StrongGuardRunningState(this->mOrokuData));
				}
			}
#pragma endregion
		}
	}
}

void StrongGuard::SetState(OrokuState *newState)
{
	delete this->mOrokuData->state;

	this->mOrokuData->state = newState;

	mPreCurrentAnimation = mCurrentAnimation;
	this->changeAnimation(newState->GetState());

	if (mPreCurrentAnimation != nullptr)
		this->posY += (mPreCurrentAnimation->GetHeight() - mCurrentAnimation->GetHeight()) / 2.0f;

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

	if (mCurrentState == OrokuState::StrongGuardAttack)
	{
		rect.left = this->posX - mCurrentAnimation->GetWidth() / 2;
		rect.right = rect.left + mCurrentAnimation->GetWidth();
		rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
		rect.bottom = rect.top + mCurrentAnimation->GetHeight();
	}
	else
	{
		rect.left = this->posX - mCurrentAnimation->GetWidth() / 10;
		rect.right = this->posX + mCurrentAnimation->GetWidth() / 10;
		rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
		rect.bottom = rect.top + mCurrentAnimation->GetHeight();
	}

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
	if ((this->allowImunity || this->collisionAppleWeapon) && mCurrentState != OrokuState::StrongGuardHurting)
	{
		this->collisionAppleWeapon = false;
		this->SetState(new StrongGuardHurtingState(this->mOrokuData));
		return;
	}
	this->mOrokuData->state->OnCollision(impactor, side, data);
}

void StrongGuard::changeAnimation(OrokuState::StateName state)
{
	switch (state)
	{
	case OrokuState::StrongGuardStanding:
		delete mAnimationStanding;
		mAnimationStanding = new Animation("Resources/Orokus/Guards/StrongGuardStanding.png", 6, 1, 6, 0.1f);
		mCurrentAnimation = mAnimationStanding;
		break;

	case OrokuState::StrongGuardRunning:
		delete mAnimationRunning;
		mAnimationRunning = new Animation("Resources/Orokus/Guards/StrongGuardRunning.png", 8, 1, 8, 0.1f);
		mCurrentAnimation = mAnimationRunning;
		break;

	case OrokuState::StrongGuardRunningFire:
		delete mAnimationRunningFire;
		mAnimationRunningFire = new Animation("Resources/Orokus/Guards/StrongGuardRunningFire.png", 9, 1, 9, 0.1f);
		mCurrentAnimation = mAnimationRunningFire;
		break;

	case OrokuState::StrongGuardAttack:
		delete mAnimationAttack;
		mAnimationAttack = new Animation("Resources/Orokus/Guards/StrongGuardAttack.png", 5, 1, 5, 0.05f);
		mCurrentAnimation = mAnimationAttack;
		break;

	case OrokuState::StrongGuardHurting:
		delete mAnimationHurting;
		mAnimationHurting = new Animation("Resources/Orokus/Guards/StrongGuardHurting.png", 6, 1, 6, 0.1f);
		mCurrentAnimation = mAnimationHurting;
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