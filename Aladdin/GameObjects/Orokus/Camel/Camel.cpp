#include "Camel.h"
#include "CamelDefaultState.h"
#include "CamelLyingState.h"
#include "../../Player/Player.h"
#include "../../../GameDefines/GameDefine.h"

Camel::Camel(D3DXVECTOR3 position)
{
	mAnimationDefault = new Animation("Resources/Orokus/Camel/CamelDefault.png", 1, 1, 1, 0.0f);

	this->SetPosition(position);

	this->mOrokuData = new OrokuData();
	this->mOrokuData->camel = this;
	this->vx = 0;
	this->vy = 0;

	this->SetState(new CamelLyingState(this->mOrokuData));

	if (!mPlayer)
	{
		settedPlayer = false;
	}
}

Camel::~Camel()
{

}

void Camel::Update(float dt)
{
	mCurrentAnimation->Update(dt);

	if (this->mOrokuData->state)
	{
		this->mOrokuData->state->Update(dt);
	}

	this->Entity::Update(dt);
}

void Camel::SetState(OrokuState *newState)
{
	delete this->mOrokuData->state;

	this->mOrokuData->state = newState;

	mPreCurrentAnimation = mCurrentAnimation;
	this->changeAnimation(newState->GetState());

	if (mPreCurrentAnimation != nullptr)
		this->posY += (mPreCurrentAnimation->GetHeight() - mCurrentAnimation->GetHeight()) / 2.0f;

	mCurrentState = newState->GetState();
}

void Camel::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}

void Camel::SetPlayer(Player *player)
{
	this->mPlayer = player;
}

RECT Camel::GetBound()
{
	RECT rect;

	if (mCurrentState == OrokuState::CamelDefault)
	{
		rect.left = this->posX - 100;
		rect.right = rect.left + 50;
		rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
		rect.bottom = this->posY + mCurrentAnimation->GetHeight() / 2;
	}
	else if (mCurrentState == OrokuState::CamelLying)
	{
		rect.left = this->posX - mCurrentAnimation->GetWidth() / 2;
		rect.right = this->posX + mCurrentAnimation->GetWidth() / 2;
		rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
		rect.bottom = this->posY + mCurrentAnimation->GetHeight() / 2;
	}
	return rect;
}

void Camel::Draw(D3DXVECTOR2 trans)
{
	mCurrentAnimation->FlipVertical(this->mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), trans);
}

void Camel::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	this->mOrokuData->state->OnCollision(impactor, side, data);
}

void Camel::changeAnimation(OrokuState::StateName state)
{
	switch (state)
	{
	case OrokuState::CamelDefault:
		mCurrentAnimation = mAnimationDefault;
		break;

	case OrokuState::CamelLying:
		delete mAnimationLying;
		mAnimationLying = new Animation("Resources/Orokus/Camel/CamelLying.png", 7, 1, 7, 0.05f);
		mCurrentAnimation = mAnimationLying;
		break;

	default:
		break;
	}

	this->width = mCurrentAnimation->GetWidth();
	this->height = mCurrentAnimation->GetHeight();
}

OrokuState::StateName Camel::getState()
{
	return mCurrentState;
}