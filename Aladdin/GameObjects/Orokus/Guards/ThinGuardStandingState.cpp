#include "ThinGuardStandingState.h"

ThinGuardStandingState::ThinGuardStandingState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	this->mOrokuData->thinGuard->Mode = Oroku::RunMode::None;
	this->mOrokuData->thinGuard->SetVx(0);
	this->mOrokuData->thinGuard->SetVy(0);
}

ThinGuardStandingState::~ThinGuardStandingState()
{
}

void ThinGuardStandingState::Update(float dt)
{

}

void ThinGuardStandingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

OrokuState::StateName ThinGuardStandingState::GetState()
{
	return OrokuState::ThinGuardStanding;
}
