#pragma once
#include "StrongGuard.h"
#include "../OrokuState.h"
#include "../../../GameDefines/GameDefine.h"

class StrongGuardRunningState : public OrokuState
{
public:
	StrongGuardRunningState(OrokuData *orokuData);
	~StrongGuardRunningState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();
protected:
	float originPosX;
};