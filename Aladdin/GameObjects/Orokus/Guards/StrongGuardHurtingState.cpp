#include "StrongGuardHurtingState.h"
#include "StrongGuardStandingState.h"
#include "StrongGuardRunningState.h"
#include "StrongGuardAttackState.h"

StrongGuardHurtingState::StrongGuardHurtingState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	this->mOrokuData->strongGuard->runningFire = true;
	this->mOrokuData->strongGuard->SetVx(this->mOrokuData->strongGuard->GetVx());
	this->mOrokuData->strongGuard->SetVy(0);
}

StrongGuardHurtingState::~StrongGuardHurtingState()
{
}

void StrongGuardHurtingState::Update(float dt)
{
	if (this->mOrokuData->strongGuard->Mode == Oroku::RunMode::RunComeback)
	{
		//oroku quay lai cho cu
		if (this->mOrokuData->strongGuard->GetPosition().x - this->mOrokuData->strongGuard->mOriginPosition.x < -1)
		{
			this->mOrokuData->strongGuard->SetReverse(true);
		}
		else if (this->mOrokuData->strongGuard->GetPosition().x - this->mOrokuData->strongGuard->mOriginPosition.x > 1)
		{
			this->mOrokuData->strongGuard->SetReverse(false);
		}
		else
		{
			this->mOrokuData->strongGuard->Mode = Oroku::RunMode::None;
			this->mOrokuData->strongGuard->mCurrentReverse = !this->mOrokuData->strongGuard->mCurrentReverse;
			this->mOrokuData->strongGuard->SetState(new StrongGuardStandingState(this->mOrokuData));
			return;
		}
	}
	//tang van toc sau khi xac dinh huong
	if (this->mOrokuData->strongGuard->mCurrentReverse)
	{
		this->mOrokuData->strongGuard->AddVx(Define::OROKU_HURT_SPPED_X);
		if (this->mOrokuData->strongGuard->GetVx() > Define::OROKU_MAX_HURTING_SPEED)
		{
			this->mOrokuData->strongGuard->SetVx(Define::OROKU_MAX_HURTING_SPEED);
		}
	}
	else if (!this->mOrokuData->strongGuard->mCurrentReverse)
	{
		this->mOrokuData->strongGuard->AddVx(-Define::OROKU_HURT_SPPED_X);
		if (this->mOrokuData->strongGuard->GetVx() < -Define::OROKU_MAX_HURTING_SPEED)
		{
			this->mOrokuData->strongGuard->SetVx(-Define::OROKU_MAX_HURTING_SPEED);
		}
	}
}

void StrongGuardHurtingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::Aladdin)
	{
		switch (side)
		{
		case Entity::Left:
			this->mOrokuData->strongGuard->SetReverse(false);
			this->mOrokuData->strongGuard->SetState(new StrongGuardAttackState(this->mOrokuData));
			break;

		case Entity::Right:
			this->mOrokuData->strongGuard->SetReverse(true);
			this->mOrokuData->strongGuard->SetState(new StrongGuardAttackState(this->mOrokuData));
			break;

		default:
			break;
		}
	}
	else if (impactor->Tag != Entity::EntityTypes::Fire)
	{
		switch (side)
		{
		case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
			this->mOrokuData->strongGuard->runningFire = false;
			this->mOrokuData->strongGuard->SetState(new StrongGuardRunningState(this->mOrokuData));
			break;

		default:
			break;
		}
	}
}

OrokuState::StateName StrongGuardHurtingState::GetState()
{
	return OrokuState::StrongGuardHurting;
}