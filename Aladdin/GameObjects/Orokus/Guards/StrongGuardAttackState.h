#pragma once
#include "StrongGuard.h"
#include "../OrokuState.h"

class StrongGuardAttackState : public OrokuState
{
public:
	StrongGuardAttackState(OrokuData *orokuData);
	~StrongGuardAttackState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
	float timeDelayState;
};