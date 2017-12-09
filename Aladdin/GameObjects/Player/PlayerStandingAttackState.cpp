#include "PlayerStandingAttackState.h"
#include "PlayerDefaultState.h"
#include "PlayerDeathState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"
#include "../Orokus/Oroku.h"
#include "../MapObjects/Weapons/AppleWeapon.h"

PlayerStandingAttackState::PlayerStandingAttackState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
}

PlayerStandingAttackState::~PlayerStandingAttackState()
{

}

void PlayerStandingAttackState::HandleKeyboard(std::map<int, bool> keys)
{
	
}

void PlayerStandingAttackState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);
	if (impactor->Tag == Entity::EntityTypes::Fire)
	{
		this->mPlayerData->player->effectFire = true;
		this->mPlayerData->player->mOriginPositionItem = D3DXVECTOR3(
			this->mPlayerData->player->GetPosition().x, impactor->GetPosition().y - 55, 0);
	}
	if (impactor->Tag == Entity::EntityTypes::Fire && !this->mPlayerData->player->allowImunity)
	{
		this->mPlayerData->player->bloodOfEntity--;
	}
	else if (impactor->Tag == Entity::EntityTypes::Item)
	{
		if (impactor->Id == Entity::EntityId::Revitalization_Default || impactor->Id == Entity::EntityId::Feddler_Standing)
			return;
		else if (impactor->Id == Entity::EntityId::Lamp)
			this->mPlayerData->player->effectLamp = true;
		else if (impactor->Id == Entity::EntityId::HeadGenie || impactor->Id == Entity::EntityId::Life)
			this->mPlayerData->player->effectSpecial = true;
		this->mPlayerData->player->allowEffect = true;
		this->mPlayerData->player->collisionItem = true;
		this->mPlayerData->player->mOriginPositionItem = impactor->GetPosition();
		if (impactor->Id == Entity::EntityId::AppleItem)
		{
			this->mPlayerData->player->apple = new AppleWeapon();
			this->mPlayerData->player->mListApplePlayer.push_back(this->mPlayerData->player->apple);
		}
	}
	else if (impactor->Tag == Entity::EntityTypes::Oroku && impactor->Id != Entity::EntityId::Camel)
	{
		if(!impactor->allowImunity)
			this->mPlayerData->player->collisionWithOroku = true;
	}
	else if (impactor->Tag == Entity::EntityTypes::Sword || impactor->Id == Entity::EntityId::Camel ||
		impactor->Tag == Entity::EntityTypes::Pot || impactor->Tag == Entity::EntityTypes::FallControl ||
		impactor->Tag == Entity::EntityTypes::Fire)
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

PlayerState::StateName PlayerStandingAttackState::GetState()
{
	return PlayerState::StandingAttack;
}