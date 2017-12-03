#include "PlayerStandingThrowAppleState.h"
#include "PlayerDeathState.h"
#include "../../GameComponents/GameCollision.h"

PlayerStandingThrowAppleState::PlayerStandingThrowAppleState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
}

PlayerStandingThrowAppleState::~PlayerStandingThrowAppleState()
{

}

void PlayerStandingThrowAppleState::HandleKeyboard(std::map<int, bool> keys)
{

}

void PlayerStandingThrowAppleState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if ((impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Pot || 
		impactor->Tag == Entity::EntityTypes::Fire) &&
		!this->mPlayerData->player->allowImunity)
	{
		this->mPlayerData->player->bloodOfEntity--;
	}
	else if (impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Oroku ||
		impactor->Tag == Entity::EntityTypes::Fire || impactor->Tag == Entity::EntityTypes::FallControl)
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

		case Entity::Top:
			break;

		case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->SetVy(0);
			break;
		}
	}
}

PlayerState::StateName PlayerStandingThrowAppleState::GetState()
{
	return PlayerState::StandingThrowApple;
}