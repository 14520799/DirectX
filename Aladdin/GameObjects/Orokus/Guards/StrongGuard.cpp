#include "StrongGuard.h"
#include "StrongGuardStandingState.h"

StrongGuard::StrongGuard(D3DXVECTOR3 position)
{
	mAnimationStanding = new Animation("Resources/Orokus/Guards/StrongGuardStanding_1.png", 6, 1, 6, 0.1f);

	this->SetPosition(position);

	this->mOrokuData = new OrokuData();
	this->mOrokuData->strongGuard = this;
	this->vx = 0;
	this->vy = 0;

	this->SetState(new StrongGuardStandingState(this->mOrokuData));
}

StrongGuard::~StrongGuard()
{

}

void StrongGuard::Update(float dt)
{
	mCurrentAnimation->Update(dt);

	if (this->mOrokuData->state)
	{
		this->mOrokuData->state->Update(dt);
	}

	this->Entity::Update(dt);
}

void StrongGuard::SetState(OrokuState *newState)
{
	delete this->mOrokuData->state;

	this->mOrokuData->state = newState;

	this->changeAnimation(newState->GetState());

	mCurrentState = newState->GetState();
}

void StrongGuard::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}

RECT StrongGuard::GetBound()
{
	RECT rect;
	rect.left = this->posX - mCurrentAnimation->GetWidth() / 2;
	rect.right = rect.left + mCurrentAnimation->GetWidth();
	rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
	rect.bottom = rect.top + mCurrentAnimation->GetHeight();

	return rect;
}

void StrongGuard::Draw(D3DXVECTOR2 trans)
{
	mCurrentAnimation->FlipVertical(this->mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), trans);
}

void StrongGuard::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	this->mOrokuData->state->OnCollision(impactor, side, data);
}

void StrongGuard::changeAnimation(OrokuState::StateName state)
{
	switch (state)
	{
	case OrokuState::StrongGuardStanding:
		mCurrentAnimation = mAnimationStanding;
		break;

	case OrokuState::StrongGuardRunning:
		mCurrentAnimation = mAnimationRunning;
		break;

	case OrokuState::StrongGuardAttack:
		mCurrentAnimation = mAnimationAttack;
		break;

	default:
		break;
	}

	this->width = mCurrentAnimation->GetWidth();
	this->height = mCurrentAnimation->GetHeight();
}

OrokuState::StateName StrongGuard::getState()
{
	return mCurrentState;
}