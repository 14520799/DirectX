#include "CivilianWindowDefaultState.h"
#include "../../../GameDefines/GameDefine.h"

CivilianWindowDefaultState::CivilianWindowDefaultState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	timeDelay = 0;
	this->mOrokuData->civilianWindow->weapon->SetPosition(D3DXVECTOR3(
		this->mOrokuData->civilianWindow->GetPosition().x,
		this->mOrokuData->civilianWindow->GetPosition().y + 20,
		0));
	//sau khi thuc hien xong state throwpot thi pot se xuat hien va hien tai state default
	this->mOrokuData->civilianWindow->allowDrawWeapon = true;
	this->mOrokuData->civilianWindow->allowDefault = true;
}

CivilianWindowDefaultState::~CivilianWindowDefaultState()
{
}

void CivilianWindowDefaultState::Update(float dt)
{
	timeDelay += dt;

	if (timeDelay > 0.8f)
	{
		this->mOrokuData->civilianWindow->allowDefault = false;
	}

	if (this->mOrokuData->civilianWindow->allowDrawWeapon)
	{
		this->mOrokuData->civilianWindow->weapon->AddVx(Define::ITEM_SPEED_X / 5);
		this->mOrokuData->civilianWindow->weapon->AddVy(Define::ITEM_SPEED_Y * 2);
	}
}

OrokuState::StateName CivilianWindowDefaultState::GetState()
{
	return OrokuState::CivilianWindowDefault;
}