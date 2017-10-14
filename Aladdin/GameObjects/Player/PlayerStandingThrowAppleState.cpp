#include "PlayerStandingThrowAppleState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"

PlayerStandingThrowAppleState::PlayerStandingThrowAppleState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
}

PlayerStandingThrowAppleState::~PlayerStandingThrowAppleState()
{

}

void PlayerStandingThrowAppleState::HandleKeyboard(std::map<int, bool> keys)
{

}

void PlayerStandingThrowAppleState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

PlayerState::StateName PlayerStandingThrowAppleState::GetState()
{
	return PlayerState::StandingThrowApple;
}