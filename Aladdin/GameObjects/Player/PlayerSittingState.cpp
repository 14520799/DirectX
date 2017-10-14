#include "PlayerSittingState.h"
#include "PlayerStandingState.h"
#include "PlayerRunningState.h"
#include "PlayerFallingState.h"
#include "../../GameDefines/GameDefine.h"

PlayerSittingState::PlayerSittingState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}

PlayerSittingState::~PlayerSittingState()
{

}

void PlayerSittingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
	}
}

PlayerState::StateName PlayerSittingState::GetState()
{
	return PlayerState::Sitting;
}