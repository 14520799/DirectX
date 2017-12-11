#include "JafarDefaultState.h"
#include "JafarWitchAttackState.h"
#include "../../../GameDefines/GameDefine.h"

JafarDefaultState::JafarDefaultState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
}

JafarDefaultState::~JafarDefaultState()
{

}

void JafarDefaultState::Update(float dt)
{
	if (this->mOrokuData->jafar->GetPosition().y - this->mOrokuData->jafar->mPlayer->GetPosition().y > -Define::DANGEROUS_AREA_MAX_Y * 2 &&
		this->mOrokuData->jafar->GetPosition().y - this->mOrokuData->jafar->mPlayer->GetPosition().y < Define::DANGEROUS_AREA_MAX_Y * 2)
	{
		//boss cach player PosX tu -600 --> 600
		if (this->mOrokuData->jafar->GetPosition().x - this->mOrokuData->jafar->mPlayer->GetPosition().x > -Define::DANGEROUS_AREA_MAX_X * 3 &&
			this->mOrokuData->jafar->GetPosition().x - this->mOrokuData->jafar->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX_X * 3)
		{
			this->mOrokuData->jafar->SetState(new JafarWitchAttackState(this->mOrokuData));
		}
	}
}

OrokuState::StateName JafarDefaultState::GetState()
{
	return OrokuState::JafarDefault;
}