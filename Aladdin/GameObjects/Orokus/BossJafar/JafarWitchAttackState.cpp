#include "JafarWitchAttackState.h"
#include "JafarDefaultState.h"
#include "JafarSnakeAttackState.h"
#include "../../MapObjects/Weapons/StarWeapon.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/Sound.h"

JafarWitchAttackState::JafarWitchAttackState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
	timeCreateWeapon = 0;
}

JafarWitchAttackState::~JafarWitchAttackState()
{

}

void JafarWitchAttackState::Update(float dt)
{
	if (this->mOrokuData->jafar->GetPosition().y - this->mOrokuData->jafar->mPlayer->GetPosition().y > -Define::DANGEROUS_AREA_MAX_Y * 2 &&
		this->mOrokuData->jafar->GetPosition().y - this->mOrokuData->jafar->mPlayer->GetPosition().y < Define::DANGEROUS_AREA_MAX_Y * 2)
	{
		//boss cach player PosX tu 0 --> 600
		if (this->mOrokuData->jafar->GetPosition().x - this->mOrokuData->jafar->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN_X &&
			this->mOrokuData->jafar->GetPosition().x - this->mOrokuData->jafar->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX_X * 2)
		{
			timeCreateWeapon += dt;
			if (timeCreateWeapon > 0.1f)
			{
				Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/JafarTractor.wav", "JafarTractor");
				Sound::getInstance()->play("JafarTractor", false, 1);
				this->mOrokuData->jafar->weapon = new StarWeapon(this->mOrokuData->jafar->GetPosition() + D3DXVECTOR3(-70, -40, 0));
				this->mOrokuData->jafar->mListWeapon.push_back(this->mOrokuData->jafar->weapon);
				timeCreateWeapon = 0;
			}
			this->mOrokuData->jafar->mCurrentReverse = true;
		}
		//boss cach player PosX tu -600 --> 0
		else if (this->mOrokuData->jafar->GetPosition().x - this->mOrokuData->jafar->mPlayer->GetPosition().x > -Define::DANGEROUS_AREA_MAX_X * 2 &&
			this->mOrokuData->jafar->GetPosition().x - this->mOrokuData->jafar->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MIN_X)
		{
			timeCreateWeapon += dt;
			if (timeCreateWeapon > 0.1f)
			{
				Sound::getInstance()->loadSound("Resources/Sounds/Aladdin/JafarTractor.wav", "JafarTractor");
				Sound::getInstance()->play("JafarTractor", false, 1);
				this->mOrokuData->jafar->weapon = new StarWeapon(this->mOrokuData->jafar->GetPosition() + D3DXVECTOR3(70, -40, 0));
				this->mOrokuData->jafar->mListWeapon.push_back(this->mOrokuData->jafar->weapon);
				timeCreateWeapon = 0;
			}
			this->mOrokuData->jafar->mCurrentReverse = false;
		}
		else
		{
			this->mOrokuData->jafar->SetState(new JafarDefaultState(this->mOrokuData));
		}
	}
	else
	{
		this->mOrokuData->jafar->SetState(new JafarDefaultState(this->mOrokuData));
	}
}

void JafarWitchAttackState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::AppleWeapon)
	{

	}
	else if (impactor->Tag == Entity::EntityTypes::Aladdin && !impactor->allowImunity)
		this->mOrokuData->jafar->collisionWithPlayer = true;
}

OrokuState::StateName JafarWitchAttackState::GetState()
{
	return OrokuState::JafarWitchAttack;
}