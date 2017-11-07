#pragma once
#include "FatGuard.h"
#include "../OrokuState.h"
#include "../../../GameDefines/GameDefine.h"

class FatGuardRunningState : public OrokuState
{
public:
	FatGuardRunningState(OrokuData *orokuData);
	~FatGuardRunningState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();
protected:
	float originPosX;
};