#include "FatGuardAttackState.h"
#include "FatGuardRunningState.h"
#include "FatGuardDefaultState.h"
#include "../../../GameDefines/GameDefine.h"

FatGuardAttackState::FatGuardAttackState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	//them sword vao quadtree
	if (this->mOrokuData->fatGuard->addSwordQuadTree)
	{
		this->mOrokuData->fatGuard->addSwordQuadTree = false;
		this->mOrokuData->fatGuard->mQuadTree->insertEntity(this->mOrokuData->fatGuard->sword);
	}
	//set lai huong chay cua fatguard thanh false
	this->mOrokuData->fatGuard->mSettingLeftRun = false;
	this->mOrokuData->fatGuard->mSettingRightRun = false;
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
	this->mOrokuData->fatGuard->timeDelayDefaultState += dt;

	if (this->mOrokuData->fatGuard->timeDelayDefaultState > 0.5f)
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
				this->mOrokuData->fatGuard->sword->AddVx(-Define::SWORDFATGUARD_SPEED);
				return;
			}
			this->mOrokuData->fatGuard->sword->mSettingRightItem = true;
			this->mOrokuData->fatGuard->sword->AddVx(Define::SWORDFATGUARD_SPEED);
		}
		else if (!this->mOrokuData->fatGuard->mCurrentReverse)
		{
			if (this->mOrokuData->fatGuard->sword->mSettingRightItem)
			{
				this->mOrokuData->fatGuard->sword->AddVx(Define::SWORDFATGUARD_SPEED);
				return;
			}
			this->mOrokuData->fatGuard->sword->mSettingLeftItem = true;
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
