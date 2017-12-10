#include "PlayerDeathState.h"
#include "PlayerRunningState.h"

PlayerDeathState::PlayerDeathState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
	this->mPlayerData->player->allowImunity = true;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
	allowDelayHurting = true; //dang trong khoang thoi gian thuc hien animationDeath
	timeDelayHurting = 0;
}


PlayerDeathState::~PlayerDeathState()
{
}

void PlayerDeathState::Update(float dt)
{
	if (allowDelayHurting)
	{
		timeDelayHurting += dt;

		if (timeDelayHurting > 0.5f)
		{
			allowDelayHurting = false;
			timeDelayHurting = 0;
		}
	}
}

void PlayerDeathState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_LEFT] || keys[VK_RIGHT])
    {
		//cho phep thuc hien animation khac khi animationDeath thuc hien xong
		if (!allowDelayHurting)
		{
			this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
			return;
		}
    }
}

void PlayerDeathState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if ((impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Pot ||
		impactor->Tag == Entity::EntityTypes::Fire) &&
		!this->mPlayerData->player->allowImunity)
	{
		if (impactor->Tag == Entity::EntityTypes::Fire)
			this->mPlayerData->player->effectFire = true;
		this->mPlayerData->player->bloodOfEntity--;
	}
	else if (impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Oroku ||
		impactor->Tag == Entity::EntityTypes::Pot || impactor->Tag == Entity::EntityTypes::FallControl ||
		impactor->Tag == Entity::EntityTypes::FireControl)
	{

	}
	else if (impactor->Tag == Entity::EntityTypes::Fire)
		this->mPlayerData->player->effectFire = true;
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

		case Entity::Top: case Entity::TopLeft: case Entity::TopRight:
			break;

		case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->SetVy(0);
			break;
		}
	}
}

PlayerState::StateName PlayerDeathState::GetState()
{
    return PlayerState::Death;
}