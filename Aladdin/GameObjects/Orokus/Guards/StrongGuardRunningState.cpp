#include "StrongGuardRunningState.h"
#include "StrongGuardAttackState.h"
#include "StrongGuardStandingState.h"
#include "StrongGuardHurtingState.h"

StrongGuardRunningState::StrongGuardRunningState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	originPosX = this->mOrokuData->strongGuard->GetPosition().x;
	this->mOrokuData->strongGuard->SetVx(0);
	this->mOrokuData->strongGuard->SetVy(0);
}

StrongGuardRunningState::~StrongGuardRunningState()
{
}

void StrongGuardRunningState::Update(float dt)
{
	//xac dinh huong
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
			if(this->mOrokuData->strongGuard->GetPosition().x - this->mOrokuData->strongGuard->mPlayer->GetPosition().x > 0)
				this->mOrokuData->strongGuard->SetReverse(false);
			else
				this->mOrokuData->strongGuard->SetReverse(true);
			this->mOrokuData->strongGuard->SetState(new StrongGuardStandingState(this->mOrokuData));
			return;
		}
	}
	//tang van toc sau khi xac dinh huong
	if (this->mOrokuData->strongGuard->mCurrentReverse)
	{
		this->mOrokuData->strongGuard->AddVx(Define::OROKU_NORMAL_SPPED_X);
		if (this->mOrokuData->strongGuard->GetVx() > Define::OROKU_MAX_RUNNING_SPEED)
		{
			this->mOrokuData->strongGuard->SetVx(Define::OROKU_MAX_RUNNING_SPEED);
		}
	}
	else if (!this->mOrokuData->strongGuard->mCurrentReverse)
	{
		this->mOrokuData->strongGuard->AddVx(-Define::OROKU_NORMAL_SPPED_X);
		if (this->mOrokuData->strongGuard->GetVx() < -Define::OROKU_MAX_RUNNING_SPEED)
		{
			this->mOrokuData->strongGuard->SetVx(-Define::OROKU_MAX_RUNNING_SPEED);
		}
	}
}

void StrongGuardRunningState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
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
	else if (impactor->Tag == Entity::EntityTypes::Fire)
	{
		switch (side)
		{
		case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
			this->mOrokuData->strongGuard->SetState(new StrongGuardHurtingState(this->mOrokuData));
			break;

		default:
			break;
		}
	}
	else if (impactor->Tag != Entity::EntityTypes::Guard && impactor->Tag != Entity::EntityTypes::Sword &&
			impactor->Tag != Entity::EntityTypes::AppleItem)
	{
 		switch (side)
		{
		case Entity::Left:
			this->mOrokuData->strongGuard->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			break;

		case Entity::Right:
			this->mOrokuData->strongGuard->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			break;

		default:
			break;
		}
	}
}

OrokuState::StateName StrongGuardRunningState::GetState()
{
	return OrokuState::StrongGuardRunning;
}
