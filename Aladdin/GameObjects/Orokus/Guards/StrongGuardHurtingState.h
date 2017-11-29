#pragma once
#include "StrongGuard.h"
#include "../OrokuState.h"

class StrongGuardHurtingState : public OrokuState
{
public:
	StrongGuardHurtingState(OrokuData *orokuData);
	~StrongGuardHurtingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
	float timeDelay;
};