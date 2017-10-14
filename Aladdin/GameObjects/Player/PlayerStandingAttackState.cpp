#include "PlayerStandingAttackState.h"
#include "PlayerStandingState.h"
#include "PlayerRunningState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"

PlayerStandingAttackState::PlayerStandingAttackState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
}

PlayerStandingAttackState::~PlayerStandingAttackState()
{

}

void PlayerStandingAttackState::HandleKeyboard(std::map<int, bool> keys)
{

}

void PlayerStandingAttackState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

PlayerState::StateName PlayerStandingAttackState::GetState()
{
	return PlayerState::StandingAttack;
}