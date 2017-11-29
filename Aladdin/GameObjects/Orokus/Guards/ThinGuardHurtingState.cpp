#include "ThinGuardHurtingState.h"
#include "ThinGuardDefaultState.h"

ThinGuardHurtingState::ThinGuardHurtingState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	this->mOrokuData->thinGuard->allowDefault = true;
	this->mOrokuData->thinGuard->settingAttack = false;
	this->mOrokuData->thinGuard->mSettingRightRun = false;
	this->mOrokuData->thinGuard->mSettingLeftRun = false;
	this->mOrokuData->thinGuard->SetVx(0);
	this->mOrokuData->thinGuard->SetVy(0);
}

ThinGuardHurtingState::~ThinGuardHurtingState()
{
}

void ThinGuardHurtingState::Update(float dt)
{
	timeDelay += dt;

	if (timeDelay > 1.0f)
	{
		this->mOrokuData->thinGuard->allowDefault = false;
		this->mOrokuData->thinGuard->SetState(new ThinGuardDefaultState(this->mOrokuData));
	}
}

void ThinGuardHurtingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

OrokuState::StateName ThinGuardHurtingState::GetState()
{
	return OrokuState::ThinGuardHurting;
}