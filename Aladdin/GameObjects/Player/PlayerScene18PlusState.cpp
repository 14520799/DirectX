#include "PlayerScene18PlusState.h"
#include "PlayerScene18PlusStopState.h"
#include "../../GameControllers/SceneManager.h"

PlayerScene18PlusState::PlayerScene18PlusState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	this->mPlayerData->player->SetReverse(false);
}


PlayerScene18PlusState::~PlayerScene18PlusState()
{
}

void PlayerScene18PlusState::Update(float dt)
{
	timeDelay += dt;
	if (timeDelay > 3)
		this->mPlayerData->player->SetState(new PlayerScene18PlusStopState(this->mPlayerData));
}

PlayerState::StateName PlayerScene18PlusState::GetState()
{
	return PlayerState::Scene18Plus;
}