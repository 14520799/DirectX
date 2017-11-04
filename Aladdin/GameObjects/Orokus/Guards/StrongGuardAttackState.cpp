#include "StrongGuardAttackState.h"
#include "StrongGuardRunningState.h"
#include "../../../GameDefines/GameDefine.h"

StrongGuardAttackState::StrongGuardAttackState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	this->mOrokuData->strongGuard->settedAttack = true;
	this->mOrokuData->strongGuard->mSettedLeftRunning = false;
	this->mOrokuData->strongGuard->mSettedRightRunning = false;
	this->mOrokuData->strongGuard->SetVx(0);
	this->mOrokuData->strongGuard->SetVy(0);
	timeDelayState = 0;
}

StrongGuardAttackState::~StrongGuardAttackState()
{
}

void StrongGuardAttackState::Update(float dt)
{
	//cho phep oroku thuc hien xong state attack roi moi co the sang state khac
	timeDelayState += dt;

	if (timeDelayState > 0.3f)
	{
		if (this->mOrokuData->strongGuard->GetPosition().x - this->mOrokuData->strongGuard->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN &&
			this->mOrokuData->strongGuard->GetPosition().x - this->mOrokuData->strongGuard->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX)
		{
			this->mOrokuData->strongGuard->SetReverse(false);
			this->mOrokuData->strongGuard->mSettedLeftRunning = true;
			this->mOrokuData->strongGuard->settedAttack = false;
			this->mOrokuData->strongGuard->SetState(new StrongGuardRunningState(this->mOrokuData));
		}
		else if ((this->mOrokuData->strongGuard->GetPosition().x - this->mOrokuData->strongGuard->mPlayer->GetPosition().x) > -Define::DANGEROUS_AREA_MAX &&
			(this->mOrokuData->strongGuard->GetPosition().x - this->mOrokuData->strongGuard->mPlayer->GetPosition().x) < Define::DANGEROUS_AREA_MIN)
		{
			this->mOrokuData->strongGuard->SetReverse(true);
			this->mOrokuData->strongGuard->mSettedRightRunning = true;
			this->mOrokuData->strongGuard->settedAttack = false;
			this->mOrokuData->strongGuard->SetState(new StrongGuardRunningState(this->mOrokuData));
		}
	}
}

void StrongGuardAttackState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

OrokuState::StateName StrongGuardAttackState::GetState()
{
	return OrokuState::StrongGuardAttack;
}