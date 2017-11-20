#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerPushingState : public PlayerState
{
public:
	PlayerPushingState(PlayerData *playerData);
	~PlayerPushingState();

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
};