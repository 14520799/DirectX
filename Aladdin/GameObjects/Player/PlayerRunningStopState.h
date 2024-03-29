#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerRunningStopState : public PlayerState
{
public:
	PlayerRunningStopState(PlayerData *playerData);
	~PlayerRunningStopState();

	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
};