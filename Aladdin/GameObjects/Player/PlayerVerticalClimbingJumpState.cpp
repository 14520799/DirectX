#include "PlayerVerticalClimbingJumpState.h"
#include "PlayerFallingState.h"
#include "PlayerVerticalClimbingDefaultState.h"
#include "PlayerHorizontalClimbingDefaultState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"
#include "../../GameObjects/MapObjects/Item.h"

PlayerVerticalClimbingJumpState::PlayerVerticalClimbingJumpState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	noPressed = false;
}


PlayerVerticalClimbingJumpState::~PlayerVerticalClimbingJumpState()
{

}

void PlayerVerticalClimbingJumpState::Update(float dt)
{
	this->mPlayerData->player->AddVy(Define::PLAYER_JUMP_SPEED_Y);

	if (mPlayerData->player->GetVy() >= Define::PLAYER_MAX_JUMP_VELOCITY)
		mPlayerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);

	if (noPressed)
	{
		if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
		{
			//player dang di chuyen sang ben trai      
			if (mPlayerData->player->GetVx() < 0)
			{
				this->mPlayerData->player->AddVx(Define::PLAYER_NORMAL_SPEED_X);

				if (mPlayerData->player->GetVx() > 0)
					this->mPlayerData->player->SetVx(0);
			}
		}
		else if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
		{
			//player dang di chuyen sang phai   
			if (mPlayerData->player->GetVx() > 0)
			{
				this->mPlayerData->player->AddVx(-Define::PLAYER_NORMAL_SPEED_X);

				if (mPlayerData->player->GetVx() < 0)
					this->mPlayerData->player->SetVx(0);
			}
		}
	}
}

void PlayerVerticalClimbingJumpState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(true);

		//di chuyen sang phai
		if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
		{
			this->mPlayerData->player->AddVx(Define::PLAYER_NORMAL_SPEED_X * 2);

			if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}

		noPressed = false;
	}
	else if (keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(false);

		//di chuyen sang trai
		if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
		{
			this->mPlayerData->player->AddVx(-Define::PLAYER_NORMAL_SPEED_X * 2);

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

void PlayerVerticalClimbingJumpState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::VerticalRope)
	{
		if (this->mPlayerData->player->GetVy() >= 0)
		{
			this->mPlayerData->player->SetPosition(impactor->GetPosition().x, this->mPlayerData->player->GetPosition().y);
			this->mPlayerData->player->SetState(new PlayerVerticalClimbingDefaultState(this->mPlayerData));
			return;
		}
	}
	//else if (impactor->Tag == Entity::EntityTypes::HorizontalRope)
	//{
	//	//this->mPlayerData->player->SetPosition(this->mPlayerData->player->GetPosition().x, impactor->GetPosition().y + (this->mPlayerData->player->GetPosition().y - impactor->GetPosition().y));
	//	this->mPlayerData->player->SetState(new PlayerHorizontalClimbingDefaultState(this->mPlayerData));
	//}
	else if (impactor->Tag == Entity::EntityTypes::Apple)
	{
		this->mPlayerData->player->collisionApple = true;
	}
	else if (impactor->Tag == Entity::EntityTypes::Guard)
	{

	}
	else
	{
		switch (side)
		{
		case Entity::Left:
			this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			this->mPlayerData->player->SetVx(0);
			break;
		

		case Entity::Right:
			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			this->mPlayerData->player->SetVx(0);
			break;
		
		case Entity::Top: case Entity::TopLeft: case Entity::TopRight:
			this->mPlayerData->player->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
			break;

		case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));
			break;
		

		default:
			break;
		}
	}
}

PlayerState::StateName PlayerVerticalClimbingJumpState::GetState()
{
	return PlayerState::VerticalClimbingJump;
}