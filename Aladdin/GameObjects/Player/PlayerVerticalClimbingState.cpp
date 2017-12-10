#include "PlayerVerticalClimbingState.h"
#include "PlayerVerticalClimbingDefaultState.h"
#include "PlayerFallingState.h"
#include "../MapObjects/Weapons/AppleWeapon.h"
#include "../../GameDefines/GameDefine.h"
#include "../../GameComponents/GameCollision.h"

PlayerVerticalClimbingState::PlayerVerticalClimbingState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}

PlayerVerticalClimbingState::~PlayerVerticalClimbingState()
{

}

void PlayerVerticalClimbingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_UP])
	{
		if (mPlayerData->player->allowMoveUp)
		{
			if (this->mPlayerData->player->GetVy() > -Define::PLAYER_MAX_VERTICAL_CLIMBING_SPEED)
			{
				this->mPlayerData->player->AddVy(-Define::PLAYER_CLIM_SPPED);

				if (this->mPlayerData->player->GetVy() <= -Define::PLAYER_MAX_VERTICAL_CLIMBING_SPEED)
				{
					this->mPlayerData->player->SetVy(-Define::PLAYER_MAX_VERTICAL_CLIMBING_SPEED);
				}
			}
		}
	}
	else if (keys[VK_DOWN])
	{
		if (this->mPlayerData->player->GetVy() < Define::PLAYER_MAX_VERTICAL_CLIMBING_SPEED)
		{
			this->mPlayerData->player->AddVy(Define::PLAYER_CLIM_SPPED);

			if (this->mPlayerData->player->GetVy() > Define::PLAYER_MAX_VERTICAL_CLIMBING_SPEED)
			{
				this->mPlayerData->player->SetVy(Define::PLAYER_MAX_VERTICAL_CLIMBING_SPEED);
			}
		}
	}
	else
	{
		this->mPlayerData->player->SetState(new PlayerVerticalClimbingDefaultState(this->mPlayerData));
	}

}

void PlayerVerticalClimbingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::Item)
	{
		if (impactor->Id == Entity::EntityId::Revitalization_Default || impactor->Id == Entity::EntityId::Feddler_Standing)
			return;
		this->mPlayerData->player->allowItemEffect = true;
		this->mPlayerData->player->collisionItem = true;
		this->mPlayerData->player->mOriginPositionItem = impactor->GetPosition();
		if (impactor->Id == Entity::EntityId::AppleItem)
		{
			this->mPlayerData->player->apple = new AppleWeapon();
			this->mPlayerData->player->mListApplePlayer.push_back(this->mPlayerData->player->apple);
		}
	}
	if (impactor->Tag != Entity::EntityTypes::VerticalRope)
	{
		switch (side)
		{
		case Entity::Top: case Entity::TopLeft: case Entity::TopRight:
			this->mPlayerData->player->allowMoveUp = false;
			this->mPlayerData->player->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
			break;

		case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));
			break;

		default:
			break;
		}
	}
	else if ((impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Pot) &&
		!this->mPlayerData->player->allowImunity)
	{
		this->mPlayerData->player->bloodOfEntity--;
	}
}

PlayerState::StateName PlayerVerticalClimbingState::GetState()
{
	return PlayerState::VerticalClimbing;
}