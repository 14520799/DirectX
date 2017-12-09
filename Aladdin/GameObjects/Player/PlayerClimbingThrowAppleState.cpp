#include "PlayerClimbingThrowAppleState.h"
#include "PlayerFallingState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"

PlayerClimbingThrowAppleState::PlayerClimbingThrowAppleState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}

PlayerClimbingThrowAppleState::~PlayerClimbingThrowAppleState()
{

}

void PlayerClimbingThrowAppleState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(false);
	}
	else if (keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(true);
	}
	else
	{
		this->mPlayerData->player->SetVx(0);
	}
}

void PlayerClimbingThrowAppleState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//if ((impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Pot) &&
	//	!this->mPlayerData->player->allowImunity)
	//{
	//	this->mPlayerData->player->bloodOfEntity--;
	//}
}

PlayerState::StateName PlayerClimbingThrowAppleState::GetState()
{
	return PlayerState::ClimbingThrowApple;
}