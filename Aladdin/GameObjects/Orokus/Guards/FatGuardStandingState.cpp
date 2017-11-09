#include "FatGuardStandingState.h"

FatGuardStandingState::FatGuardStandingState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	this->mOrokuData->fatGuard->Mode = Oroku::RunMode::None;
	this->mOrokuData->fatGuard->SetVx(0);
	this->mOrokuData->fatGuard->SetVy(0);
}

FatGuardStandingState::~FatGuardStandingState()
{
}

void FatGuardStandingState::Update(float dt)
{

}

void FatGuardStandingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

OrokuState::StateName FatGuardStandingState::GetState()
{
	return OrokuState::FatGuardStanding;
}