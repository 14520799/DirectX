#include "FatGuard.h"
#include "FatGuardStandingState.h"

FatGuard::FatGuard(D3DXVECTOR3 position)
{
	mAnimationStanding = new Animation("Resources/Orokus/Guards/FatGuardStanding_2.png", 7, 1, 7, 0.15f);

	this->SetPosition(position);

	this->mOrokuData = new OrokuData();
	this->mOrokuData->fatGuard = this;
	this->vx = 0;
	this->vy = 0;

	this->SetState(new FatGuardStandingState(this->mOrokuData));
}

FatGuard::~FatGuard()
{

}

void FatGuard::Update(float dt)
{
	mCurrentAnimation->Update(dt);

	if (this->mOrokuData->state)
	{
		this->mOrokuData->state->Update(dt);
	}

	this->Entity::Update(dt);
}

void FatGuard::SetState(OrokuState *newState)
{
	delete this->mOrokuData->state;

	this->mOrokuData->state = newState;

	this->changeAnimation(newState->GetState());

	mCurrentState = newState->GetState();
}

void FatGuard::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}

RECT FatGuard::GetBound()
{
	RECT rect;
	rect.left = this->posX - mCurrentAnimation->GetWidth() / 2;
	rect.right = rect.left + mCurrentAnimation->GetWidth();
	rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
	rect.bottom = rect.top + mCurrentAnimation->GetHeight();

	return rect;
}

void FatGuard::Draw(D3DXVECTOR2 trans)
{
	mCurrentAnimation->FlipVertical(this->mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), trans);
}

void FatGuard::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	this->mOrokuData->state->OnCollision(impactor, side, data);
}

void FatGuard::changeAnimation(OrokuState::StateName state)
{
	switch (state)
	{
	case OrokuState::FatGuardStanding:
		mCurrentAnimation = mAnimationStanding;
		break;

	case OrokuState::FatGuardRunning:
		mCurrentAnimation = mAnimationRunning;
		break;

	case OrokuState::FatGuardAttack:
		mCurrentAnimation = mAnimationAttack;
		break;

	default:
		break;
	}

	this->width = mCurrentAnimation->GetWidth();
	this->height = mCurrentAnimation->GetHeight();
}

OrokuState::StateName FatGuard::getState()
{
	return mCurrentState;
}


