#include "ThinGuardDefaultState.h"

ThinGuardDefaultState::ThinGuardDefaultState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	this->mOrokuData->thinGuard->Mode = Oroku::RunMode::None;
	this->mOrokuData->thinGuard->mSettingRightRun = false;
	this->mOrokuData->thinGuard->mSettingLeftRun = false;
	this->mOrokuData->thinGuard->settingAttack = false;
	this->mOrokuData->thinGuard->SetVx(0);
	this->mOrokuData->thinGuard->SetVy(0);
}

ThinGuardDefaultState::~ThinGuardDefaultState()
{
}

void ThinGuardDefaultState::Update(float dt)
{
	
}

void ThinGuardDefaultState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

OrokuState::StateName ThinGuardDefaultState::GetState()
{
	return OrokuState::ThinGuardDefault;
}
