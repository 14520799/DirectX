#include "PlayerRevivalState.h"
#include "PlayerStandingState.h"
#include "PlayerRunningState.h"
#include "PlayerDefaultState.h"
#include "../../GameDefines/GameDefine.h"

PlayerRevivalState::PlayerRevivalState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
}


PlayerRevivalState::~PlayerRevivalState()
{
}

void PlayerRevivalState::Update(float dt)
{
	timeDelayState += dt;
	if (timeDelayState > 1.5f)
		this->mPlayerData->player->InitPlayer();
}

PlayerState::StateName PlayerRevivalState::GetState()
{
	return PlayerState::Revival;
}