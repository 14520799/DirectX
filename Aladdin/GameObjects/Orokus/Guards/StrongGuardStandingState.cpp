#include "StrongGuardStandingState.h"

StrongGuardStandingState::StrongGuardStandingState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	this->mOrokuData->strongGuard->allowDefault = true;
	this->mOrokuData->strongGuard->settingAttack = false;
	this->mOrokuData->strongGuard->runningFire = false;
	this->mOrokuData->strongGuard->mSettingRightRun = false;
	this->mOrokuData->strongGuard->mSettingLeftRun = false;
	this->mOrokuData->strongGuard->SetVx(0);
	this->mOrokuData->strongGuard->SetVy(0);
}

StrongGuardStandingState::~StrongGuardStandingState()
{
}

void StrongGuardStandingState::Update(float dt)
{
	timeDelay += dt;

	if (timeDelay > 0.8f)
	{
		this->mOrokuData->strongGuard->allowDefault = false;
	}
}

void StrongGuardStandingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

OrokuState::StateName StrongGuardStandingState::GetState()
{
	return OrokuState::StrongGuardStanding;
}