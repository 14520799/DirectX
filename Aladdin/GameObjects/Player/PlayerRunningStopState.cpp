#include "PlayerRunningStopState.h"
#include "PlayerRunningState.h"
#include "PlayerDeathState.h"
#include "PlayerDefaultState.h"
#include "PlayerFallingState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"

PlayerRunningStopState::PlayerRunningStopState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
}


PlayerRunningStopState::~PlayerRunningStopState()
{
}

void PlayerRunningStopState::Update(float dt)
{
	if (this->mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
	{
		this->mPlayerData->player->AddVx(Define::PLAYER_NORMAL_SPEED_X);
		if (this->mPlayerData->player->GetVx() >= 0)
			this->mPlayerData->player->SetState(new PlayerDefaultState(this->mPlayerData));
	}
	else if (this->mPlayerData->player->getMoveDirection() == Player::MoveToRight)
	{
		this->mPlayerData->player->AddVx(-Define::PLAYER_NORMAL_SPEED_X);
		if (this->mPlayerData->player->GetVx() <= 0)
			this->mPlayerData->player->SetState(new PlayerDefaultState(this->mPlayerData));
	}
}

void PlayerRunningStopState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		return;
	}
}

void PlayerRunningStopState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
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
	else if (impactor->Tag == Entity::EntityTypes::CenterStairs)
	{
		//cho phep di xuong thi se remove bac thang o tren
		if (!this->mPlayerData->player->allowUp_DownStairs)
		{
			this->mPlayerData->player->mMap->RemoveUpStairs();
			this->mPlayerData->player->mSettingUp_DownStairs = false;
		}
		//cho phep di len thi se tao lai bac thang o tren
		else if (this->mPlayerData->player->allowUp_DownStairs)
		{
			this->mPlayerData->player->mMap->InsertUpStairs();
			this->mPlayerData->player->mSettingUp_DownStairs = true;
		}
	}
	else if (impactor->Tag == Entity::EntityTypes::UpStairs)
	{
		if (this->mPlayerData->player->mSettingUp_DownStairs)
		{
			//sau khi len bac thang thanh cong thi se cho phep chuyen huong di xuong
			this->mPlayerData->player->allowUp_DownStairs = false;
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
	}
	else if (impactor->Tag == Entity::EntityTypes::DownStairs)
	{
		if (!this->mPlayerData->player->mSettingUp_DownStairs)
		{
			//sau khi xuong bac thang thanh cong thi se cho phep chuyen huong
			this->mPlayerData->player->allowUp_DownStairs = true;
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
	}
	else
	{
		switch (side)
		{
		case Entity::Left:
			this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			break;

		case Entity::Right:
			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
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

PlayerState::StateName PlayerRunningStopState::GetState()
{
	return PlayerState::RunningStop;
}