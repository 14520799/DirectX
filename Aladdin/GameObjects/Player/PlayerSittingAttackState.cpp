#include "PlayerSittingAttackState.h"
#include "PlayerDeathState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameObjects/MapObjects/Weapons/AppleWeapon.h"

PlayerSittingAttackState::PlayerSittingAttackState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
}

PlayerSittingAttackState::~PlayerSittingAttackState()
{

}

void PlayerSittingAttackState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
	}
}

void PlayerSittingAttackState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if ((impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Pot ||
		impactor->Tag == Entity::EntityTypes::Fire) &&
		!this->mPlayerData->player->allowImunity)
	{
		this->mPlayerData->player->bloodOfEntity--;
	}
	else if (impactor->Tag == Entity::EntityTypes::Oroku && impactor->Id != Entity::EntityId::Camel)
	{
		if (!impactor->allowImunity)
			this->mPlayerData->player->collisionWithOroku = true;
	}
	else if (impactor->Tag == Entity::EntityTypes::Sword  || impactor->Id == Entity::EntityId::Camel ||
		impactor->Tag == Entity::EntityTypes::Pot || impactor->Tag == Entity::EntityTypes::FallControl ||
		impactor->Tag == Entity::EntityTypes::OrokuControl || impactor->Tag == Entity::EntityTypes::FireControl)
	{

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
			this->mPlayerData->player->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
			break;

		case Entity::Bottom:
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->SetVy(0);
			break;
		}
	}
}

PlayerState::StateName PlayerSittingAttackState::GetState()
{
	return PlayerState::SittingAttack;
}