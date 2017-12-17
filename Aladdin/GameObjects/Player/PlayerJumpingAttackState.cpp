#include "PlayerJumpingAttackState.h"
#include "PlayerDefaultState.h"
#include "PlayerStandingState.h"
#include "PlayerStandingJumpState.h"
#include "PlayerFallingState.h"
#include "PlayerSomersaultState.h"
#include "PlayerVerticalClimbingState.h"
#include "PlayerHorizontalClimbingState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"
#include "../MapObjects/Weapons/AppleWeapon.h"
#include "../../GameComponents/Sound.h"

PlayerJumpingAttackState::PlayerJumpingAttackState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
}

PlayerJumpingAttackState::~PlayerJumpingAttackState()
{

}

void PlayerJumpingAttackState::Update(float dt)
{
	this->mPlayerData->player->AddVy(Define::PLAYER_FALL_SPEED_Y);

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

void PlayerJumpingAttackState::HandleKeyboard(std::map<int, bool> keys)
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

void PlayerJumpingAttackState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
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
			{
				Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/SpringDoing.wav", "SpringDoing");
				Sound::getInstance()->play("SpringDoing", false, 1);
				this->mPlayerData->player->collisionSpring = true;
				this->mPlayerData->player->mOriginPositionItem = impactor->GetPosition();
				this->mPlayerData->player->SetState(new PlayerSomersaultState(this->mPlayerData));
			}
			else if (impactor->Id == Entity::EntityId::Camel)
			{
				Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/CamelSpit.wav", "CamelSpit");
				Sound::getInstance()->play("CamelSpit", false, 1);
				this->mPlayerData->player->SetState(new PlayerStandingJumpState(this->mPlayerData));
			}
			break;

		default:
			break;
		}
	}
	else if (impactor->Tag == Entity::EntityTypes::Oroku && impactor->Id != Entity::EntityId::Camel)
	{
		if (!impactor->allowImunity)
			this->mPlayerData->player->collisionWithOroku = true;
	}
	else if (impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Pot)
	{

	}
	else if (impactor->Tag == Entity::EntityTypes::DownStairsControl || impactor->Tag == Entity::EntityTypes::UpStairsControl ||
		impactor->Tag == Entity::EntityTypes::FallControl || impactor->Tag == Entity::EntityTypes::OrokuControl)
	{

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
			//this->mPlayerData->player->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
			break;
		}

		case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
		{
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->SetState(new PlayerDefaultState(this->mPlayerData));
			break;
		}

		default:
			break;
		}
	}
}

PlayerState::StateName PlayerJumpingAttackState::GetState()
{
	return PlayerState::JumpingAttack;
}