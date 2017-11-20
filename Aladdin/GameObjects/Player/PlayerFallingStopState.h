#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerFallingStopState : public PlayerState
{
public:
	PlayerFallingStopState(PlayerData *playerData);
	~PlayerFallingStopState();

	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
	float timeDelayState;
};