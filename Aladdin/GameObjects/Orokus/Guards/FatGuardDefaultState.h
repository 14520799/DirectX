#pragma once
#include "FatGuard.h"
#include "../Oroku.h"
#include "../OrokuState.h"

class FatGuardDefaultState : public OrokuState
{
public:
	FatGuardDefaultState(OrokuData *orokuData);
	~FatGuardDefaultState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
	float timeDelay;
};