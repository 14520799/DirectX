#pragma once
#include "OrokuData.h"
#include "../Entity.h"
#include "../../GameComponents/GameCollision.h"
#include <map>

class OrokuState
{
public:
	enum StateName
	{
		ThinGuardStanding,
		ThinGuardRunning,
		ThinGuardAttack,
		FatGuardDefault,
		FatGuardStanding,
		FatGuardRunning,
		FatGuardAttack,
		StrongGuardStanding,
		StrongGuardRunning,
		StrongGuardHurting,
		StrongGuardAttack
	};

	~OrokuState();

	virtual void Update(float dt);

	virtual void HandleKeyboard(std::map<int, bool> keys);

	virtual void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState() = 0;
protected:
	OrokuState(OrokuData *orokuData);
	OrokuState();

	OrokuData *mOrokuData;
};