#include "PlayerRunningState.h"
#include "PlayerRunningStopState.h"
#include "PlayerDeathState.h"
#include "PlayerDefaultState.h"
#include "PlayerFallingState.h"
#include "PlayerPushingState.h"
#include "PlayerVerticalClimbingDefaultState.h"
#include "../MapObjects/Weapons/AppleWeapon.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"

PlayerRunningState::PlayerRunningState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}


PlayerRunningState::~PlayerRunningState()
{
}

void PlayerRunningState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(false);

		//di chuyen sang phai
		if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
		{
			this->mPlayerData->player->AddVx(Define::PLAYER_RUN_SPEED_X);

			if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
	}
	else if (keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(true);

		//di chuyen sang trai
		if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
		{
			this->mPlayerData->player->AddVx(-Define::PLAYER_RUN_SPEED_X);

			if (this->mPlayerData->player->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
	}
	else
	{
		if (this->mPlayerData->player->GetVx() <= -Define::PLAYER_MAX_RUNNING_SPEED ||
			this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
			this->mPlayerData->player->SetState(new PlayerRunningStopState(this->mPlayerData));
		else
			this->mPlayerData->player->SetState(new PlayerDefaultState(this->mPlayerData));
		return;
	}
}

void PlayerRunningState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::GroundControl)
	{
		this->mPlayerData->player->CurrentMoveStairs = Entity::EntityCurrentMoveStairs::CurrentGround;
		return;
	}

	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);
	if ((impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Pot ||
		impactor->Tag == Entity::EntityTypes::Fire) &&
		!this->mPlayerData->player->allowImunity)
	{
		this->mPlayerData->player->bloodOfEntity--;
	}
	else if (impactor->Tag == Entity::EntityTypes::VerticalRope)
	{
		this->mPlayerData->player->SetPosition(impactor->GetPosition().x, this->mPlayerData->player->GetPosition().y);
		this->mPlayerData->player->SetState(new PlayerVerticalClimbingDefaultState(this->mPlayerData));
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
	else if (impactor->Tag == Entity::EntityTypes::ObjStairs)
	{
		switch (side)
		{
		case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->collisionObjectMap = true;
			break;
		}
	}
	else if (impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Oroku ||
		impactor->Tag == Entity::EntityTypes::Fire || impactor->Tag == Entity::EntityTypes::FallControl ||
		impactor->Tag == Entity::EntityTypes::OrokuControl || impactor->Tag == Entity::EntityTypes::FireControl ||
		impactor->Tag == Entity::EntityTypes::Spring || impactor->Tag == Entity::EntityTypes::Pot)
	{

	}
	else if (impactor->Tag == Entity::EntityTypes::DownStairsControl)
	{
		//khi trang thai cua player dang di tren dat -> tao cau thang downstairs -> de di len cau thang downstairs
		if (this->mPlayerData->player->CurrentMoveStairs == Entity::EntityCurrentMoveStairs::CurrentGround)
			this->mPlayerData->player->mMap->InsertDownStairs();
		//khi trang thai cua player dang di tren cau thang downstairs -> xoa cau thang downstairs -> di xuong dat
		else if (this->mPlayerData->player->CurrentMoveStairs == Entity::EntityCurrentMoveStairs::CurrentDownStairs)
			this->mPlayerData->player->mMap->RemoveDownStairs();
		this->mPlayerData->player->CurrentMoveStairs = Entity::EntityCurrentMoveStairs::CurrentNone;
	}
	else if (impactor->Tag == Entity::EntityTypes::UpStairsControl)
	{
		//khi trang thai cua player dang di tren cau thang downstairs -> tao cau thang upstairs -> de di len cau thang upstairs
		if (this->mPlayerData->player->CurrentMoveStairs == Entity::EntityCurrentMoveStairs::CurrentDownStairs)
			this->mPlayerData->player->mMap->InsertUpStairs();
		//khi trang thai cua player dang di tren cau thang upstairs -> xoa cau thang upstairs -> de di xuong cau thang downstairs
		else if (this->mPlayerData->player->CurrentMoveStairs == Entity::EntityCurrentMoveStairs::CurrentUpStairs)
			this->mPlayerData->player->mMap->RemoveUpStairs();
		this->mPlayerData->player->CurrentMoveStairs = Entity::EntityCurrentMoveStairs::CurrentNone;
	}
	else if (impactor->Tag == Entity::EntityTypes::DownStairs)
	{
		if (this->mPlayerData->player->CurrentMoveStairs == Entity::EntityCurrentMoveStairs::CurrentNone)
		{
			this->mPlayerData->player->CurrentMoveStairs = Entity::EntityCurrentMoveStairs::CurrentDownStairs;
		}
		switch (side)
		{
		case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->SetVy(0);
			break;

		default:
			break;
		}
	}
	else if (impactor->Tag == Entity::EntityTypes::UpStairs)
	{
		if (this->mPlayerData->player->CurrentMoveStairs == Entity::EntityCurrentMoveStairs::CurrentNone)
		{
			this->mPlayerData->player->CurrentMoveStairs = Entity::EntityCurrentMoveStairs::CurrentUpStairs;
		}
		switch (side)
		{
		case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->SetVy(0);
			break;

		default:
			break;
		}
	}
	else if (impactor->Tag == Entity::EntityTypes::Bin)
	{
		switch (side)
		{
		case Entity::Bottom:
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			break;

		default:
			break;
		}
	}
	else
	{
		switch (side)
		{
		case Entity::Left: case Entity::TopLeft:
			//va cham phia ben trai player
			if (this->mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
			{
				//day Player ra phia ben phai de cho player khong bi xuyen qua object
				this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
				this->mPlayerData->player->SetState(new PlayerPushingState(this->mPlayerData));
			}
			break;

		case Entity::Right: case Entity::TopRight:
			//va cham phia ben phai player
			if (this->mPlayerData->player->getMoveDirection() == Player::MoveToRight)
			{
				this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
				this->mPlayerData->player->SetState(new PlayerPushingState(this->mPlayerData));
			}
			break;

		case Entity::Top:
			break;

		case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->SetVy(0);
			break;
		}
	}
}

PlayerState::StateName PlayerRunningState::GetState()
{
	return PlayerState::Running;
}
