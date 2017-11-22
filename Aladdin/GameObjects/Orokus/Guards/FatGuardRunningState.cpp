#include "FatGuardRunningState.h"
#include "FatGuardStandingState.h"
#include "FatGuardAttackState.h"

FatGuardRunningState::FatGuardRunningState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	originPosX = this->mOrokuData->fatGuard->GetPosition().x;
	//set lai huong tan cong cua fatguard thanh false
	this->mOrokuData->fatGuard->mSettingLeftAttack = false;
	this->mOrokuData->fatGuard->mSettingRightAttack = false;
	this->mOrokuData->fatGuard->SetVx(0);
	this->mOrokuData->fatGuard->SetVy(0);
}

FatGuardRunningState::~FatGuardRunningState()
{
}

void FatGuardRunningState::Update(float dt)
{
	//xac dinh huong
	if (this->mOrokuData->fatGuard->Mode == Oroku::RunMode::RunAround)
	{
		//oroku di qua di lai trong 1 vung bang Define::AREA_OROKU_RUNAROUND 
		if (this->mOrokuData->fatGuard->GetPosition().x < originPosX - Define::AREA_OROKU_RUNAROUND)
		{
			this->mOrokuData->fatGuard->SetReverse(true);
		}
		else if (this->mOrokuData->fatGuard->GetPosition().x >= originPosX)
		{
			this->mOrokuData->fatGuard->SetReverse(false);
		}
	}
	else if (this->mOrokuData->fatGuard->Mode == Oroku::RunMode::RunComeback)
	{
		//oroku quay lai cho cu
		if (this->mOrokuData->fatGuard->GetPosition().x - this->mOrokuData->fatGuard->mOriginPosition.x < -1)
		{
			this->mOrokuData->fatGuard->SetReverse(true);
		}
		else if (this->mOrokuData->fatGuard->GetPosition().x - this->mOrokuData->fatGuard->mOriginPosition.x > 1)
		{
			this->mOrokuData->fatGuard->SetReverse(false);
		}
		else
		{
			this->mOrokuData->fatGuard->mCurrentReverse = !this->mOrokuData->fatGuard->mCurrentReverse;
			this->mOrokuData->fatGuard->SetState(new FatGuardStandingState(this->mOrokuData));
			return;
		}
	}

	//tang van toc sau khi xac dinh huong
	if (this->mOrokuData->fatGuard->mCurrentReverse)
	{
		this->mOrokuData->fatGuard->AddVx(Define::OROKU_NORMAL_SPPED_X);
		if (this->mOrokuData->fatGuard->GetVx() > Define::OROKU_MAX_RUNNING_SPEED)
		{
			this->mOrokuData->fatGuard->SetVx(Define::OROKU_MAX_RUNNING_SPEED);
		}
	}
	else if (!this->mOrokuData->fatGuard->mCurrentReverse)
	{
		this->mOrokuData->fatGuard->AddVx(-Define::OROKU_NORMAL_SPPED_X);
		if (this->mOrokuData->fatGuard->GetVx() < -Define::OROKU_MAX_RUNNING_SPEED)
		{
			this->mOrokuData->fatGuard->SetVx(-Define::OROKU_MAX_RUNNING_SPEED);
		}
	}
}

void FatGuardRunningState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag != Entity::EntityTypes::Guard && impactor->Tag != Entity::EntityTypes::Aladdin &&
		impactor->Tag != Entity::EntityTypes::Sword)
	{
		switch (side)
		{
		case Entity::Left:
			this->mOrokuData->fatGuard->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			break;

		case Entity::Right:
			this->mOrokuData->fatGuard->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			break;

		default:
			break;
		}
	}
}

OrokuState::StateName FatGuardRunningState::GetState()
{
	return OrokuState::FatGuardRunning;
}
