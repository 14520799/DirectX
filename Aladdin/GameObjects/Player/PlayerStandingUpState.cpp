#include "PlayerStandingUpState.h"
#include "PlayerStandingUpStopState.h"
#include "PlayerDeathState.h"

PlayerStandingUpState::PlayerStandingUpState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}


PlayerStandingUpState::~PlayerStandingUpState()
{
}

void PlayerStandingUpState::Update(float dt)
{
	timeDelayState += dt;
	if (timeDelayState > 0.3f)
		this->mPlayerData->player->SetState(new PlayerStandingUpStopState(this->mPlayerData));
}

void PlayerStandingUpState::HandleKeyboard(std::map<int, bool> keys)
{

}

void PlayerStandingUpState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
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
	else if (impactor->Tag == Entity::EntityTypes::Sword || impactor->Tag == Entity::EntityTypes::Oroku ||
		impactor->Tag == Entity::EntityTypes::Fire || impactor->Tag == Entity::EntityTypes::FallControl ||
		impactor->Tag == Entity::EntityTypes::OrokuControl || impactor->Tag == Entity::EntityTypes::FireControl ||
		impactor->Tag == Entity::EntityTypes::Spring)
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

		case Entity::Top: case Entity::TopLeft: case Entity::TopRight:
			this->mPlayerData->player->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
			break;

		case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->SetVy(0);
			break;
		}
	}
}

PlayerState::StateName PlayerStandingUpState::GetState()
{
	return PlayerState::StandingUp;
}