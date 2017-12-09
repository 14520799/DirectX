#pragma once
#include "CivilianBasket.h"
#include "../OrokuState.h"
#include "../../../GameDefines/GameDefine.h"

class CivilianBasketRunningState : public OrokuState
{
public:
	CivilianBasketRunningState(OrokuData *orokuData);
	~CivilianBasketRunningState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();
protected:
	float originPosX;
};