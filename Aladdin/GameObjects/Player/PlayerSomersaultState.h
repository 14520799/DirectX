#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerSomersaultState : public PlayerState
{
public:
	PlayerSomersaultState(PlayerData *playerData);
	~PlayerSomersaultState();

	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
	bool noPressed;
	bool allowMoveRight, allowMoveLeft;
};