#pragma once
#include "StrongGuard.h"
#include "../OrokuState.h"

class StrongGuardStandingState : public OrokuState
{
public:
	StrongGuardStandingState(OrokuData *orokuData);
	~StrongGuardStandingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
	bool allowSoundCommon;

	float timeDelay;
};