#include "CivilianBasketStandingState.h"
#include "CivilianBasketAttackState.h"

CivilianBasketStandingState::CivilianBasketStandingState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	this->mOrokuData->civilianBasket->Mode = Oroku::RunMode::None;
	this->mOrokuData->civilianBasket->mSettingRightRun = false;
	this->mOrokuData->civilianBasket->mSettingLeftRun = false;
	this->mOrokuData->civilianBasket->settingAttack = false;
	this->mOrokuData->civilianBasket->SetVx(0);
	this->mOrokuData->civilianBasket->SetVy(0);
}

CivilianBasketStandingState::~CivilianBasketStandingState()
{
}

void CivilianBasketStandingState::Update(float dt)
{

}

void CivilianBasketStandingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
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
}

OrokuState::StateName CivilianBasketStandingState::GetState()
{
	return OrokuState::CivilianBasketStanding;
}