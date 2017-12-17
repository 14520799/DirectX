#include "FatGuardHurtingState.h"
#include "FatGuardAttackState.h"
#include "FatGuardDefaultState.h"
#include "../../../GameDefines/GameDefine.h"

FatGuardHurtingState::FatGuardHurtingState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	timeDelay = 0;
	this->mOrokuData->fatGuard->SetVx(0);
	this->mOrokuData->fatGuard->SetVy(0);
	this->mOrokuData->fatGuard->allowDefault = true;
}

FatGuardHurtingState::~FatGuardHurtingState()
{
}

void FatGuardHurtingState::Update(float dt)
{
	if (this->mOrokuData->fatGuard->weapon->mSettingLeftItem)
	{
		this->mOrokuData->fatGuard->weapon->AddVx(-Define::ITEM_SPEED_X);
		if (this->mOrokuData->fatGuard->weapon->GetVy() <= Define::ITEM_MIN_VELOCITY || this->mOrokuData->fatGuard->weapon->DirectionDown)
		{
			this->mOrokuData->fatGuard->weapon->AddVy(Define::ITEM_SPEED_Y);
			this->mOrokuData->fatGuard->weapon->DirectionDown = true;
		}
		else if (this->mOrokuData->fatGuard->weapon->GetVy() > Define::ITEM_MIN_VELOCITY)
			this->mOrokuData->fatGuard->weapon->AddVy(-Define::ITEM_SPEED_Y);
	}
	else if (this->mOrokuData->fatGuard->weapon->mSettingRightItem)
	{
		this->mOrokuData->fatGuard->weapon->AddVx(Define::ITEM_SPEED_X);
		if (this->mOrokuData->fatGuard->weapon->GetVy() <= Define::ITEM_MIN_VELOCITY || this->mOrokuData->fatGuard->weapon->DirectionDown)
		{
			this->mOrokuData->fatGuard->weapon->AddVy(Define::ITEM_SPEED_Y);
			this->mOrokuData->fatGuard->weapon->DirectionDown = true;
		}
		else if (this->mOrokuData->fatGuard->weapon->GetVy() > Define::ITEM_MIN_VELOCITY)
			this->mOrokuData->fatGuard->weapon->AddVy(-Define::ITEM_SPEED_Y);
	}

	timeDelay += dt;

	if (timeDelay > 0.7f)
	{
		this->mOrokuData->fatGuard->allowDefault = false;
		this->mOrokuData->fatGuard->SetState(new FatGuardDefaultState(this->mOrokuData));
		return;
	}


}

void FatGuardHurtingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

OrokuState::StateName FatGuardHurtingState::GetState()
{
	return OrokuState::FatGuardHurting;
}