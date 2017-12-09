#pragma once
#include "CivilianBasket.h"
#include "../OrokuState.h"

class CivilianBasketStandingState : public OrokuState
{
public:
	CivilianBasketStandingState(OrokuData *orokuData);
	~CivilianBasketStandingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
};