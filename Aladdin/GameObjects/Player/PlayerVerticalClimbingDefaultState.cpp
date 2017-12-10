#include "PlayerVerticalClimbingDefaultState.h"
#include "PlayerVerticalClimbingState.h"
#include "PlayerFallingState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"

PlayerVerticalClimbingDefaultState::PlayerVerticalClimbingDefaultState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}

PlayerVerticalClimbingDefaultState::~PlayerVerticalClimbingDefaultState()
{

}

void PlayerVerticalClimbingDefaultState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_DOWN] || keys[VK_UP])
	{
		this->mPlayerData->player->SetState(new PlayerVerticalClimbingState(this->mPlayerData));
	}
	else if (keys[VK_RIGHT])
	{
		this->mPlayerData->player->SetReverse(true);
	}
	else if (keys[VK_LEFT])
	{
		this->mPlayerData->player->SetReverse(false);
	}
	else
	{
		this->mPlayerData->player->SetVy(0);
	}
}

void PlayerVerticalClimbingDefaultState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::VerticalRopeControl)
		this->mPlayerData->player->SetPosition(impactor->GetPosition().x, impactor->GetPosition().y + this->mPlayerData->player->GetHeight() / 2);
	else if ((impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Pot) &&
		!this->mPlayerData->player->allowImunity)
	{
		this->mPlayerData->player->bloodOfEntity--;
	}
}

PlayerState::StateName PlayerVerticalClimbingDefaultState::GetState()
{
	return PlayerState::VerticalClimbingDefault;
}