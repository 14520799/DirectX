#pragma once
#include "FatGuard.h"
#include "../Oroku.h"
#include "../OrokuState.h"

class FatGuardStandingState : public OrokuState
{
public:
	FatGuardStandingState(OrokuData *orokuData);
	~FatGuardStandingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
};