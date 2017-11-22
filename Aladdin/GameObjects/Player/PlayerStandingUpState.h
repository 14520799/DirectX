#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerStandingUpState : public PlayerState
{
public:
	PlayerStandingUpState(PlayerData *playerData);
	~PlayerStandingUpState();

	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
	float timeDelayState;
};