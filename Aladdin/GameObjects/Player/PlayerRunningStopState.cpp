#include "PlayerRunningStopState.h"
#include "PlayerRunningState.h"
#include "PlayerDeathState.h"
#include "PlayerDefaultState.h"
#include "PlayerFallingState.h"
#include "../MapObjects/AppleWeapon.h"
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
		this->mPlayerData->player->AddVx(Define::PLAYER_RUN_SPEED_X);
		if (this->mPlayerData->player->GetVx() >= 0)
			this->mPlayerData->player->SetState(new PlayerDefaultState(this->mPlayerData));
	}
	else if (this->mPlayerData->player->getMoveDirection() == Player::MoveToRight)
	{
		this->mPlayerData->player->AddVx(-Define::PLAYER_RUN_SPEED_X);
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
	if ((impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Pot ||
		impactor->Tag == Entity::EntityTypes::Fire) &&
		this->mPlayerData->player->allowDeath)
	{
		this->mPlayerData->player->SetState(new PlayerDeathState(this->mPlayerData));
	}
	else if (impactor->Tag == Entity::EntityTypes::AppleItem)
	{
		this->mPlayerData->player->collisionAppleItem = true;
		this->mPlayerData->player->apple = new AppleWeapon();
		this->mPlayerData->player->mListApplePlayer.push_back(this->mPlayerData->player->apple);
	}
	else if (impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Guard ||
		impactor->Tag == Entity::EntityTypes::Camel || impactor->Tag == Entity::EntityTypes::Pot || 
		impactor->Tag == Entity::EntityTypes::Fire)
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

PlayerState::StateName PlayerRunningStopState::GetState()
{
	return PlayerState::RunningStop;
}