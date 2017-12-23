#include "PlayerLevelCompleteState.h"
#include "../../GameControllers/SceneManager.h"
#include "PlayerDefaultState.h"

PlayerLevelCompleteState::PlayerLevelCompleteState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	this->mPlayerData->player->SetReverse(false);
}


PlayerLevelCompleteState::~PlayerLevelCompleteState()
{
}

void PlayerLevelCompleteState::Update(float dt)
{
	timeDelay += dt;
	if (timeDelay > 5.5f)
		this->mPlayerData->player->SetState(new PlayerDefaultState(this->mPlayerData));
}

PlayerState::StateName PlayerLevelCompleteState::GetState()
{
	return PlayerState::LevelComplete;
}