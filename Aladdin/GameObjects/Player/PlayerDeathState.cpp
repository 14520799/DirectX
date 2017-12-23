#include "PlayerDeathState.h"
#include "PlayerRevivalState.h"

PlayerDeathState::PlayerDeathState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
	this->mPlayerData->player->SetReverse(false);
	timeDelay = 0;
}


PlayerDeathState::~PlayerDeathState()
{
}

void PlayerDeathState::Update(float dt)
{
	timeDelay += dt;
	if (timeDelay > 3.0f)
	{
		if (this->mPlayerData->player->collisionRevitalization)
			this->mPlayerData->player->SetState(new PlayerRevivalState(this->mPlayerData));
		else
			this->mPlayerData->player->InitPlayer();
	}
}

void PlayerDeathState::HandleKeyboard(std::map<int, bool> keys)
{

}

void PlayerDeathState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	
}

PlayerState::StateName PlayerDeathState::GetState()
{
    return PlayerState::Death;
}