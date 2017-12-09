#pragma once
#include "CivilianBasket.h"
#include "../OrokuState.h"

class CivilianBasketAttackState : public OrokuState
{
public:
	CivilianBasketAttackState(OrokuData *orokuData);
	~CivilianBasketAttackState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
	float timeDelayState;
};