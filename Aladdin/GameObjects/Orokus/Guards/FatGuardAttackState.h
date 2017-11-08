#pragma once
#include "FatGuard.h"
#include "../OrokuState.h"

class FatGuardAttackState : public OrokuState
{
public:
	FatGuardAttackState(OrokuData *orokuData);
	~FatGuardAttackState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
};