#include "PlayerStandingJumpState.h"
#include "PlayerDefaultState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "PlayerVerticalClimbingDefaultState.h"
#include "PlayerHorizontalClimbingDefaultState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"
#include "../../GameObjects/MapObjects/Weapons/AppleWeapon.h"

PlayerStandingJumpState::PlayerStandingJumpState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->AddPosition(0, -10);
	this->mPlayerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	noPressed = false;
}


PlayerStandingJumpState::~PlayerStandingJumpState()
{

}

void PlayerStandingJumpState::Update(float dt)
{
	this->mPlayerData->player->AddVy(Define::PLAYER_FALL_SPEED_Y);

	if (mPlayerData->player->GetVy() >= Define::PLAYER_MAX_JUMP_VELOCITY)
	{
		this->mPlayerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
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

void PlayerStandingJumpState::HandleKeyboard(std::map<int, bool> keys)
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

void PlayerStandingJumpState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
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
	else if (impactor->Tag == Entity::EntityTypes::Item && impactor->Id != Entity::EntityId::Revitalization_Default)
	{
		this->mPlayerData->player->allowEffect = true;
		this->mPlayerData->player->collisionItem = true;
		this->mPlayerData->player->mOriginPositionItem = impactor->GetPosition();
		if (impactor->Id == Entity::EntityId::AppleItem)
		{
			this->mPlayerData->player->apple = new AppleWeapon();
			this->mPlayerData->player->mListApplePlayer.push_back(this->mPlayerData->player->apple);
		}
	}
	else if (impactor->Id == Entity::EntityId::Camel)
	{
		switch (side)
		{
		case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
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
	else if (impactor->Tag == Entity::EntityTypes::DownStairsControl || impactor->Tag == Entity::EntityTypes::UpStairsControl ||
		impactor->Tag == Entity::EntityTypes::FallControl)
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

		case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
			this->mPlayerData->player->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
			this->mPlayerData->player->SetVy(0);
			break;

		case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->SetState(new PlayerDefaultState(this->mPlayerData));

		default:
			break;
		}
	}
}

PlayerState::StateName PlayerStandingJumpState::GetState()
{
	return PlayerState::StandingJump;
}