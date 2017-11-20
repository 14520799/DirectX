#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerVerticalClimbingJumpState : public PlayerState
{
public:
	PlayerVerticalClimbingJumpState(PlayerData *playerData);
	~PlayerVerticalClimbingJumpState();

	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
	bool noPressed;
};