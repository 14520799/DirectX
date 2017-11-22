#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerStandingUpStopState : public PlayerState
{
public:
	PlayerStandingUpStopState(PlayerData *playerData);
	~PlayerStandingUpStopState();

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
};