#pragma once
#include "ThinGuard.h"
#include "../OrokuState.h"

class ThinGuardHurtingState : public OrokuState
{
public:
	ThinGuardHurtingState(OrokuData *orokuData);
	~ThinGuardHurtingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
	float timeDelay;
};