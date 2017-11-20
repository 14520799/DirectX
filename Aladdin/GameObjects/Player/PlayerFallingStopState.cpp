#include "PlayerFallingStopState.h"
#include "PlayerRunningState.h"
#include "PlayerDeathState.h"
#include "PlayerDefaultState.h"
#include "PlayerFallingState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"

PlayerFallingStopState::PlayerFallingStopState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	timeDelayState = 0;
}


PlayerFallingStopState::~PlayerFallingStopState()
{
}

void PlayerFallingStopState::Update(float dt)
{
	timeDelayState += dt;
	if (timeDelayState > 0.5f)
		this->mPlayerData->player->SetState(new PlayerDefaultState(this->mPlayerData));
}

void PlayerFallingStopState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		return;
	}
}

void PlayerFallingStopState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
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
	else if (impactor->Tag == Entity::EntityTypes::UpStairsControl || impactor->Tag == Entity::EntityTypes::DownStairsControl || impactor->Tag == Entity::EntityTypes::GroundControl)
	{

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

PlayerState::StateName PlayerFallingStopState::GetState()
{
	return PlayerState::FallingStop;
}