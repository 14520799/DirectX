#include "JafarSnakeAttackState.h"
#include "../../MapObjects/Weapons/FireWeapon.h"
#include "../../../GameDefines/GameDefine.h"

JafarSnakeAttackState::JafarSnakeAttackState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	timeCreateWeapon = 1.0f;
}

JafarSnakeAttackState::~JafarSnakeAttackState()
{

}

void JafarSnakeAttackState::Update(float dt)
{
	if (this->mOrokuData->jafar->GetPosition().y - this->mOrokuData->jafar->mPlayer->GetPosition().y > -Define::DANGEROUS_AREA_MAX_Y * 2 &&
		this->mOrokuData->jafar->GetPosition().y - this->mOrokuData->jafar->mPlayer->GetPosition().y < Define::DANGEROUS_AREA_MAX_Y * 2)
	{
		//boss cach player PosX tu 0 --> 600
		if (this->mOrokuData->jafar->GetPosition().x - this->mOrokuData->jafar->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN_X &&
			this->mOrokuData->jafar->GetPosition().x - this->mOrokuData->jafar->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX_X * 3)
		{
			timeCreateWeapon += dt;
			if (timeCreateWeapon > 1.0f)
			{
				this->mOrokuData->jafar->weapon = new FireWeapon(this->mOrokuData->jafar->GetPosition() + D3DXVECTOR3(-40, 30, 0));
				this->mOrokuData->jafar->mListWeapon.push_back(this->mOrokuData->jafar->weapon);
				timeCreateWeapon = 0;
			}
			this->mOrokuData->jafar->mCurrentReverse = true;
		}
		//boss cach player PosX tu -600 --> 0
		else if (this->mOrokuData->jafar->GetPosition().x - this->mOrokuData->jafar->mPlayer->GetPosition().x > -Define::DANGEROUS_AREA_MAX_X * 3 &&
			this->mOrokuData->jafar->GetPosition().x - this->mOrokuData->jafar->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MIN_X)
		{
			timeCreateWeapon += dt;
			if (timeCreateWeapon > 2.0f)
			{
				this->mOrokuData->jafar->weapon = new FireWeapon(this->mOrokuData->jafar->GetPosition() + D3DXVECTOR3(40, 30, 0));
				this->mOrokuData->jafar->mListWeapon.push_back(this->mOrokuData->jafar->weapon);
				timeCreateWeapon = 0;
			}
			this->mOrokuData->jafar->mCurrentReverse = false;
		}
	}
}

void JafarSnakeAttackState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::AppleWeapon)
	{

	}
	else if (impactor->Tag == Entity::EntityTypes::Aladdin && !impactor->allowImunity)
		this->mOrokuData->jafar->collisionWithPlayer = true;
}

OrokuState::StateName JafarSnakeAttackState::GetState()
{
	return OrokuState::JafarSnakeAttack;
}