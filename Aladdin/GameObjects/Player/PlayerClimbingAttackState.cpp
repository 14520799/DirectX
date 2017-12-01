#include "PlayerClimbingAttackState.h"
#include "PlayerFallingState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"

PlayerClimbingAttackState::PlayerClimbingAttackState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}

PlayerClimbingAttackState::~PlayerClimbingAttackState()
{

}

void PlayerClimbingAttackState::HandleKeyboard(std::map<int, bool> keys)
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

void PlayerClimbingAttackState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::Guard)
	{
		this->mPlayerData->player->collisionWithOroku = true;
	}
	else if (impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Pot)
	{

	}
}

PlayerState::StateName PlayerClimbingAttackState::GetState()
{
	return PlayerState::ClimbingAttack;
}