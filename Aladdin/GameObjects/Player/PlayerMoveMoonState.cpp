#include "PlayerMoveMoonState.h"
#include "../../GameControllers/SceneManager.h"
#include "PlayerScene18PlusState.h"

PlayerMoveMoonState::PlayerMoveMoonState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	this->mPlayerData->player->SetReverse(false);
}


PlayerMoveMoonState::~PlayerMoveMoonState()
{
}

void PlayerMoveMoonState::Update(float dt)
{
	timeDelay += dt;
	if (timeDelay > 8.0f)
		this->mPlayerData->player->SetState(new PlayerScene18PlusState(this->mPlayerData));
}

PlayerState::StateName PlayerMoveMoonState::GetState()
{
	return PlayerState::MoveMoon;
}