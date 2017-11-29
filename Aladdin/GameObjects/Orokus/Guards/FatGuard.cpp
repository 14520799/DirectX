#include "FatGuard.h"
#include "FatGuardStandingState.h"
#include "FatGuardRunningState.h"
#include "FatGuardAttackState.h"
#include "FatGuardDefaultState.h"
#include "FatGuardHurtingState.h"
#include "../../Player/Player.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../MapObjects/SwordFatGuard.h"

FatGuard::FatGuard(D3DXVECTOR3 position)
{
	mAnimationDefault = new Animation("Resources/Orokus/Guards/FatGuardDefault.png", 1, 1, 1, 0.0f);

	this->mOriginPosition = position;
	this->SetPosition(mOriginPosition);

	this->mOrokuData = new OrokuData();
	this->mOrokuData->fatGuard = this;
	this->vx = 0;
	this->vy = 0;

	this->SetState(new FatGuardStandingState(this->mOrokuData));

	Mode = RunMode::None;

	if (!mPlayer)
	{
		settedPlayer = false;
	}

	this->sword = new SwordFatGuard(D3DXVECTOR3(
		this->mOrokuData->fatGuard->GetPosition().x,
		this->mOrokuData->fatGuard->GetPosition().y - this->mOrokuData->fatGuard->GetHeight() / 2,
		0));
	this->mOrokuData->fatGuard->sword->Tag = Entity::EntityTypes::Sword;
}

FatGuard::~FatGuard()
{

}

