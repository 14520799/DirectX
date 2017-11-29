#include "FatGuardHurtingState.h"
#include "FatGuardAttackState.h"
#include "FatGuardDefaultState.h"

FatGuardHurtingState::FatGuardHurtingState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	timeDelay = 0;
	this->mOrokuData->fatGuard->allowDefault = true;
	//set lai huong tan cong cua fatguard thanh false
	this->mOrokuData->fatGuard->mSettingLeftAttack = false;
	this->mOrokuData->fatGuard->mSettingRightAttack = false;
	//set lai huong bay cua cay kiem thanh false
	this->mOrokuData->fatGuard->sword->mSettingLeftItem = false;
	this->mOrokuData->fatGuard->sword->mSettingRightItem = false;
	this->mOrokuData->fatGuard->SetVx(0);
	this->mOrokuData->fatGuard->SetVy(0);
}

FatGuardHurtingState::~FatGuardHurtingState()
{
}

void FatGuardHurtingState::Update(float dt)
{
	timeDelay += dt;

	if (timeDelay > 1.0f)
	{
		this->mOrokuData->fatGuard->allowDefault = false;
		this->mOrokuData->fatGuard->SetState(new FatGuardDefaultState(this->mOrokuData));
	}
}

void FatGuardHurtingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

OrokuState::StateName FatGuardHurtingState::GetState()
{
	return OrokuState::FatGuardHurting;
}