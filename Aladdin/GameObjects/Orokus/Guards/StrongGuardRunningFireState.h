#pragma once
#include "StrongGuard.h"
#include "../OrokuState.h"
#include "../../../GameDefines/GameDefine.h"

class StrongGuardRunningFireState : public OrokuState
{
public:
	StrongGuardRunningFireState(OrokuData *orokuData);
	~StrongGuardRunningFireState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();
protected:
	float originPosX;
};