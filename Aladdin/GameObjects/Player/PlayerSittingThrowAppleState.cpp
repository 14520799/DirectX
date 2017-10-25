#include "PlayerSittingThrowAppleState.h"
#include "../../GameComponents/GameCollision.h"

PlayerSittingThrowAppleState::PlayerSittingThrowAppleState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
}

PlayerSittingThrowAppleState::~PlayerSittingThrowAppleState()
{

}

void PlayerSittingThrowAppleState::HandleKeyboard(std::map<int, bool> keys)
{

}

void PlayerSittingThrowAppleState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

PlayerState::StateName PlayerSittingThrowAppleState::GetState()
{
	return PlayerState::SittingThrowApple;
}