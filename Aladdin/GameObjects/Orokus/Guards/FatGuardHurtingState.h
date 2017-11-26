#pragma once
#include "FatGuard.h"
#include "../Oroku.h"
#include "../OrokuState.h"

class FatGuardHurtingState : public OrokuState
{
public:
	FatGuardHurtingState(OrokuData *orokuData);
	~FatGuardHurtingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
	float timeDelay;
};