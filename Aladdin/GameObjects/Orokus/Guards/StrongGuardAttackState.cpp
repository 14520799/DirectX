#include "StrongGuardAttackState.h"
#include "StrongGuardRunningState.h"
#include "StrongGuardRunningFireState.h"
#include "../../../GameDefines/GameDefine.h"

StrongGuardAttackState::StrongGuardAttackState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	this->mOrokuData->strongGuard->settingAttack = true;
	this->mOrokuData->strongGuard->mSettingLeftRun = false;
	this->mOrokuData->strongGuard->mSettingRightRun = false;
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
		if (this->mOrokuData->strongGuard->GetPosition().x - this->mOrokuData->strongGuard->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN_X &&
			this->mOrokuData->strongGuard->GetPosition().x - this->mOrokuData->strongGuard->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX_X)
		{
			this->mOrokuData->strongGuard->SetReverse(false);
			this->mOrokuData->strongGuard->mSettingLeftRun = true;
			this->mOrokuData->strongGuard->settingAttack = false;
			if(this-mOrokuData->strongGuard->runningFire)
				this->mOrokuData->strongGuard->SetState(new StrongGuardRunningFireState(this->mOrokuData));
			else
				this->mOrokuData->strongGuard->SetState(new StrongGuardRunningState(this->mOrokuData));
		}
		else if ((this->mOrokuData->strongGuard->GetPosition().x - this->mOrokuData->strongGuard->mPlayer->GetPosition().x) > -Define::DANGEROUS_AREA_MAX_X &&
			(this->mOrokuData->strongGuard->GetPosition().x - this->mOrokuData->strongGuard->mPlayer->GetPosition().x) < Define::DANGEROUS_AREA_MIN_X)
		{
			this->mOrokuData->strongGuard->SetReverse(true);
			this->mOrokuData->strongGuard->mSettingRightRun = true;
			this->mOrokuData->strongGuard->settingAttack = false;
			if (this - mOrokuData->strongGuard->runningFire)
				this->mOrokuData->strongGuard->SetState(new StrongGuardRunningFireState(this->mOrokuData));
			else
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