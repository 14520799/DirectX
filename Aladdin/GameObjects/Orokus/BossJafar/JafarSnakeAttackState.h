#pragma once
#include "Jafar.h"
#include "../OrokuState.h"

class JafarSnakeAttackState : public OrokuState
{
public:
	JafarSnakeAttackState(OrokuData *orokuData);
	~JafarSnakeAttackState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
	float timeCreateWeapon;
};