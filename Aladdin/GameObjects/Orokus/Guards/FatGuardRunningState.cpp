#include "FatGuardRunningState.h"
#include "FatGuardStandingState.h"
#include "FatGuardAttackState.h"
#include "FatGuardDefaultState.h"

FatGuardRunningState::FatGuardRunningState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
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
	if (this->mOrokuData->fatGuard->Mode == Oroku::RunMode::RunComeback)
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
		this->mOrokuData->fatGuard->AddVx(Define::OROKU_RUN_SPPED_X);
		if (this->mOrokuData->fatGuard->GetVx() > Define::OROKU_MAX_RUNNING_SPEED)
		{
			this->mOrokuData->fatGuard->SetVx(Define::OROKU_MAX_RUNNING_SPEED);
		}
	}
	else if (!this->mOrokuData->fatGuard->mCurrentReverse)
	{
		this->mOrokuData->fatGuard->AddVx(-Define::OROKU_RUN_SPPED_X);
		if (this->mOrokuData->fatGuard->GetVx() < -Define::OROKU_MAX_RUNNING_SPEED)
		{
			this->mOrokuData->fatGuard->SetVx(-Define::OROKU_MAX_RUNNING_SPEED);
		}
	}
}

void FatGuardRunningState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::Fire || impactor->Tag == Entity::EntityTypes::Camel)
	{
		switch (side)
		{
		case Entity::BottomLeft: case Entity::Left:
			this->mOrokuData->fatGuard->AddPosition(10, 0);
			break;

		case Entity::BottomRight: case Entity::Right:
			this->mOrokuData->fatGuard->AddPosition(-10, 0);
			break;

		default:
			break;
		}

		this->mOrokuData->fatGuard->mPreCurrentReverse = this->mOrokuData->fatGuard->mCurrentReverse;
		this->mOrokuData->fatGuard->SetState(new FatGuardDefaultState(this->mOrokuData));
		if (impactor->Tag == Entity::EntityTypes::Fire)
			this->mOrokuData->fatGuard->collisionFire = true;
		if (impactor->Tag == Entity::EntityTypes::Camel)
			return;
	}

	if (impactor->Tag != Entity::EntityTypes::Guard && impactor->Tag != Entity::EntityTypes::Aladdin &&
		impactor->Tag != Entity::EntityTypes::Sword && impactor->Tag != Entity::EntityTypes::AppleItem)
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
