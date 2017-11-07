#include "FatGuardAttackState.h"
#include "FatGuardRunningState.h"
#include "FatGuardDefaultState.h"
#include "../../../GameDefines/GameDefine.h"

FatGuardAttackState::FatGuardAttackState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	//set lai huong chay cua fatguard thanh false
	this->mOrokuData->fatGuard->mSettedLeftRunning = false;
	this->mOrokuData->fatGuard->mSettedRightRunning = false;
	//set lai huong bay cua cay kiem thanh false
	this->mOrokuData->fatGuard->sword->mSettedLeftReserve = false;
	this->mOrokuData->fatGuard->sword->mSettedRightReserve = false;
	this->mOrokuData->fatGuard->SetVx(0);
	this->mOrokuData->fatGuard->SetVy(0);
	this->mOrokuData->fatGuard->sword->SetPosition(this->mOrokuData->fatGuard->GetPosition());
	this->mOrokuData->fatGuard->sword->SetVx(0);
	this->mOrokuData->fatGuard->sword->SetVy(0);
}

FatGuardAttackState::~FatGuardAttackState()
{
}

void FatGuardAttackState::Update(float dt)
{
	//cho phep oroku thuc hien xong state attack roi moi co the sang state khac
	timeDelayState += dt;

	if (timeDelayState > 0.5f)
	{
		this->mOrokuData->fatGuard->SetState(new FatGuardDefaultState(this->mOrokuData));
		return;
	}

	if (this->mOrokuData->fatGuard->allowDrawSword)
	{
		//xet huong hien tai cua fatguard
		if (this->mOrokuData->fatGuard->mCurrentReverse)
		{
			if (this->mOrokuData->fatGuard->sword->mSettedLeftReserve)
			{
				this->mOrokuData->fatGuard->sword->AddVx(-Define::SWORDFATGUARD_SPEED);
				return;
			}
			this->mOrokuData->fatGuard->sword->mSettedRightReserve = true;
			this->mOrokuData->fatGuard->sword->AddVx(Define::SWORDFATGUARD_SPEED);
		}
		else if (!this->mOrokuData->fatGuard->mCurrentReverse)
		{
			if (this->mOrokuData->fatGuard->sword->mSettedRightReserve)
			{
				this->mOrokuData->fatGuard->sword->AddVx(Define::SWORDFATGUARD_SPEED);
				return;
			}
			this->mOrokuData->fatGuard->sword->mSettedLeftReserve = true;
			this->mOrokuData->fatGuard->sword->AddVx(-Define::SWORDFATGUARD_SPEED);
		}
	}
}

void FatGuardAttackState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

OrokuState::StateName FatGuardAttackState::GetState()
{
	return OrokuState::FatGuardAttack;
}
