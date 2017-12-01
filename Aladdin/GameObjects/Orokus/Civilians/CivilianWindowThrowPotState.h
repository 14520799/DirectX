#pragma once
#include "CivilianWindow.h"
#include "../OrokuState.h"

class CivilianWindowThrowPotState : public OrokuState
{
public:
	CivilianWindowThrowPotState(OrokuData *orokuData);
	~CivilianWindowThrowPotState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
};