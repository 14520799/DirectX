#include "CivilianCircusStandingState.h"
#include "../../../GameDefines/GameDefine.h"

CivilianCircusStandingState::CivilianCircusStandingState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
}

CivilianCircusStandingState::~CivilianCircusStandingState()
{
	
}

void CivilianCircusStandingState::Update(float dt)
{
	if (this->mOrokuData->civilianCircus->allowDrawWeapon)
	{
		//kiem bay qua ben phai
		if (this->mOrokuData->civilianCircus->weapon->currentReverse)
		{
			if (this->mOrokuData->civilianCircus->weapon->Mode == MapObject::WeaponMode::Nomal)
			{
				this->mOrokuData->civilianCircus->weapon->AddVx(Define::ITEM_SPEED_X);
				this->mOrokuData->civilianCircus->weapon->AddVy(Define::ITEM_SPEED_Y);
			}
			else if (this->mOrokuData->civilianCircus->weapon->Mode == MapObject::WeaponMode::Fantastic)
			{
				this->mOrokuData->civilianCircus->weapon->AddVx(Define::ITEM_SPEED_X / 5 * 2);
				this->mOrokuData->civilianCircus->weapon->AddVy(Define::ITEM_SPEED_Y * 10);
			}
		}
		//kiem bay qua ben trai
		else
		{
			if (this->mOrokuData->civilianCircus->weapon->Mode == MapObject::WeaponMode::Nomal)
			{
				this->mOrokuData->civilianCircus->weapon->AddVx(-Define::ITEM_SPEED_X);
				this->mOrokuData->civilianCircus->weapon->AddVy(Define::ITEM_SPEED_Y);
			}
			else if (this->mOrokuData->civilianCircus->weapon->Mode == MapObject::WeaponMode::Fantastic)
			{
				this->mOrokuData->civilianCircus->weapon->AddVx(-Define::ITEM_SPEED_X / 5 * 2);
				this->mOrokuData->civilianCircus->weapon->AddVy(Define::ITEM_SPEED_Y * 10);
			}
		}
	}
}

OrokuState::StateName CivilianCircusStandingState::GetState()
{
	return OrokuState::CivilianCircusStanding;
}