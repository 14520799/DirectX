#include "FatGuard.h"
#include "FatGuardStandingState.h"
#include "FatGuardRunningState.h"
#include "FatGuardAttackState.h"
#include "FatGuardDefaultState.h"
#include "../../Player/Player.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../MapObjects/SwordFatGuard.h"

FatGuard::FatGuard(D3DXVECTOR3 position)
{
	mAnimationDefault = new Animation("Resources/Orokus/Guards/FatGuardDefault.png", 1, 1, 1, 0.0f);
	mAnimationStanding = new Animation("Resources/Orokus/Guards/FatGuardStanding_2.png", 7, 1, 7, 0.15f);
	mAnimationRunning = new Animation("Resources/Orokus/Guards/FatGuardRunning.png", 8, 1, 8, 0.1f);
	mAnimationAttack = new Animation("Resources/Orokus/Guards/FatGuardAttack.png", 5, 1, 5, 0.1f);

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

	sword = new SwordFatGuard(mOriginPosition);
	sword->Tag = Entity::EntityTypes::Sword;
	addSwordQuadTree = true;
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
	if (sword->collisionWithPlayer)
	{
		allowDrawSword = false;
		sword->collisionWithPlayer = false;
	}

	//khi cay kiem dang bay ra va state doi sang running thi cay kiem van tiep tuc bay
	if (settingRunning)
	{
		if (this->sword->mSettedLeftReserve)
		{
			this->sword->AddVx(-Define::SWORDFATGUARD_SPEED);
		}
		else if (this->sword->mSettedRightReserve)
		{
			this->sword->AddVx(Define::SWORDFATGUARD_SPEED);
		}

		this->timeDelayDefaultState += dt;
		if (this->timeDelayDefaultState > 0.5f)
		{
			this->timeDelayDefaultState = 0;
			this->sword->mSettedLeftReserve = false;
			this->sword->mSettedRightReserve = false;
			this->allowDrawSword = false;
		}
	}

	//delay 1 khoang time de thuc hien statedefault
	if (!allowDefault)
	{
#pragma region OROKU ATTACK PLAYER
		// khi co khoang cach voi player 0 < player < 200 thi oroku se chay toi tan cong player
		if (this->GetPosition().x - this->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN &&
			this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX)
		{
			this->settingRunning = false;
			//khi cay kiem dang bay ra theo huong nao thi se tiep tuc bay theo huong do 
			//cho du player co di qua phia ben kia cua fatguard
			if (this->sword->mSettedLeftReserve)
			{
				this->sword->AddVx(-Define::SWORDFATGUARD_SPEED);
				this->timeDelayDefaultState += dt;
				if (this->timeDelayDefaultState > 0.5f)
				{
					this->timeDelayDefaultState = 0;
					this->SetState(new FatGuardDefaultState(this->mOrokuData));
				}
				return;
			}
			else if (this->sword->mSettedRightReserve)
			{
				this->sword->AddVx(Define::SWORDFATGUARD_SPEED);
				this->timeDelayDefaultState += dt;
				if (this->timeDelayDefaultState > 0.5f)
				{
					this->timeDelayDefaultState = 0;
					this->SetState(new FatGuardDefaultState(this->mOrokuData));
				}
				return;
			}

			if (mSettedRightAttack)
				mSettedRightAttack = false;
			//neu oroku dang di sang ben trai thi return k can set state lai nua
			if (mSettedLeftAttack)
			{
				return;
			}
			this->SetReverse(false);
			this->allowDrawSword = true;
			this->timeDelayDefaultState = 0;
			this->SetState(new FatGuardAttackState(this->mOrokuData));
			this->mSettedLeftAttack = true;
		}
		else if ((this->GetPosition().x - this->mPlayer->GetPosition().x) > -Define::DANGEROUS_AREA_MAX &&
				 (this->GetPosition().x - this->mPlayer->GetPosition().x) < Define::DANGEROUS_AREA_MIN)
		{
			this->settingRunning = false;

			if (this->sword->mSettedLeftReserve)
			{
				this->sword->AddVx(-Define::SWORDFATGUARD_SPEED);
				this->timeDelayDefaultState += dt;
				if (this->timeDelayDefaultState > 0.5f)
				{
					this->timeDelayDefaultState = 0;
					this->SetState(new FatGuardDefaultState(this->mOrokuData));
				}
				return;
			}
			else if (this->sword->mSettedRightReserve)
			{
				this->sword->AddVx(Define::SWORDFATGUARD_SPEED);
				this->timeDelayDefaultState += dt;
				if (this->timeDelayDefaultState > 0.5f)
				{
					this->timeDelayDefaultState = 0;
					this->SetState(new FatGuardDefaultState(this->mOrokuData));
				}
				return;
			}

			if (mSettedLeftAttack)
				mSettedLeftAttack = false;
			//neu oroku dang di sang ben phai thi return k can set state lai nua
			if (mSettedRightAttack)
			{
				return;
			}
			this->SetReverse(true);
			this->allowDrawSword = true;
			this->timeDelayDefaultState = 0;
			this->SetState(new FatGuardAttackState(this->mOrokuData));
			this->mSettedRightAttack = true;
		}
#pragma endregion

#pragma region OROKU RUN TO ATTACK PLAYER
		// khi co khoang cach voi player -30 < player < 200 thi oroku se chay toi tan cong player
		else if (this->GetPosition().x - this->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN &&
				 this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX * 2)
		{
			Mode = RunMode::RunAttack;

			if (mSettedRightRunning)
				mSettedRightRunning = false;
			//neu oroku dang di sang ben trai thi return k can set state lai nua
			if (mSettedLeftRunning)
			{
				return;
			}
			this->SetReverse(false);
			this->settingRunning = true;
			this->timeDelayDefaultState = 0;
			this->mSettedLeftRunning = true;
			this->SetState(new FatGuardRunningState(this->mOrokuData));
		}
		else if ((this->GetPosition().x - this->mPlayer->GetPosition().x) > -Define::DANGEROUS_AREA_MAX * 2 &&
				 (this->GetPosition().x - this->mPlayer->GetPosition().x) < Define::DANGEROUS_AREA_MIN)
		{
			Mode = RunMode::RunAttack;

			if (mSettedLeftRunning)
				mSettedLeftRunning = false;
			//neu oroku dang di sang ben phai thi return k can set state lai nua
			if (mSettedRightRunning)
			{
				return;
			}
			this->SetReverse(true);
			this->settingRunning = true;
			this->timeDelayDefaultState = 0;
			this->mSettedRightRunning = true;
			this->SetState(new FatGuardRunningState(this->mOrokuData));
		}
#pragma endregion

#pragma region OROKU RUN AROUND
		// khi co khoang cach voi player -400 --> 400 thi oroku se di xung quanh
		else if (this->GetPosition().x - this->mPlayer->GetPosition().x > (-Define::DANGEROUS_AREA_MAX * 3) &&
				 this->GetPosition().x - this->mPlayer->GetPosition().x < (Define::DANGEROUS_AREA_MAX * 3) &&
				 Mode == Oroku::RunMode::None)
		{
			Mode = Oroku::RunMode::RunAround;
			this->allowDrawSword = false;
			this->settingRunning = false;
			this->SetState(new FatGuardRunningState(this->mOrokuData));
		}
#pragma endregion

#pragma region OROKU RUN COMEBACK
		// khi co khoang cach voi player -600 --> 600 thi oroku se quay ve cho cu
		else if ((this->GetPosition().x - this->mPlayer->GetPosition().x < (-Define::DANGEROUS_AREA_MAX * 3) ||
				 this->GetPosition().x - this->mPlayer->GetPosition().x >(Define::DANGEROUS_AREA_MAX * 3)) &&
				 Mode == Oroku::RunMode::RunAttack)
		{
			Mode = Oroku::RunMode::RunComeback;
			mSettedRightRunning = false;
			mSettedLeftRunning = false;
			this->allowDrawSword = false;
			this->settingRunning = false;
			this->SetState(new FatGuardRunningState(this->mOrokuData));
		}
#pragma endregion
	}

}

void FatGuard::SetState(OrokuState *newState)
{
	delete this->mOrokuData->state;

	this->mOrokuData->state = newState;

	this->changeAnimation(newState->GetState());

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
		mCurrentAnimation = mAnimationStanding;
		break;

	case OrokuState::FatGuardRunning:
		mCurrentAnimation = mAnimationRunning;
		break;

	case OrokuState::FatGuardAttack:
		mCurrentAnimation = mAnimationAttack;
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


