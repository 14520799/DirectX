#pragma once
#include "ThinGuard.h"
#include "../OrokuState.h"

class ThinGuardAttackState : public OrokuState
{
public:
	ThinGuardAttackState(OrokuData *orokuData);
	~ThinGuardAttackState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
	float timeDelayState;
};