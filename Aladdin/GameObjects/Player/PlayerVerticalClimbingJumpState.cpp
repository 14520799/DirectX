#include "PlayerVerticalClimbingJumpState.h"
#include "PlayerFallingState.h"
#include "PlayerDefaultState.h"
#include "PlayerVerticalClimbingDefaultState.h"
#include "PlayerHorizontalClimbingDefaultState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"
#include "../MapObjects/Weapons/AppleWeapon.h"

PlayerVerticalClimbingJumpState::PlayerVerticalClimbingJumpState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY - 50);
	noPressed = false;
}


PlayerVerticalClimbingJumpState::~PlayerVerticalClimbingJumpState()
{

}

void PlayerVerticalClimbingJumpState::Update(float dt)
{
	this->mPlayerData->player->AddVy(Define::PLAYER_FALL_SPEED_Y);

	if (mPlayerData->player->GetVy() >= Define::PLAYER_MAX_JUMP_VELOCITY)
		mPlayerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);

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

void PlayerVerticalClimbingJumpState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(true);

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
		mPlayerData->player->SetReverse(false);

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

void PlayerVerticalClimbingJumpState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::HorizontalRope)
	{
		this->mPlayerData->player->SetPosition(this->mPlayerData->player->GetPosition().x, impactor->GetPosition().y + this->mPlayerData->player->GetHeight() / 2);
		this->mPlayerData->player->SetState(new PlayerHorizontalClimbingDefaultState(this->mPlayerData));
	}
	else if (impactor->Tag == Entity::EntityTypes::VerticalRope)
	{
		if (this->mPlayerData->player->GetVy() >= 0)
		{
			this->mPlayerData->player->SetPosition(impactor->GetPosition().x, this->mPlayerData->player->GetPosition().y);
			this->mPlayerData->player->SetState(new PlayerVerticalClimbingDefaultState(this->mPlayerData));
		}
	}
	//else if ((impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Pot) &&
	//	!this->mPlayerData->player->allowImunity)
	//{
	//	this->mPlayerData->player->bloodOfEntity--;
	//}
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
	else if (impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Oroku ||
		impactor->Tag == Entity::EntityTypes::Pot || impactor->Tag == Entity::EntityTypes::VerticalRopeControl)
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
			//this->mPlayerData->player->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
			break;

		case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			if (noPressed)
				this->mPlayerData->player->SetState(new PlayerDefaultState(this->mPlayerData));
			else
				this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
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