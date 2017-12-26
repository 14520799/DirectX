#include "PlayerClimbingAttackState.h"
#include "PlayerFallingState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"
#include "../../GameObjects/MapObjects/Weapons/AppleWeapon.h"

PlayerClimbingAttackState::PlayerClimbingAttackState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}

PlayerClimbingAttackState::~PlayerClimbingAttackState()
{

}

void PlayerClimbingAttackState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(false);
	}
	else if (keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(true);
	}
	else
	{
		this->mPlayerData->player->SetVx(0);
	}
}

void PlayerClimbingAttackState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::Oroku && impactor->Id != Entity::EntityId::Camel)
	{
		if (!impactor->allowImunity)
			this->mPlayerData->player->collisionWithOroku = true;
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
	else if (impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Pot ||
		impactor->Tag == Entity::EntityTypes::VerticalRopeControl)
	{

	}
}

PlayerState::StateName PlayerClimbingAttackState::GetState()
{
	return PlayerState::ClimbingAttack;
}