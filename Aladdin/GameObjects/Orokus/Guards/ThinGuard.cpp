#include "ThinGuard.h"
#include "ThinGuardStandingState.h"
#include "ThinGuardRunningState.h"
#include "ThinGuardAttackState.h"
#include "../../Player/Player.h"
#include "../../../GameDefines/GameDefine.h"

ThinGuard::ThinGuard(D3DXVECTOR3 position)
{
	mAnimationStanding = new Animation("Resources/Orokus/Guards/ThinGuardStanding.png", 9, 1, 9, 0.1f);
	mAnimationRunning = new Animation("Resources/Orokus/Guards/ThinGuardRunning.png", 8, 1, 8, 0.1f);
	mAnimationAttack = new Animation("Resources/Orokus/Guards/ThinGuardAttack.png", 6, 1, 6, 0.05f);

	this->SetPosition(position);

	this->mOrokuData = new OrokuData();
	this->mOrokuData->thinGuard = this;
	this->vx = 0;
	this->vy = 0;

	this->SetState(new ThinGuardStandingState(this->mOrokuData));

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

#pragma region OROKU RUNNING
	// khi co khoang cach voi player -30 < player < 200 thi oroku se chay toi tan cong player
	if (this->GetPosition().x - this->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN &&
		this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX && !settedAttack)
	{
		if (mSettedRightRunning)
			mSettedRightRunning = false;
		//neu oroku dang di sang ben trai thi return k can set state lai nua
		if (mSettedLeftRunning)
		{
			return;
		}
		this->SetReverse(false);
		this->SetState(new ThinGuardRunningState(this->mOrokuData));
		this->mSettedLeftRunning = true;
	}
	else if ((this->GetPosition().x - this->mPlayer->GetPosition().x) > -Define::DANGEROUS_AREA_MAX &&
			(this->GetPosition().x - this->mPlayer->GetPosition().x) < Define::DANGEROUS_AREA_MIN && !settedAttack)
	{
		if (mSettedLeftRunning)
			mSettedLeftRunning = false;
		//neu oroku dang di sang ben phai thi return k can set state lai nua
		if (mSettedRightRunning)
		{
			return;
		}
		this->SetReverse(true);
		this->SetState(new ThinGuardRunningState(this->mOrokuData));
		this->mSettedRightRunning = true;
	}
#pragma endregion
}

void ThinGuard::SetState(OrokuState *newState)
{
	delete this->mOrokuData->state;

	this->mOrokuData->state = newState;

	this->changeAnimation(newState->GetState());

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
	this->mOrokuData->state->OnCollision(impactor, side, data);
}

void ThinGuard::changeAnimation(OrokuState::StateName state)
{
	switch (state)
	{
	case OrokuState::ThinGuardStanding:
		mCurrentAnimation = mAnimationStanding;
		break;

	case OrokuState::ThinGuardRunning:
		mCurrentAnimation = mAnimationRunning;
		break;

	case OrokuState::ThinGuardAttack:
		mCurrentAnimation = mAnimationAttack;
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
