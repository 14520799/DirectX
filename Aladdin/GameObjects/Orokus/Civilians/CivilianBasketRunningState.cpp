#include "CivilianBasketRunningState.h"
#include "civilianBasketAttackState.h"
#include "CivilianBasketStandingState.h"

CivilianBasketRunningState::CivilianBasketRunningState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	this->mOrokuData->civilianBasket->SetVx(0);
	this->mOrokuData->civilianBasket->SetVy(0);
}

CivilianBasketRunningState::~CivilianBasketRunningState()
{
}

void CivilianBasketRunningState::Update(float dt)
{
	//xac dinh huong
	if (this->mOrokuData->civilianBasket->Mode == Oroku::RunMode::RunComeback)
	{
		//oroku quay lai cho cu
		if (this->mOrokuData->civilianBasket->GetPosition().x - this->mOrokuData->civilianBasket->mOriginPosition.x < -1)
		{
			this->mOrokuData->civilianBasket->SetReverse(true);
		}
		else if (this->mOrokuData->civilianBasket->GetPosition().x - this->mOrokuData->civilianBasket->mOriginPosition.x > 1)
		{
			this->mOrokuData->civilianBasket->SetReverse(false);
		}
		else
		{
			this->mOrokuData->civilianBasket->mCurrentReverse = !this->mOrokuData->civilianBasket->mCurrentReverse;
			this->mOrokuData->civilianBasket->Mode = Oroku::RunMode::None;
			this->mOrokuData->civilianBasket->SetState(new CivilianBasketStandingState(this->mOrokuData));
			return;
		}
	}
	//tang van toc sau khi xac dinh huong
	if (this->mOrokuData->civilianBasket->mCurrentReverse)
	{
		this->mOrokuData->civilianBasket->AddVx(-Define::OROKU_RUN_SPPED_X);
		if (this->mOrokuData->civilianBasket->GetVx() < -Define::OROKU_MAX_RUNNING_SPEED)
		{
			this->mOrokuData->civilianBasket->SetVx(-Define::OROKU_MAX_RUNNING_SPEED);
		}
	}
	else if (!this->mOrokuData->civilianBasket->mCurrentReverse)
	{
		this->mOrokuData->civilianBasket->AddVx(Define::OROKU_RUN_SPPED_X);
		if (this->mOrokuData->civilianBasket->GetVx() > Define::OROKU_MAX_RUNNING_SPEED)
		{
			this->mOrokuData->civilianBasket->SetVx(Define::OROKU_MAX_RUNNING_SPEED);
		}
	}
}

void CivilianBasketRunningState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::Aladdin)
	{
		switch (side)
		{
		case Entity::Left:
			this->mOrokuData->civilianBasket->SetReverse(true);
			this->mOrokuData->civilianBasket->SetState(new CivilianBasketAttackState(this->mOrokuData));
			break;

		case Entity::Right:
			this->mOrokuData->civilianBasket->SetReverse(false);
			this->mOrokuData->civilianBasket->SetState(new CivilianBasketAttackState(this->mOrokuData));
			break;

		default:
			break;
		}
	}
	else if (impactor->Tag == Entity::EntityTypes::OrokuControl)
	{
		switch (side)
		{
		case Entity::BottomLeft: case Entity::Left:
			this->mOrokuData->civilianBasket->AddPosition(10, 0);
			break;

		case Entity::BottomRight: case Entity::Right:
			this->mOrokuData->civilianBasket->AddPosition(-10, 0);
			break;

		default:
			break;
		}
		this->mOrokuData->civilianBasket->mPreCurrentReverse = this->mOrokuData->civilianBasket->mCurrentReverse;
		this->mOrokuData->civilianBasket->allowRun = false;
		this->mOrokuData->civilianBasket->SetState(new CivilianBasketStandingState(this->mOrokuData));
	}
	else if (impactor->Tag != Entity::EntityTypes::Oroku && impactor->Tag != Entity::EntityTypes::Sword &&
		impactor->Tag != Entity::EntityTypes::Item)
	{
		switch (side)
		{
		case Entity::Left:
			this->mOrokuData->civilianBasket->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			break;

		case Entity::Right:
			this->mOrokuData->civilianBasket->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			break;

		default:
			break;
		}
	}
}

OrokuState::StateName CivilianBasketRunningState::GetState()
{
	return OrokuState::CivilianBasketRunning;
}