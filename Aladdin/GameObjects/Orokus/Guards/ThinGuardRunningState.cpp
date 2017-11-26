#include "ThinGuardRunningState.h"
#include "ThinGuardAttackState.h"
#include "ThinGuardDefaultState.h"

ThinGuardRunningState::ThinGuardRunningState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	originPosX = this->mOrokuData->thinGuard->GetPosition().x;
	this->mOrokuData->thinGuard->SetVx(0);
	this->mOrokuData->thinGuard->SetVy(0);
}

ThinGuardRunningState::~ThinGuardRunningState()
{
}

void ThinGuardRunningState::Update(float dt)
{
	//xac dinh huong
	if (this->mOrokuData->thinGuard->Mode == Oroku::RunMode::RunAround)
	{
		//oroku di qua di lai trong 1 vung bang Define::AREA_OROKU_RUNAROUND 
		if (this->mOrokuData->thinGuard->GetPosition().x < originPosX - Define::AREA_OROKU_RUNAROUND)
		{
			this->mOrokuData->thinGuard->SetReverse(true);
		}
		else if(this->mOrokuData->thinGuard->GetPosition().x >= originPosX)
		{
			this->mOrokuData->thinGuard->SetReverse(false);
		}
	}
	else if (this->mOrokuData->thinGuard->Mode == Oroku::RunMode::RunComeback)
	{
		//oroku quay lai cho cu
		if (this->mOrokuData->thinGuard->GetPosition().x - this->mOrokuData->thinGuard->mOriginPosition.x < -1)
		{
			this->mOrokuData->thinGuard->SetReverse(true);
		}
		else if(this->mOrokuData->thinGuard->GetPosition().x - this->mOrokuData->thinGuard->mOriginPosition.x > 1)
		{
			this->mOrokuData->thinGuard->SetReverse(false);
		}
		else
		{
			this->mOrokuData->thinGuard->mCurrentReverse = !this->mOrokuData->thinGuard->mCurrentReverse;
			this->mOrokuData->thinGuard->SetState(new ThinGuardDefaultState(this->mOrokuData));
			return;
		}
	}
	//tang van toc sau khi xac dinh huong
	if (this->mOrokuData->thinGuard->mCurrentReverse)
	{
		this->mOrokuData->thinGuard->AddVx(Define::OROKU_NORMAL_SPPED_X);
		if (this->mOrokuData->thinGuard->GetVx() > Define::OROKU_MAX_RUNNING_SPEED)
		{
			this->mOrokuData->thinGuard->SetVx(Define::OROKU_MAX_RUNNING_SPEED);
		}
	}
	else if (!this->mOrokuData->thinGuard->mCurrentReverse)
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
	if (impactor->Tag == Entity::EntityTypes::Aladdin)
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
	else if(impactor->Tag != Entity::EntityTypes::Guard && impactor->Tag != Entity::EntityTypes::Sword &&
			impactor->Tag != Entity::EntityTypes::AppleItem)
	{
		switch (side)
		{
		case Entity::Left:
			this->mOrokuData->thinGuard->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			break;

		case Entity::Right:
			this->mOrokuData->thinGuard->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			break;

		default:
			break;
		}
	}
}

OrokuState::StateName ThinGuardRunningState::GetState()
{
	return OrokuState::ThinGuardRunning;
}
