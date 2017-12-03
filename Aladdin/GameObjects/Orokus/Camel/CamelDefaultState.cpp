#include "CamelDefaultState.h"
#include "CamelLyingState.h"

CamelDefaultState::CamelDefaultState(OrokuData *orokuData)
{
	this->mOrokuData = orokuData;
}

CamelDefaultState::~CamelDefaultState()
{
}

void CamelDefaultState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::Aladdin)
	{
		switch (side)
		{
		case Entity::Top: case Entity::TopLeft: case Entity::TopRight: case Entity::Left: case Entity::Right:
			if(this->mOrokuData->camel->mPlayer->mCurrentState == PlayerState::RunningJump ||
				this->mOrokuData->camel->mPlayer->mCurrentState == PlayerState::StandingJump ||
				this->mOrokuData->camel->mPlayer->mCurrentState == PlayerState::Falling)
				this->mOrokuData->camel->SetState(new CamelLyingState(this->mOrokuData));
			break;

		default:
			break;
		}
	}
	if (impactor->Tag == Entity::EntityTypes::Oroku && impactor->Id != Entity::EntityId::Camel)
	{
		this->mOrokuData->camel->collisionWithOroku = false;
	}
}

OrokuState::StateName CamelDefaultState::GetState()
{
	return OrokuState::CamelDefault;
}