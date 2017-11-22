#include "PlayerRunningJumpState.h"
#include "PlayerDefaultState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "PlayerVerticalClimbingDefaultState.h"
#include "PlayerHorizontalClimbingDefaultState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"
#include "../../GameObjects/MapObjects/Item.h"

PlayerRunningJumpState::PlayerRunningJumpState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	noPressed = false;
}


PlayerRunningJumpState::~PlayerRunningJumpState()
{

}

void PlayerRunningJumpState::Update(float dt)
{
	this->mPlayerData->player->AddVy(Define::PLAYER_FALL_SPEED_Y);

	if (mPlayerData->player->GetVy() >= Define::PLAYER_MAX_JUMP_VELOCITY + 100)
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
				this->mPlayerData->player->AddVx(Define::PLAYER_RUN_SPEED_X);

				if (mPlayerData->player->GetVx() > 0)
					this->mPlayerData->player->SetVx(0);
			}
		}
		else if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
		{
			//player dang di chuyen sang phai   
			if (mPlayerData->player->GetVx() > 0)
			{
				this->mPlayerData->player->AddVx(-Define::PLAYER_RUN_SPEED_X);

				if (mPlayerData->player->GetVx() < 0)
					this->mPlayerData->player->SetVx(0);
			}
		}
	}
}

void PlayerRunningJumpState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(false);

		//di chuyen sang phai
		if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_JUMPING_SPEED)
		{
			this->mPlayerData->player->AddVx(Define::PLAYER_JUMP_SPEED_X);

			if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_JUMPING_SPEED)
			{
				this->mPlayerData->player->SetVx(Define::PLAYER_MAX_JUMPING_SPEED);
			}
		}

		noPressed = false;
	}
	else if (keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(true);

		//di chuyen sang trai
		if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_JUMPING_SPEED)
		{
			this->mPlayerData->player->AddVx(-Define::PLAYER_JUMP_SPEED_X);

			if (this->mPlayerData->player->GetVx() < -Define::PLAYER_MAX_JUMPING_SPEED)
			{
				this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_JUMPING_SPEED);
			}
		}

		noPressed = false;
	}
	else
	{
		noPressed = true;
	}
}

void PlayerRunningJumpState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::GroundControl)
	{
		this->mPlayerData->player->CurrentMoveStairs = Entity::EntityCurrentMoveStairs::CurrentGround;
		return;
	}


	if (impactor->Tag == Entity::EntityTypes::VerticalRope)
	{
		this->mPlayerData->player->SetPosition(impactor->GetPosition().x, this->mPlayerData->player->GetPosition().y);
		this->mPlayerData->player->SetState(new PlayerVerticalClimbingDefaultState(this->mPlayerData));
	}
	else if (impactor->Tag == Entity::EntityTypes::HorizontalRope)
	{
		//this->mPlayerData->player->SetPosition(this->mPlayerData->player->GetPosition().x, impactor->GetPosition().y + (this->mPlayerData->player->GetPosition().y - impactor->GetPosition().y));
		this->mPlayerData->player->SetState(new PlayerHorizontalClimbingDefaultState(this->mPlayerData));
	}
	else if (impactor->Tag == Entity::EntityTypes::Apple)
	{
		this->mPlayerData->player->collisionApple = true;
	}
	else if (impactor->Tag == Entity::EntityTypes::Guard)
	{

	}
	else if (impactor->Tag == Entity::EntityTypes::DownStairsControl || impactor->Tag == Entity::EntityTypes::UpStairsControl)
	{

	}
	else
	{
		switch (side)
		{
			case Entity::Left:
				this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
				this->mPlayerData->player->SetVx(0);
				this->mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));
				break;

			case Entity::Right:
				this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
				this->mPlayerData->player->SetVx(0);
				this->mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));
				break;

			case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
				this->mPlayerData->player->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
				this->mPlayerData->player->SetVy(0);
				this->mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));
				break;

			case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
				this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
				break;

			default:
				break;
		}
	}
}

PlayerState::StateName PlayerRunningJumpState::GetState()
{
	return PlayerState::RunningJump;
}
