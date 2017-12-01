#include "CamelLyingState.h"
#include "CamelDefaultState.h"

CamelLyingState::CamelLyingState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	timeDelay = 0;
}

CamelLyingState::~CamelLyingState()
{
}

void CamelLyingState::Update(float dt)
{
	timeDelay += dt;

	if (timeDelay > 0.5f)
	{
		this->mOrokuData->camel->SetState(new CamelDefaultState(this->mOrokuData));
	}
}

void CamelLyingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::Guard)
		this->mOrokuData->camel->collisionWithOroku = true;
}

OrokuState::StateName CamelLyingState::GetState()
{
	return OrokuState::CamelLying;
}