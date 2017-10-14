#include "PlayerSittingAttackState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"

PlayerSittingAttackState::PlayerSittingAttackState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
}

PlayerSittingAttackState::~PlayerSittingAttackState()
{

}

void PlayerSittingAttackState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
	}
}

void PlayerSittingAttackState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

PlayerState::StateName PlayerSittingAttackState::GetState()
{
	return PlayerState::SittingAttack;
}