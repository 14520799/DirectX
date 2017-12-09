#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerRevivalState : public PlayerState
{
public:
	PlayerRevivalState(PlayerData *playerData);
	~PlayerRevivalState();

	void Update(float dt);

	virtual StateName GetState();

protected:
	float timeDelayState;
};