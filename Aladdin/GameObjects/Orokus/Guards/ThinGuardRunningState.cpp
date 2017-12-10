#include "ThinGuardRunningState.h"
#include "ThinGuardAttackState.h"
#include "ThinGuardDefaultState.h"

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
	//xac dinh huong
	if (this->mOrokuData->thinGuard->Mode == Oroku::RunMode::RunComeback)
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
		this->mOrokuData->thinGuard->AddVx(Define::OROKU_RUN_SPPED_X);
		if (this->mOrokuData->thinGuard->GetVx() > Define::OROKU_MAX_RUNNING_SPEED)
		{
			this->mOrokuData->thinGuard->SetVx(Define::OROKU_MAX_RUNNING_SPEED);
		}
	}
	else if (!this->mOrokuData->thinGuard->mCurrentReverse)
	{
		this->mOrokuData->thinGuard->AddVx(-Define::OROKU_RUN_SPPED_X);
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
	else if (impactor->Tag == Entity::EntityTypes::Fire || impactor->Tag == Entity::EntityTypes::OrokuControl)
	{
		switch (side)
		{
		case Entity::BottomLeft: case Entity::Left:
			this->mOrokuData->thinGuard->AddPosition(10, 0);
			break;

		case Entity::BottomRight: case Entity::Right:
			this->mOrokuData->thinGuard->AddPosition(-10, 0);
			break;

		default:
			break;
		}
		this->mOrokuData->thinGuard->mPreCurrentReverse = this->mOrokuData->thinGuard->mCurrentReverse;
		this->mOrokuData->thinGuard->collisionFire = true;
		this->mOrokuData->thinGuard->SetState(new ThinGuardDefaultState(this->mOrokuData));
	}
	else if(impactor->Tag != Entity::EntityTypes::Oroku && impactor->Tag != Entity::EntityTypes::Sword &&
			impactor->Tag != Entity::EntityTypes::Item)
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
