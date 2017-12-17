#include "FatGuardAttackState.h"
#include "FatGuardRunningState.h"
#include "FatGuardDefaultState.h"
#include "../../../GameDefines/GameDefine.h"
#include "../Oroku.h"
#include "../../../GameComponents/Sound.h"

FatGuardAttackState::FatGuardAttackState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/HighSword.wav", "HighSword");
	Sound::getInstance()->play("HighSword", false, 1);
	//set lai huong chay tan cong cua fatguard
	this->mOrokuData->fatGuard->mSettingLeftRun = false;
	this->mOrokuData->fatGuard->mSettingRightRun = false;
	this->mOrokuData->fatGuard->SetVx(0);
	this->mOrokuData->fatGuard->SetVy(0);
	this->mOrokuData->fatGuard->weapon->SetPosition(D3DXVECTOR3(
		this->mOrokuData->fatGuard->GetPosition().x,
		this->mOrokuData->fatGuard->GetPosition().y - this->mOrokuData->fatGuard->GetHeight() / 2,
		0));
	this->mOrokuData->fatGuard->weapon->SetVx(0);
	this->mOrokuData->fatGuard->weapon->SetVy(Define::ITEM_MIN_VELOCITY);
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

	if (this->mOrokuData->fatGuard->allowDrawWeapon)
	{
		//xet huong hien tai cua fatguard
		if (this->mOrokuData->fatGuard->mCurrentReverse)
		{
			if (this->mOrokuData->fatGuard->weapon->mSettingLeftItem)
			{
				this->mOrokuData->fatGuard->weapon->AddVx(-Define::ITEM_SPEED_X);
				this->mOrokuData->fatGuard->weapon->AddVy(Define::ITEM_SPEED_Y);
				return;
			}
			this->mOrokuData->fatGuard->weapon->mSettingRightItem = true;
			this->mOrokuData->fatGuard->weapon->AddVx(Define::ITEM_SPEED_X);
			if (this->mOrokuData->fatGuard->weapon->GetVy() <= Define::ITEM_MIN_VELOCITY || this->mOrokuData->fatGuard->weapon->DirectionDown)
			{
				this->mOrokuData->fatGuard->weapon->AddVy(Define::ITEM_SPEED_Y);
				this->mOrokuData->fatGuard->weapon->DirectionDown = true;
			}
			else if (this->mOrokuData->fatGuard->weapon->GetVy() > Define::ITEM_MIN_VELOCITY)
				this->mOrokuData->fatGuard->weapon->AddVy(-Define::ITEM_SPEED_Y);
		}
		else if (!this->mOrokuData->fatGuard->mCurrentReverse)
		{
			if (this->mOrokuData->fatGuard->weapon->mSettingRightItem)
			{
				this->mOrokuData->fatGuard->weapon->AddVx(Define::ITEM_SPEED_X);
				this->mOrokuData->fatGuard->weapon->AddVy(Define::ITEM_SPEED_Y);
				return;
			}
			this->mOrokuData->fatGuard->weapon->mSettingLeftItem = true;
			this->mOrokuData->fatGuard->weapon->AddVx(-Define::ITEM_SPEED_X);
			if (this->mOrokuData->fatGuard->weapon->GetVy() <= Define::ITEM_MIN_VELOCITY || this->mOrokuData->fatGuard->weapon->DirectionDown)
			{
				this->mOrokuData->fatGuard->weapon->AddVy(Define::ITEM_SPEED_Y);
				this->mOrokuData->fatGuard->weapon->DirectionDown = true;
			}
			else if (this->mOrokuData->fatGuard->weapon->GetVy() > Define::ITEM_MIN_VELOCITY)
				this->mOrokuData->fatGuard->weapon->AddVy(-Define::ITEM_SPEED_Y);
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
