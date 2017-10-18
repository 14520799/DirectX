#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerStandingState : public PlayerState
{
public:
    PlayerStandingState(PlayerData *playerData);
    ~PlayerStandingState();

    void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

    virtual StateName GetState();

protected:
};

