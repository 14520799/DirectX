#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerDefaultState : public PlayerState
{
public:
	PlayerDefaultState(PlayerData *playerData);
	~PlayerDefaultState();

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
};