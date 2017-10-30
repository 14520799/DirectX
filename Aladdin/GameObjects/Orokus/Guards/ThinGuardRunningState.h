#pragma once
#include "ThinGuard.h"
#include "../OrokuState.h"
#include "../../../GameDefines/GameDefine.h"

class ThinGuardRunningState : public OrokuState
{
public:
	ThinGuardRunningState(OrokuData *orokuData);
	~ThinGuardRunningState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
};