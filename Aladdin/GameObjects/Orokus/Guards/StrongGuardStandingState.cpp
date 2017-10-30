#include "StrongGuardStandingState.h"

StrongGuardStandingState::StrongGuardStandingState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	this->mOrokuData->strongGuard->SetVx(0);
	this->mOrokuData->strongGuard->SetVy(0);
}

StrongGuardStandingState::~StrongGuardStandingState()
{
}

void StrongGuardStandingState::Update(float dt)
{

}

void StrongGuardStandingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

OrokuState::StateName StrongGuardStandingState::GetState()
{
	return OrokuState::StrongGuardStanding;
}