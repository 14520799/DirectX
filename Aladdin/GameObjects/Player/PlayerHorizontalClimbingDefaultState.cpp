#include "PlayerHorizontalClimbingDefaultState.h"
#include "PlayerHorizontalClimbingState.h"
#include "PlayerFallingState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"

PlayerHorizontalClimbingDefaultState::PlayerHorizontalClimbingDefaultState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}

PlayerHorizontalClimbingDefaultState::~PlayerHorizontalClimbingDefaultState()
{

}

void PlayerHorizontalClimbingDefaultState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		this->mPlayerData->player->SetState(new PlayerHorizontalClimbingState(this->mPlayerData));
		return;
	}
	else
	{
		this->mPlayerData->player->SetVx(0);
	}
}

void PlayerHorizontalClimbingDefaultState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::HorizontalRope)
		this->mPlayerData->player->SetPosition(this->mPlayerData->player->GetPosition().x, impactor->GetPosition().y + this->mPlayerData->player->GetHeight() / 2);
	//else if ((impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Pot) &&
	//	!this->mPlayerData->player->allowImunity)
	//{
	//	this->mPlayerData->player->bloodOfEntity--;
	//}
}

PlayerState::StateName PlayerHorizontalClimbingDefaultState::GetState()
{
	return PlayerState::HorizontalClimbingDefault;
}