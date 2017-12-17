#include "PlayerDefaultState.h"
#include "PlayerStandingState.h"
#include "PlayerRunningState.h"
#include "PlayerDeathState.h"
#include "../../GameDefines/GameDefine.h"

PlayerDefaultState::PlayerDefaultState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}


PlayerDefaultState::~PlayerDefaultState()
{
}

void PlayerDefaultState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		return;
	}
}

void PlayerDefaultState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::Fire)
	{
		this->mPlayerData->player->effectFire = true;
		this->mPlayerData->player->mOriginPositionItem = D3DXVECTOR3(
			this->mPlayerData->player->GetPosition().x, impactor->GetPosition().y - 55, 0);
	}
	if ((impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Pot ||
		impactor->Tag == Entity::EntityTypes::Fire) &&
		!this->mPlayerData->player->allowImunity)
	{
		this->mPlayerData->player->bloodOfEntity--;
	}
	else if (impactor->Id == Entity::EntityId::Feddler_Standing)
		this->mPlayerData->player->collisionFeddler = true;
	else if (impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Oroku ||
		impactor->Tag == Entity::EntityTypes::Pot || impactor->Tag == Entity::EntityTypes::FallControl ||
		impactor->Tag == Entity::EntityTypes::OrokuControl || impactor->Tag == Entity::EntityTypes::FireControl ||
		impactor->Tag == Entity::EntityTypes::Spring)
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
		case Entity::Left: case Entity::BottomLeft: case Entity::BottomRight:
			this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			break;

		case Entity::Right:
			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			break;

		case Entity::Top: case Entity::TopLeft: case Entity::TopRight:
			break;

		case Entity::Bottom:
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->SetVy(0);
			break;
		}
	}
}

PlayerState::StateName PlayerDefaultState::GetState()
{
	return PlayerState::Default;
}