void FatGuard::Update(float dt)
{
	mCurrentAnimation->Update(dt);

	if (this->mOrokuData->state)
	{
		this->mOrokuData->state->Update(dt);
		if (allowDrawSword)
		{
			sword->Update(dt);
			sword->Entity::Update(dt);
		}
	}

	this->Entity::Update(dt);

	//neu sword va cham voi player thi se bien mat
	if (sword->collisionWithPlayer || sword->weaponCollided)
	{
		allowDrawSword = false;
		sword->collisionWithPlayer = false;
		sword->weaponCollided = false;
	}

	//delay 1 khoang time de thuc hien statedefault
	if (!allowDefault)
	{
#pragma region OROKU ATTACK PLAYER
		// khi co khoang cach voi player 0 < player < 200 thi oroku se tan cong player
		if ((this->GetPosition().x - this->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN_X &&
			this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX_X))
		{
			Mode = RunMode::None;

			//khi cay kiem dang bay ra theo huong nao thi se tiep tuc bay theo huong do 
			//cho du player co di qua phia ben kia cua fatguard
			if (this->sword->mSettingLeftItem)
			{
				this->sword->AddVx(-Define::ITEM_SPEED_X);
				this->sword->AddVy(Define::ITEM_SPEED_Y);
				this->timeDelayDefaultState += dt;
				if (this->timeDelayDefaultState > 0.8f)
				{
					this->timeDelayDefaultState = 0;
					this->SetState(new FatGuardDefaultState(this->mOrokuData));
				}
				return;
			}
			else if (this->sword->mSettingRightItem)
			{
				this->sword->AddVx(Define::ITEM_SPEED_X);
				this->sword->AddVy(Define::ITEM_SPEED_Y);
				this->timeDelayDefaultState += dt;
				if (this->timeDelayDefaultState > 0.8f)
				{
					this->timeDelayDefaultState = 0;
					this->SetState(new FatGuardDefaultState(this->mOrokuData));
				}
				return;
			}

			if (mSettingRightAttack)
				mSettingRightAttack = false;
			//neu oroku dang di sang ben trai thi return k can set state lai nua
			if (mSettingLeftAttack)
			{
				return;
			}
			this->SetReverse(false);
			this->allowDrawSword = true;
			this->timeDelayDefaultState = 0;
			this->SetState(new FatGuardAttackState(this->mOrokuData));
			this->mSettingLeftAttack = true;
		}
		else if ((this->GetPosition().x - this->mPlayer->GetPosition().x) > -Define::DANGEROUS_AREA_MAX_X &&
			(this->GetPosition().x - this->mPlayer->GetPosition().x) < Define::DANGEROUS_AREA_MIN_X)
		{
			Mode = RunMode::None;

			if (this->sword->mSettingLeftItem)
			{
				this->sword->AddVx(-Define::ITEM_SPEED_X);
				this->sword->AddVy(Define::ITEM_SPEED_Y);
				this->timeDelayDefaultState += dt;
				if (this->timeDelayDefaultState > 0.8f)
				{
					this->timeDelayDefaultState = 0;
					this->SetState(new FatGuardDefaultState(this->mOrokuData));
				}
				return;
			}
			else if (this->sword->mSettingRightItem)
			{
				this->sword->AddVx(Define::ITEM_SPEED_X);
				this->sword->AddVy(Define::ITEM_SPEED_Y);
				this->timeDelayDefaultState += dt;
				if (this->timeDelayDefaultState > 0.8f)
				{
					this->timeDelayDefaultState = 0;
					this->SetState(new FatGuardDefaultState(this->mOrokuData));
				}
				return;
			}
			if (mSettingLeftAttack)
				mSettingLeftAttack = false;
			//neu oroku dang di sang ben phai thi return k can set state lai nua
			if (mSettingRightAttack)
			{
				return;
			}
			this->SetReverse(true);
			this->allowDrawSword = true;
			this->timeDelayDefaultState = 0;
			this->SetState(new FatGuardAttackState(this->mOrokuData));
			this->mSettingRightAttack = true;
		}
#pragma endregion

#pragma region OROKU DEFAULT
		else if (((this->GetPosition().x - this->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN_X &&
			this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX_X * 1.5f)
			||
			(this->GetPosition().x - this->mPlayer->GetPosition().x > -Define::DANGEROUS_AREA_MAX_X * 1.5f &&
				this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MIN_X)) 
			&& Mode != Oroku::RunMode::RunAttack)
		{
			if (this->sword->mSettingLeftItem)
			{
				this->sword->AddVx(-Define::ITEM_SPEED_X);
				this->sword->AddVy(Define::ITEM_SPEED_Y);
				this->timeDelayDefaultState += dt;
				if (this->timeDelayDefaultState > 0.8f)
				{
					this->timeDelayDefaultState = 0;
					this->SetState(new FatGuardDefaultState(this->mOrokuData));
				}
				return;
			}
			else if (this->sword->mSettingRightItem)
			{
				this->sword->AddVx(Define::ITEM_SPEED_X);
				this->sword->AddVy(Define::ITEM_SPEED_Y);
				this->timeDelayDefaultState += dt;
				if (this->timeDelayDefaultState > 0.8f)
				{
					this->timeDelayDefaultState = 0;
					this->SetState(new FatGuardDefaultState(this->mOrokuData));
				}
				return;
			}
		}
#pragma endregion

#pragma region OROKU RUN TO ATTACK PLAYER
		// khi co khoang cach voi player -30 < player < 200 thi oroku se chay toi tan cong player
		else if (this->GetPosition().x - this->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN_X &&
			this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX_X * 2)
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
			this->timeDelayDefaultState = 0;
			this->mSettingLeftRun = true;
			if (mPreCurrentReverse != mCurrentReverse || !collisionFire)
			{
				collisionFire = false;
				this->SetState(new FatGuardRunningState(this->mOrokuData));
			}
		}
		else if ((this->GetPosition().x - this->mPlayer->GetPosition().x) > -Define::DANGEROUS_AREA_MAX_X * 2 &&
			(this->GetPosition().x - this->mPlayer->GetPosition().x) < Define::DANGEROUS_AREA_MIN_X)
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
			this->timeDelayDefaultState = 0;
			this->mSettingRightRun = true;
			if (mPreCurrentReverse != mCurrentReverse || !collisionFire)
			{
				collisionFire = false;
				this->SetState(new FatGuardRunningState(this->mOrokuData));
			}
		}
