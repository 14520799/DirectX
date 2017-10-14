#include "PlayerHorizontalClimbingState.h"
#include "PlayerFallingState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"

PlayerHorizontalClimbingState::PlayerHorizontalClimbingState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);

	accelaretorX = 15.0f;

	this->mPlayerData->player->allowMoveLeft = true;
	this->mPlayerData->player->allowMoveRight = true;
}

PlayerHorizontalClimbingState::~PlayerHorizontalClimbingState()
{

}

void PlayerHorizontalClimbingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT])
	{
		if (mPlayerData->player->allowMoveLeft)
		{
			mPlayerData->player->SetReverse(false);
			mPlayerData->player->allowMoveRight = true;

			if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_HORIZONTAL_CLIMBING_SPEED)
			{
				this->mPlayerData->player->AddVx(-accelaretorX);

				if (this->mPlayerData->player->GetVx() <= -Define::PLAYER_MAX_HORIZONTAL_CLIMBING_SPEED)
				{
					this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_HORIZONTAL_CLIMBING_SPEED);
				}
			}
		}
	}
	else if (keys[VK_RIGHT])
	{
		if (mPlayerData->player->allowMoveRight)
		{
			mPlayerData->player->SetReverse(true);
			mPlayerData->player->allowMoveLeft = true;

			if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_HORIZONTAL_CLIMBING_SPEED)
			{
				this->mPlayerData->player->AddVx(accelaretorX);

				if (this->mPlayerData->player->GetVx() > Define::PLAYER_MAX_HORIZONTAL_CLIMBING_SPEED)
				{
					this->mPlayerData->player->SetVx(Define::PLAYER_MAX_HORIZONTAL_CLIMBING_SPEED);
				}
			}
		}
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

void PlayerHorizontalClimbingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	switch (side)
	{
		case Entity::Left:
			//va cham phia ben trai player
			if (this->mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
			{
				this->mPlayerData->player->allowMoveLeft = false;
				//day Player ra phia ben phai de cho player khong bi xuyen qua object
				this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			}
			break;

		case Entity::Right:
			//va cham phia ben phai player
			if (this->mPlayerData->player->getMoveDirection() == Player::MoveToRight)
			{
				this->mPlayerData->player->allowMoveRight = false;
				this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			}
			break;

		default:
			break;
	}
}

PlayerState::StateName PlayerHorizontalClimbingState::GetState()
{
	return PlayerState::HorizontalClimbing;
}