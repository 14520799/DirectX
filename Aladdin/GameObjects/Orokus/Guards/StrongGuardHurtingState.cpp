#include "StrongGuardHurtingState.h"

StrongGuardHurtingState::StrongGuardHurtingState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	timeDelay = 0;
	this->mOrokuData->strongGuard->allowDefault = true;
	this->mOrokuData->strongGuard->settingAttack = false;
	this->mOrokuData->strongGuard->runningFire = false;
	this->mOrokuData->strongGuard->mSettingRightRun = false;
	this->mOrokuData->strongGuard->mSettingLeftRun = false;
	this->mOrokuData->strongGuard->SetVx(0);
	this->mOrokuData->strongGuard->SetVy(0);
}

StrongGuardHurtingState::~StrongGuardHurtingState()
{
}

void StrongGuardHurtingState::Update(float dt)
{
	timeDelay += dt;

	if (timeDelay > 1.0f)
	{
		this->mOrokuData->strongGuard->allowDefault = false;
	}
}

void StrongGuardHurtingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

OrokuState::StateName StrongGuardHurtingState::GetState()
{
	return OrokuState::StrongGuardHurting;
}