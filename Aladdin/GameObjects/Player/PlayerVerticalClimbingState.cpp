#include "PlayerVerticalClimbingState.h"
#include "PlayerFallingState.h"
#include "../../GameDefines/GameDefine.h"
#include "../../GameComponents/GameCollision.h"

PlayerVerticalClimbingState::PlayerVerticalClimbingState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);

	acceleratorY = 15.0f;

	this->mPlayerData->player->allowMoveUp = true;
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
				this->mPlayerData->player->AddVy(-acceleratorY);

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
			this->mPlayerData->player->AddVy(acceleratorY);

			if (this->mPlayerData->player->GetVy() > Define::PLAYER_MAX_VERTICAL_CLIMBING_SPEED)
			{
				this->mPlayerData->player->SetVy(Define::PLAYER_MAX_VERTICAL_CLIMBING_SPEED);
			}
		}
	}
	else if (keys[VK_LEFT])
	{
		this->mPlayerData->player->AddPosition(this->mPlayerData->player->GetBound().left - this->mPlayerData->player->GetBound().right, 0);
		this->mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));
	}
	else if (keys[VK_RIGHT])
	{
		this->mPlayerData->player->AddPosition(this->mPlayerData->player->GetBound().right - this->mPlayerData->player->GetBound().left, 0);
		this->mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));
	}
	else
	{
		this->mPlayerData->player->SetVy(0);

	}
}

void PlayerVerticalClimbingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
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

}

PlayerState::StateName PlayerVerticalClimbingState::GetState()
{
	return PlayerState::VerticalClimbing;
}