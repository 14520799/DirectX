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
		ThinGuardDefault,
		ThinGuardRunning,
		ThinGuardAttack,
		ThinGuardHurting,
		FatGuardDefault,
		FatGuardStanding,
		FatGuardRunning,
		FatGuardAttack,
		FatGuardHurting,
		StrongGuardStanding,
		StrongGuardRunning,
		StrongGuardRunningFire,
		StrongGuardHurting,
		StrongGuardAttack,
		CamelDefault,
		CamelLying,
		CivilianWindowDefault,
		CivilianWindowThrowPot,
		CivilianCircusStanding
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