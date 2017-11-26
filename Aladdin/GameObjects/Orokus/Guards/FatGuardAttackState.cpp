#include "FatGuardAttackState.h"
#include "FatGuardRunningState.h"
#include "FatGuardDefaultState.h"
#include "../../../GameDefines/GameDefine.h"
#include "../Oroku.h"

FatGuardAttackState::FatGuardAttackState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	//set lai huong chay tan cong cua fatguard
	this->mOrokuData->fatGuard->mSettingLeftRun = false;
	this->mOrokuData->fatGuard->mSettingRightRun = false;
	this->mOrokuData->fatGuard->SetVx(0);
	this->mOrokuData->fatGuard->SetVy(0);
	this->mOrokuData->fatGuard->sword->SetPosition(D3DXVECTOR3(
		this->mOrokuData->fatGuard->GetPosition().x,
		this->mOrokuData->fatGuard->GetPosition().y - this->mOrokuData->fatGuard->GetHeight() / 2,
		0));
	this->mOrokuData->fatGuard->sword->SetVx(0);
	this->mOrokuData->fatGuard->sword->SetVy(0);
}

FatGuardAttackState::~FatGuardAttackState()
{
}

void FatGuardAttackState::Update(float dt)
{
	//cho phep oroku thuc hien xong state attack roi moi co the sang state khac
	this->mOrokuData->fatGuard->timeDelayDefaultState += dt;

	if (this->mOrokuData->fatGuard->timeDelayDefaultState > 0.8f)
	{
		this->mOrokuData->fatGuard->timeDelayDefaultState = 0;
		this->mOrokuData->fatGuard->SetState(new FatGuardDefaultState(this->mOrokuData));
		return;
	}

	if (this->mOrokuData->fatGuard->allowDrawSword)
	{
		//xet huong hien tai cua fatguard
		if (this->mOrokuData->fatGuard->mCurrentReverse)
		{
			if (this->mOrokuData->fatGuard->sword->mSettingLeftItem)
			{
				this->mOrokuData->fatGuard->sword->AddVx(-Define::ITEM_SPEED_X);
				this->mOrokuData->fatGuard->sword->AddVy(Define::ITEM_SPEED_Y);
				return;
			}
			this->mOrokuData->fatGuard->sword->mSettingRightItem = true;
			this->mOrokuData->fatGuard->sword->AddVx(Define::ITEM_SPEED_X);
			this->mOrokuData->fatGuard->sword->AddVy(Define::ITEM_SPEED_Y);
		}
		else if (!this->mOrokuData->fatGuard->mCurrentReverse)
		{
			if (this->mOrokuData->fatGuard->sword->mSettingRightItem)
			{
				this->mOrokuData->fatGuard->sword->AddVx(Define::ITEM_SPEED_X);
				this->mOrokuData->fatGuard->sword->AddVy(Define::ITEM_SPEED_Y);
				return;
			}
			this->mOrokuData->fatGuard->sword->mSettingLeftItem = true;
			this->mOrokuData->fatGuard->sword->AddVx(-Define::ITEM_SPEED_X);
			this->mOrokuData->fatGuard->sword->AddVy(Define::ITEM_SPEED_Y);
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
