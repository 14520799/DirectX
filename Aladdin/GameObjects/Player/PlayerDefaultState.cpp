#include "PlayerDefaultState.h"
#include "PlayerStandingState.h"
#include "PlayerRunningState.h"
#include "PlayerDeathState.h"

PlayerDefaultState::PlayerDefaultState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}


PlayerDefaultState::~PlayerDefaultState()
{
}

void PlayerDefaultState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		return;
	}
}

void PlayerDefaultState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::Fire && this->mPlayerData->player->allowDeath)
	{
		this->mPlayerData->player->SetState(new PlayerDeathState(this->mPlayerData));
	}
	else if (impactor->Tag == Entity::EntityTypes::Sword && this->mPlayerData->player->allowDeath)
	{
		this->mPlayerData->player->SetState(new PlayerDeathState(this->mPlayerData));
	}
	else if (impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Guard)
	{

	}
	else
	{
		switch (side)
		{
		case Entity::Left:
			this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			break;

		case Entity::Right:
			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			break;

		case Entity::Top: case Entity::TopLeft: case Entity::TopRight:
			this->mPlayerData->player->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
			break;

		case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->SetVy(0);
			break;
		}
	}
}

PlayerState::StateName PlayerDefaultState::GetState()
{
	return PlayerState::Default;
}