#pragma endregion

#pragma region OROKU RUN COMEBACK
		// khi co khoang cach voi player -600 --> 600 thi oroku se quay ve cho cu
		else if ((this->GetPosition().x - this->mPlayer->GetPosition().x < -Define::DANGEROUS_AREA_MAX_X * 2 ||
			this->GetPosition().x - this->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MAX_X * 2) &&
			Mode == Oroku::RunMode::RunAttack)
		{
			Mode = Oroku::RunMode::RunComeback;
			mSettingRightRun = false;
			mSettingLeftRun = false;
			this->allowDrawSword = false;
			this->SetState(new FatGuardRunningState(this->mOrokuData));
		}
#pragma endregion
	}

}

void FatGuard::SetState(OrokuState *newState)
{
	delete this->mOrokuData->state;

	this->mOrokuData->state = newState;

	mPreCurrentAnimation = mCurrentAnimation;
	this->changeAnimation(newState->GetState());

	if (mPreCurrentAnimation != nullptr)
		this->posY += (mPreCurrentAnimation->GetHeight() - mCurrentAnimation->GetHeight()) / 2.0f;

	mCurrentState = newState->GetState();
}

void FatGuard::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}

RECT FatGuard::GetBound()
{
	RECT rect;
	rect.left = this->posX - mCurrentAnimation->GetWidth() / 2;
	rect.right = rect.left + mCurrentAnimation->GetWidth();
	rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
	rect.bottom = rect.top + mCurrentAnimation->GetHeight();

	return rect;
}

bool FatGuard::GetReverse()
{
	return mCurrentReverse;
}

void FatGuard::Draw(D3DXVECTOR2 trans)
{
	mCurrentAnimation->FlipVertical(this->mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), trans);
	if (allowDrawSword)
	{
		sword->Draw(D3DXVECTOR3(sword->posX, sword->posY, 0), trans);
	}
}

void FatGuard::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (impactor->Tag == Entity::EntityTypes::AppleWeapon)
	{
		this->mOrokuData->fatGuard->SetState(new FatGuardHurtingState(this->mOrokuData));
		return;
	}
	this->mOrokuData->state->OnCollision(impactor, side, data);
}

void FatGuard::changeAnimation(OrokuState::StateName state)
{
	switch (state)
	{
	case OrokuState::FatGuardDefault:
		mCurrentAnimation = mAnimationDefault;
		break;

	case OrokuState::FatGuardStanding:
		delete mAnimationStanding;
		mAnimationStanding = new Animation("Resources/Orokus/Guards/FatGuardStanding.png", 7, 1, 7, 0.15f);
		mCurrentAnimation = mAnimationStanding;
		break;

	case OrokuState::FatGuardRunning:
		delete mAnimationRunning;
		mAnimationRunning = new Animation("Resources/Orokus/Guards/FatGuardRunning.png", 8, 1, 8, 0.1f);
		mCurrentAnimation = mAnimationRunning;
		break;

	case OrokuState::FatGuardAttack:
		delete mAnimationAttack;
		mAnimationAttack = new Animation("Resources/Orokus/Guards/FatGuardAttack.png", 5, 1, 5, 0.1f);
		mCurrentAnimation = mAnimationAttack;
		break;

	case OrokuState::FatGuardHurting:
		delete mAnimationHurting;
		mAnimationHurting = new Animation("Resources/Orokus/Guards/FatGuardHurting.png", 7, 1, 7, 0.1f);
		mCurrentAnimation = mAnimationHurting;
		break;

	default:
		break;
	}

	this->width = mCurrentAnimation->GetWidth();
	this->height = mCurrentAnimation->GetHeight();
}

OrokuState::StateName FatGuard::getState()
{
	return mCurrentState;
}


