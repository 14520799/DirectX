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
	
}

PlayerState::StateName PlayerClimbingAttackState::GetState()
{
	return PlayerState::ClimbingAttack;
}