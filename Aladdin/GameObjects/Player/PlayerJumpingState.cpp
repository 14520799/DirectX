#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "PlayerVerticalClimbingState.h"
#include "PlayerHorizontalClimbingState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"

PlayerJumpingState::PlayerJumpingState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);

	acceleratorY = 30.0f;
	acceleratorX = 15.0f;

	noPressed = false;
}


PlayerJumpingState::~PlayerJumpingState()
{

}

void PlayerJumpingState::Update(float dt)
{
	this->mPlayerData->player->AddVy(acceleratorY);

	if (mPlayerData->player->GetVy() >= 0)
	{
		mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));

		return;
	}

	if (noPressed)
	{
		if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
		{
			//player dang di chuyen sang ben trai      
			if (mPlayerData->player->GetVx() < 0)
			{
				this->mPlayerData->player->AddVx(acceleratorX);

				if (mPlayerData->player->GetVx() > 0)
					this->mPlayerData->player->SetVx(0);
			}
		}
		else if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
		{
			//player dang di chuyen sang phai   
			if (mPlayerData->player->GetVx() > 0)
			{
				this->mPlayerData->player->AddVx(-acceleratorX);

				if (mPlayerData->player->GetVx() < 0)
					this->mPlayerData->player->SetVx(0);
			}
		}
	}
}

void PlayerJumpingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(false);

		//di chuyen sang phai
		if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
		{
			this->mPlayerData->player->AddVx(acceleratorX);

			if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}

		noPressed = false;
	}
	else if (keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(true);

		//di chuyen sang trai
		if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
		{
			this->mPlayerData->player->AddVx(-acceleratorX);

			if (this->mPlayerData->player->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}

		noPressed = false;
	}
	else
	{
		noPressed = true;
	}
}

void PlayerJumpingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::VerticalRope)
	{
		this->mPlayerData->player->SetPosition(impactor->GetPosition().x, this->mPlayerData->player->GetPosition().y);
		this->mPlayerData->player->SetState(new PlayerVerticalClimbingState(this->mPlayerData));
	}
	else if (impactor->Tag == Entity::EntityTypes::HorizontalRope)
	{
		//this->mPlayerData->player->SetPosition(this->mPlayerData->player->GetPosition().x, impactor->GetPosition().y + (this->mPlayerData->player->GetPosition().y - impactor->GetPosition().y));
		this->mPlayerData->player->SetState(new PlayerHorizontalClimbingState(this->mPlayerData));
	}
	else
	{
		switch (side)
		{
			case Entity::Left:
			{
				this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
				this->mPlayerData->player->SetVx(0);
				break;
			}

			case Entity::Right:
			{
				this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
				this->mPlayerData->player->SetVx(0);
				break;
			}

			case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
			{
				this->mPlayerData->player->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
				this->mPlayerData->player->SetVy(0);
				break;
			}

			case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
			{
				this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
				break;
			}

			default:
				break;
		}
	}
}

PlayerState::StateName PlayerJumpingState::GetState()
{
	return PlayerState::Jumping;
}