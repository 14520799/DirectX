#include "PlayerRunningState.h"
#include "PlayerRunningStopState.h"
#include "PlayerDeathState.h"
#include "PlayerDefaultState.h"
#include "PlayerFallingState.h"
#include "PlayerPushingState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"

PlayerRunningState::PlayerRunningState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	acceletoryX = Define::PLAYER_NORMAL_SPEED_X;
	this->mPlayerData->player->SetVx(0);
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
			this->mPlayerData->player->AddVx(acceletoryX);

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
			this->mPlayerData->player->AddVx(-acceletoryX);

			if (this->mPlayerData->player->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
	}
	else
	{
		if (this->mPlayerData->player->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED * 4.5f / 5 ||
			this->mPlayerData->player->GetVx() > Define::PLAYER_MAX_RUNNING_SPEED * 4.5f / 5)
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
	if (impactor->Tag == Entity::EntityTypes::Fire && this->mPlayerData->player->allowDeath)
	{
		this->mPlayerData->player->SetState(new PlayerDeathState(this->mPlayerData));
	}
	else if (impactor->Tag == Entity::EntityTypes::Fire && !this->mPlayerData->player->allowDeath)
	{
		//giam toc do khi player chay vao bai lua
		//acceletoryX = Define::PLAYER_HURT_SPEED_X;
	}
	//bi thuong khi trung kiem
	else if (impactor->Tag == Entity::EntityTypes::Sword && this->mPlayerData->player->allowDeath)
	{
		this->mPlayerData->player->SetState(new PlayerDeathState(this->mPlayerData));
	}
	else if (impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Guard)
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
	else
	{
		switch (side)
		{
		case Entity::Left:
			//va cham phia ben trai player
			if (this->mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
			{
				//day Player ra phia ben phai de cho player khong bi xuyen qua object
				this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
				this->mPlayerData->player->SetState(new PlayerPushingState(this->mPlayerData));
			}
			break;

		case Entity::Right:
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
