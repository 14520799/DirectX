#include "ThinGuardAttackState.h"
#include "ThinGuardRunningState.h"
#include "../../../GameDefines/GameDefine.h"

ThinGuardAttackState::ThinGuardAttackState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	this->mOrokuData->thinGuard->settingAttack = true;
	this->mOrokuData->thinGuard->mSettingLeftRun = false;
	this->mOrokuData->thinGuard->mSettingRightRun = false;
	this->mOrokuData->thinGuard->SetVx(0);
	this->mOrokuData->thinGuard->SetVy(0);
	timeDelayState = 0;
}

ThinGuardAttackState::~ThinGuardAttackState()
{
}

void ThinGuardAttackState::Update(float dt)
{
	//cho phep oroku thuc hien xong state attack roi moi co the sang state khac
	timeDelayState += dt;

	if (timeDelayState > 0.3f)
	{
		if (this->mOrokuData->thinGuard->GetPosition().x - this->mOrokuData->thinGuard->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN &&
			this->mOrokuData->thinGuard->GetPosition().x - this->mOrokuData->thinGuard->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX)
		{
			this->mOrokuData->thinGuard->SetReverse(false);
			this->mOrokuData->thinGuard->mSettingLeftRun = true;
			this->mOrokuData->thinGuard->settingAttack = false;
			this->mOrokuData->thinGuard->SetState(new ThinGuardRunningState(this->mOrokuData));
		}
		else if ((this->mOrokuData->thinGuard->GetPosition().x - this->mOrokuData->thinGuard->mPlayer->GetPosition().x) > -Define::DANGEROUS_AREA_MAX &&
			(this->mOrokuData->thinGuard->GetPosition().x - this->mOrokuData->thinGuard->mPlayer->GetPosition().x) < Define::DANGEROUS_AREA_MIN)
		{
			this->mOrokuData->thinGuard->SetReverse(true);
			this->mOrokuData->thinGuard->mSettingRightRun = true;
			this->mOrokuData->thinGuard->settingAttack = false;
			this->mOrokuData->thinGuard->SetState(new ThinGuardRunningState(this->mOrokuData));
		}
	}
	
}

void ThinGuardAttackState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

OrokuState::StateName ThinGuardAttackState::GetState()
{
	return OrokuState::ThinGuardAttack;
}
