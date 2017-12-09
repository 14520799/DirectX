#include "PlayerFallingState.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerDefaultState.h"
#include "PlayerStandingJumpState.h"
#include "PlayerSittingState.h"
#include "PlayerSomersaultState.h"
#include "PlayerVerticalClimbingState.h"
#include "PlayerDeathState.h"
#include "PlayerFallingStopState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"
#include "../MapObjects/Weapons/AppleWeapon.h"

PlayerFallingState::PlayerFallingState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
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

	if (noPressed)
	{
		if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
		{
			//player dang di chuyen sang ben trai      
			this->mPlayerData->player->AddVx(Define::PLAYER_RUN_SPEED_X);

			if (mPlayerData->player->GetVx() > 0)
				this->mPlayerData->player->SetVx(0);
		}
		else if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
		{
			//player dang di chuyen sang phai   
			this->mPlayerData->player->AddVx(-Define::PLAYER_RUN_SPEED_X);

			if (mPlayerData->player->GetVx() < 0)
				this->mPlayerData->player->SetVx(0);
		}
	}
}

void PlayerFallingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(false);

		if (this->mPlayerData->player->allowMoveRight)
		{
			//di chuyen sang phai
			if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_JUMPING_SPEED)
			{
				this->mPlayerData->player->AddVx(Define::PLAYER_JUMP_SPEED_X);

				if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_JUMPING_SPEED)
				{
					this->mPlayerData->player->SetVx(Define::PLAYER_MAX_JUMPING_SPEED);
				}

				this->mPlayerData->player->allowMoveLeft = true;
			}
		}

		noPressed = false;
	}
	else if (keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(true);

		if (this->mPlayerData->player->allowMoveLeft)
		{
			//di chuyen sang trai
			if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_JUMPING_SPEED)
			{
				this->mPlayerData->player->AddVx(-Define::PLAYER_JUMP_SPEED_X);

				if (this->mPlayerData->player->GetVx() < -Define::PLAYER_MAX_JUMPING_SPEED)
				{
					this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_JUMPING_SPEED);
				}

				this->mPlayerData->player->allowMoveRight = true;
			}
		}

		noPressed = false;
	}
	else
	{
		noPressed = true;
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
	else if (impactor->Tag == Entity::EntityTypes::Item)
	{
		if (impactor->Id == Entity::EntityId::Revitalization_Default || impactor->Id == Entity::EntityId::Feddler_Standing)
			return;
		else if (impactor->Id == Entity::EntityId::Lamp)
			this->mPlayerData->player->effectLamp = true;
		else if (impactor->Id == Entity::EntityId::HeadGenie || impactor->Id == Entity::EntityId::Life)
			this->mPlayerData->player->effectSpecial = true;
		this->mPlayerData->player->allowEffect = true;
		this->mPlayerData->player->collisionItem = true;
		this->mPlayerData->player->mOriginPositionItem = impactor->GetPosition();
		if (impactor->Id == Entity::EntityId::AppleItem)
		{
			this->mPlayerData->player->apple = new AppleWeapon();
			this->mPlayerData->player->mListApplePlayer.push_back(this->mPlayerData->player->apple);
		}
	}
	else if (impactor->Id == Entity::EntityId::Camel || impactor->Tag == Entity::EntityTypes::Spring)
	{
		switch (side)
		{
		case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
			if (impactor->Tag == Entity::EntityTypes::Spring)
				this->mPlayerData->player->SetState(new PlayerSomersaultState(this->mPlayerData));
			else if (impactor->Id == Entity::EntityId::Camel)
				this->mPlayerData->player->SetState(new PlayerStandingJumpState(this->mPlayerData));
			break;

		default:
			break;
		}
	}
	else if ((impactor->Tag == Entity::EntityTypes::Oroku && impactor->Id != Entity::EntityId::Camel) ||
		impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Pot)
	{

	}
	else if (impactor->Tag == Entity::EntityTypes::UpStairsControl || impactor->Tag == Entity::EntityTypes::DownStairsControl ||
		impactor->Tag == Entity::EntityTypes::GroundControl || impactor->Tag == Entity::EntityTypes::FallControl)
	{

	}
	else if (impactor->Tag == Entity::EntityTypes::ObjStairs)
	{
		switch (side)
		{
		case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			if (noPressed)
				this->mPlayerData->player->SetState(new PlayerDefaultState(this->mPlayerData));
			else
				this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
			break;
		}
	}
	else
	{
		switch (side)
		{
		case Entity::Left:
			this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			this->mPlayerData->player->allowMoveLeft = false;
			this->mPlayerData->player->SetVx(0);
			break;

		case Entity::Right:
			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			this->mPlayerData->player->allowMoveRight = false;
			this->mPlayerData->player->SetVx(0);
			break;

		case Entity::Top:
			break;

		case Entity::Bottom:
		case Entity::BottomRight:
		case Entity::BottomLeft:
			//this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			if (noPressed)
			{
				if (this->mPlayerData->player->GetVy() >= Define::PLAYER_MAX_JUMP_VELOCITY - 10)
					this->mPlayerData->player->SetState(new PlayerFallingStopState(this->mPlayerData));
				else
					this->mPlayerData->player->SetState(new PlayerDefaultState(this->mPlayerData));
			}
			else
				this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
			break;

		default:
			break;
		}
	}

}

PlayerState::StateName PlayerFallingState::GetState()
{
	return PlayerState::Falling;
}
