#include "PlayerPushingState.h"
#include "PlayerRunningState.h"
#include "PlayerDefaultState.h"
#include "PlayerDeathState.h"
#include "../../GameComponents/Sound.h"

PlayerPushingState::PlayerPushingState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/AladdinPush.wav", "AladdinPush");
	Sound::getInstance()->play("AladdinPush", false, 1);
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}


PlayerPushingState::~PlayerPushingState()
{
}

void PlayerPushingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT])
	{
		if (!this->mPlayerData->player->GetReverse())
			this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		else
			return;
	}
	else if (keys[VK_RIGHT])
	{
		if (this->mPlayerData->player->GetReverse())
			this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		else
			return;
	}
	else
	{
		this->mPlayerData->player->SetState(new PlayerDefaultState(this->mPlayerData));
	}
}

void PlayerPushingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if ((impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Pot ||
		impactor->Tag == Entity::EntityTypes::Fire) &&
		!this->mPlayerData->player->allowImunity)
	{
		this->mPlayerData->player->bloodOfEntity--;
	}
	else if (impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Oroku ||
		impactor->Tag == Entity::EntityTypes::Pot)
	{

	}
	else
	{
		switch (side)
		{
		case Entity::Left:
			//day Player ra phia ben phai de cho player khong bi xuyen qua object
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

PlayerState::StateName PlayerPushingState::GetState()
{
	return PlayerState::Pushing;
}