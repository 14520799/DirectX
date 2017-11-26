#pragma once
#include "ThinGuard.h"
#include "../OrokuState.h"

class ThinGuardDefaultState : public OrokuState
{
public:
	ThinGuardDefaultState(OrokuData *orokuData);
	~ThinGuardDefaultState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
};