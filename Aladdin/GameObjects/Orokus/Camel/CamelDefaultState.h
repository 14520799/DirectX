#pragma once
#include "Camel.h"
#include "../OrokuState.h"

class CamelDefaultState : public OrokuState
{
public:
	CamelDefaultState(OrokuData *orokuData);
	~CamelDefaultState();

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
};