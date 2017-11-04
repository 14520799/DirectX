#include "StrongGuardHurtingState.h"
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
	//tang van toc sau khi xac dinh huong
	if (this->mOrokuData->strongGuard->mCurrentReverse)
	{
		this->mOrokuData->strongGuard->AddVx(Define::OROKU_NORMAL_SPPED_X * 2);
		if (this->mOrokuData->strongGuard->GetVx() > Define::OROKU_MAX_RUNNING_SPEED)
		{
			this->mOrokuData->strongGuard->SetVx(Define::OROKU_MAX_RUNNING_SPEED);
		}
	}
	else if (!this->mOrokuData->strongGuard->mCurrentReverse)
	{
		this->mOrokuData->strongGuard->AddVx(-Define::OROKU_NORMAL_SPPED_X * 2);
		if (this->mOrokuData->strongGuard->GetVx() < -Define::OROKU_MAX_RUNNING_SPEED)
		{
			this->mOrokuData->strongGuard->SetVx(-Define::OROKU_MAX_RUNNING_SPEED);
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
		//case Entity::Left:
		//	this->mOrokuData->strongGuard->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
		//	break;

		//case Entity::Right:
		//	this->mOrokuData->strongGuard->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
		//	break;

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