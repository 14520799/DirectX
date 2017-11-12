#include "PlayerRunningState.h"
#include "PlayerDeathState.h"
#include "PlayerDefaultState.h"
#include "PlayerFallingState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"

PlayerRunningState::PlayerRunningState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	acceletoryX = Define::PLAYER_NORMAL_SPEED_X;
	this->mPlayerData->player->allowMoveLeft = true;
	this->mPlayerData->player->allowMoveRight = true;
}


PlayerRunningState::~PlayerRunningState()
{
}

void PlayerRunningState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		if (mPlayerData->player->allowMoveRight)
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
	}
	else if (keys[VK_LEFT])
	{
		if (mPlayerData->player->allowMoveLeft)
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
	}
	else
	{
		this->mPlayerData->player->SetState(new PlayerDefaultState(this->mPlayerData));
		return;
	}
}

void PlayerRunningState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
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
		acceletoryX = Define::PLAYER_HURT_SPEED_X;
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
			//va cham phia ben trai player
			if (this->mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
			{
				this->mPlayerData->player->allowMoveLeft = false;

				//day Player ra phia ben phai de cho player khong bi xuyen qua object
				this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
				this->mPlayerData->player->SetState(new PlayerDefaultState(this->mPlayerData));
			}
			break;

		case Entity::Right:
			//va cham phia ben phai player
			if (this->mPlayerData->player->getMoveDirection() == Player::MoveToRight)
			{
				this->mPlayerData->player->allowMoveRight = false;
				this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
				this->mPlayerData->player->SetState(new PlayerDefaultState(this->mPlayerData));
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
