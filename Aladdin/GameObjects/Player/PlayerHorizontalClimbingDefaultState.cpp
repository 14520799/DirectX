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
	else if (keys[VK_DOWN])
	{
		this->mPlayerData->player->AddPosition(0, (this->mPlayerData->player->GetBound().bottom - this->mPlayerData->player->GetBound().top) / 2);
		this->mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));
	}
	else
	{
		this->mPlayerData->player->SetVx(0);
	}
}

void PlayerHorizontalClimbingDefaultState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

PlayerState::StateName PlayerHorizontalClimbingDefaultState::GetState()
{
	return PlayerState::HorizontalClimbingDefault;
}