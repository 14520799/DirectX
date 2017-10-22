#pragma once
#include "PlayerData.h"
#include "../Entity.h"
#include "../../GameComponents/GameCollision.h"
#include <map>

class PlayerState
{
public:
	enum StateName
	{
		Default,
		Standing,
		Running,
		Falling,
		Jumping,
		Sitting,
		VerticalClimbing,
		HorizontalClimbing,
		StandingAttack,
		SittingAttack,
		StandingThrowApple,
		SittingThrowApple,
        Death
    };

    ~PlayerState();

    virtual void Update(float dt);

    virtual void HandleKeyboard(std::map<int, bool> keys);

    //side va cham voi player
    virtual void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

    virtual StateName GetState() = 0;

protected:
    PlayerState(PlayerData *playerData);
    PlayerState();

    PlayerData *mPlayerData;
};

