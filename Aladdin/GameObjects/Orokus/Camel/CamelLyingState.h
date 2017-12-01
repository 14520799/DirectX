#pragma once
#include "Camel.h"
#include "../OrokuState.h"

class CamelLyingState : public OrokuState
{
public:
	CamelLyingState(OrokuData *orokuData);
	~CamelLyingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
	float timeDelay;
};