#include "PlayerFallingState.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerSittingState.h"
#include "PlayerVerticalClimbingState.h"
#include "PlayerDeathState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"

PlayerFallingState::PlayerFallingState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
}


PlayerFallingState::~PlayerFallingState()
{
}

void PlayerFallingState::Update(float dt)
{
    this->mPlayerData->player->AddVy(Define::PLAYER_FALL_SPEED_Y);

    if (mPlayerData->player->GetVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
    {
        mPlayerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
    }

	if (mPlayerData->player->GetVx() == 0)
	{
		allowMoveX = false;
	}
	else
	{
		allowMoveX = true;
	}
}

void PlayerFallingState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_RIGHT])
    {
		mPlayerData->player->SetReverse(false);

		if (allowMoveX)
		{
			isLeftOrRightKeyPressed = true;
			//di chuyen sang phai
			if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->mPlayerData->player->AddVx(Define::PLAYER_NORMAL_SPEED_X);

				if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
				{
					this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
				}
			}
		}     
    }
    else if (keys[VK_LEFT])
    {
		mPlayerData->player->SetReverse(true);

		if (allowMoveX)
		{
			isLeftOrRightKeyPressed = true;
			//di chuyen sang trai
			if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->mPlayerData->player->AddVx(-Define::PLAYER_NORMAL_SPEED_X);

				if (this->mPlayerData->player->GetVx() <= -Define::PLAYER_MAX_RUNNING_SPEED)
				{
					this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
				}
			}
		}
    }
    else
    {
        isLeftOrRightKeyPressed = false;    
    }
}

void PlayerFallingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
    //lay phia va cham so voi player
    //GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);
	if (impactor->Tag == Entity::EntityTypes::VerticalRope)
	{
		this->mPlayerData->player->SetPosition(impactor->GetPosition().x, this->mPlayerData->player->GetPosition().y);
		this->mPlayerData->player->SetState(new PlayerVerticalClimbingState(this->mPlayerData));
	}
	else if (impactor->Tag == Entity::EntityTypes::Apple)
	{
		this->mPlayerData->player->collisionApple = true;
	}
	else
	{
		switch (side)
		{
			case Entity::Left:
				if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
				{
					this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
					this->mPlayerData->player->SetVx(0);
				}
				break;

			case Entity::Right:
				if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
				{
					this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
					this->mPlayerData->player->SetVx(0);
				}
				break;

			case Entity::Top:
				break;

			case Entity::Bottom:
			case Entity::BottomRight:
			case Entity::BottomLeft:
				if (data.RegionCollision.right - data.RegionCollision.left >= 10.0f)
				{
					this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

					if (isLeftOrRightKeyPressed)
					{
						this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
					}
					else
					{
						this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
					}
				}
				return;

			default:
				break;
		}
	}
    
}

PlayerState::StateName PlayerFallingState::GetState()
{
    return PlayerState::Falling;
}
