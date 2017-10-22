#include "PlayerDefaultState..h"
#include "PlayerStandingState.h"
#include "PlayerRunningState.h"
#include "PlayerDeathState.h"

PlayerDefaultState::PlayerDefaultState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}


PlayerDefaultState::~PlayerDefaultState()
{
}

void PlayerDefaultState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		return;
	}
}

void PlayerDefaultState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::Fire && this->mPlayerData->player->allowDeath)
	{
		this->mPlayerData->player->SetState(new PlayerDeathState(this->mPlayerData));
	}
}

PlayerState::StateName PlayerDefaultState::GetState()
{
	return PlayerState::Default;
}