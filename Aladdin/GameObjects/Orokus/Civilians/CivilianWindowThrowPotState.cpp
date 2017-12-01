#include "CivilianWindowThrowPotState.h"
#include "CivilianWindowDefaultState.h"
#include "../Oroku.h"

CivilianWindowThrowPotState::CivilianWindowThrowPotState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	//doi thuc hien xong state throwpot thi pot moi xuat hien
	this->mOrokuData->civilianWindow->allowDrawWeapon = false;
	this->mOrokuData->civilianWindow->weapon->SetVx(0);
	this->mOrokuData->civilianWindow->weapon->SetVy(0);
}

CivilianWindowThrowPotState::~CivilianWindowThrowPotState()
{
}

void CivilianWindowThrowPotState::Update(float dt)
{
	//cho phep oroku thuc hien xong state attack roi moi co the sang state khac
	this->mOrokuData->civilianWindow->timeDelayDefaultState += dt;

	if (this->mOrokuData->civilianWindow->timeDelayDefaultState > 0.5f)
	{
		this->mOrokuData->civilianWindow->timeDelayDefaultState = 0;
		this->mOrokuData->civilianWindow->SetState(new CivilianWindowDefaultState(this->mOrokuData));
		return;
	}
}

void CivilianWindowThrowPotState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

OrokuState::StateName CivilianWindowThrowPotState::GetState()
{
	return OrokuState::CivilianWindowThrowPot;
}
