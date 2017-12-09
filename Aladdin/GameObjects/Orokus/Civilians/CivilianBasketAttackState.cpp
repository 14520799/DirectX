#include "CivilianBasketAttackState.h"
#include "civilianBasketRunningState.h"
#include "../../../GameDefines/GameDefine.h"

CivilianBasketAttackState::CivilianBasketAttackState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	this->mOrokuData->civilianBasket->settingAttack = true;
	this->mOrokuData->civilianBasket->mSettingLeftRun = false;
	this->mOrokuData->civilianBasket->mSettingRightRun = false;
	this->mOrokuData->civilianBasket->SetVx(0);
	this->mOrokuData->civilianBasket->SetVy(0);
	timeDelayState = 0;
}

CivilianBasketAttackState::~CivilianBasketAttackState()
{
}

void CivilianBasketAttackState::Update(float dt)
{
	//cho phep oroku thuc hien xong state attack roi moi co the sang state khac
	timeDelayState += dt;

	if (timeDelayState > 1.0f)
	{
		if (this->mOrokuData->civilianBasket->GetPosition().x - this->mOrokuData->civilianBasket->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN_X &&
			this->mOrokuData->civilianBasket->GetPosition().x - this->mOrokuData->civilianBasket->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX_X)
		{
			this->mOrokuData->civilianBasket->SetReverse(true);
			this->mOrokuData->civilianBasket->mSettingLeftRun = true;
			this->mOrokuData->civilianBasket->settingAttack = false;
			this->mOrokuData->civilianBasket->SetState(new CivilianBasketRunningState(this->mOrokuData));
		}
		else if ((this->mOrokuData->civilianBasket->GetPosition().x - this->mOrokuData->civilianBasket->mPlayer->GetPosition().x) > -Define::DANGEROUS_AREA_MAX_X &&
			(this->mOrokuData->civilianBasket->GetPosition().x - this->mOrokuData->civilianBasket->mPlayer->GetPosition().x) < Define::DANGEROUS_AREA_MIN_X)
		{
			this->mOrokuData->civilianBasket->SetReverse(false);
			this->mOrokuData->civilianBasket->mSettingRightRun = true;
			this->mOrokuData->civilianBasket->settingAttack = false;
			this->mOrokuData->civilianBasket->SetState(new CivilianBasketRunningState(this->mOrokuData));
		}
	}

}

void CivilianBasketAttackState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::Aladdin && !impactor->allowImunity && timeDelayState > 0.5f)
		this->mOrokuData->civilianBasket->collisionWithPlayer = true;
}

OrokuState::StateName CivilianBasketAttackState::GetState()
{
	return OrokuState::CivilianBasketAttack;
}