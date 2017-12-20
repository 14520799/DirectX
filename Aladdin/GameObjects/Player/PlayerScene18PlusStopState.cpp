#include "PlayerScene18PlusStopState.h"
#include "../../GameControllers/SceneManager.h"

PlayerScene18PlusStopState::PlayerScene18PlusStopState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	this->mPlayerData->player->allowShowTheEnd = true;
}


PlayerScene18PlusStopState::~PlayerScene18PlusStopState()
{
}

void PlayerScene18PlusStopState::Update(float dt)
{

}

PlayerState::StateName PlayerScene18PlusStopState::GetState()
{
	return PlayerState::Scene18PlusStop;
}