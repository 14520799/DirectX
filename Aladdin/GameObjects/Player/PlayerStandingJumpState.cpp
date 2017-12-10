#include "PlayerStandingJumpState.h"
#include "PlayerDefaultState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "PlayerSomersaultState.h"
#include "PlayerVerticalClimbingDefaultState.h"
#include "PlayerHorizontalClimbingDefaultState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"
#include "../../GameObjects/MapObjects/Weapons/AppleWeapon.h"

PlayerStandingJumpState::PlayerStandingJumpState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->AddPosition(0, -5);
	if (this->mPlayerData->player->collisionObjectMap)
	{
		this->mPlayerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY * 1.5f);
		this->mPlayerData->player->collisionObjectMap = false;
	}
	else
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

void PlayerStandingJumpState::HandleKeyboard(std::map<int, bool> keys)
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
		this->mPlayerData->player->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
	}
	else if ((impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Pot) &&
		!this->mPlayerData->player->allowImunity)
	{
		this->mPlayerData->player->bloodOfEntity--;
	}
	else if (impactor->Tag == Entity::EntityTypes::Item)
	{
		if (impactor->Id == Entity::EntityId::Revitalization_Default || impactor->Id == Entity::EntityId::Feddler_Standing)
			return;
		else if (impactor->Id == Entity::EntityId::Lamp)
			this->mPlayerData->player->effectLamp = true;
		else if (impactor->Id == Entity::EntityId::HeadGenie || impactor->Id == Entity::EntityId::Life)
			this->mPlayerData->player->effectSpecial = true;
		this->mPlayerData->player->allowItemEffect = true;
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
	else if (impactor->Tag == Entity::EntityTypes::DownStairsControl || impactor->Tag == Entity::EntityTypes::UpStairsControl ||
		impactor->Tag == Entity::EntityTypes::FallControl || impactor->Tag == Entity::EntityTypes::OrokuControl ||
		impactor->Tag == Entity::EntityTypes::FireControl)
	{

	}
	else
	{
		switch (side)
		{
		case Entity::Left:  case Entity::TopLeft: case Entity::BottomLeft:
			this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			this->mPlayerData->player->SetVx(0);
			break;


		case Entity::Right: case Entity::TopRight: case Entity::BottomRight:
			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			this->mPlayerData->player->SetVx(0);
			break;

		case Entity::Top:
			break;

		case Entity::Bottom:
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

PlayerState::StateName PlayerStandingJumpState::GetState()
{
	return PlayerState::StandingJump;
}