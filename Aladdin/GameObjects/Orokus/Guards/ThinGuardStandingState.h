#pragma once
#include "ThinGuard.h"
#include "../OrokuState.h"

class ThinGuardStandingState : public OrokuState
{
public:
	ThinGuardStandingState(OrokuData *orokuData);
	~ThinGuardStandingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
};