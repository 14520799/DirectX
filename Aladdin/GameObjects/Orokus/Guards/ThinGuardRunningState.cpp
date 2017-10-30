#include "ThinGuardRunningState.h"
#include "ThinGuardAttackState.h"

ThinGuardRunningState::ThinGuardRunningState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	this->mOrokuData->thinGuard->SetVx(0);
	this->mOrokuData->thinGuard->SetVy(0);
}

ThinGuardRunningState::~ThinGuardRunningState()
{
}

void ThinGuardRunningState::Update(float dt)
{
	if (this->mOrokuData->thinGuard->mCurrentReverse)
	{
		this->mOrokuData->thinGuard->AddVx(Define::OROKU_NORMAL_SPPED_X);
		if (this->mOrokuData->thinGuard->GetVx() > Define::OROKU_MAX_RUNNING_SPEED)
		{
			this->mOrokuData->thinGuard->SetVx(Define::OROKU_MAX_RUNNING_SPEED);
		}
	}
	else
	{
		this->mOrokuData->thinGuard->AddVx(-Define::OROKU_NORMAL_SPPED_X);
		if (this->mOrokuData->thinGuard->GetVx() < -Define::OROKU_MAX_RUNNING_SPEED)
		{
			this->mOrokuData->thinGuard->SetVx(-Define::OROKU_MAX_RUNNING_SPEED);
		}
	}


}

void ThinGuardRunningState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Left:
		this->mOrokuData->thinGuard->SetReverse(false);
		this->mOrokuData->thinGuard->SetState(new ThinGuardAttackState(this->mOrokuData));
		break;

	case Entity::Right:
		this->mOrokuData->thinGuard->SetReverse(true);
		this->mOrokuData->thinGuard->SetState(new ThinGuardAttackState(this->mOrokuData));
		break;

	default:
		break;
	}
}

OrokuState::StateName ThinGuardRunningState::GetState()
{
	return OrokuState::ThinGuardRunning;
}
