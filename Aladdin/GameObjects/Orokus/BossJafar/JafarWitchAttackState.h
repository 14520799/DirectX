#pragma once
#include "Jafar.h"
#include "../OrokuState.h"

class JafarWitchAttackState : public OrokuState
{
public:
	JafarWitchAttackState(OrokuData *orokuData);
	~JafarWitchAttackState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
	float timeCreateWeapon;

};