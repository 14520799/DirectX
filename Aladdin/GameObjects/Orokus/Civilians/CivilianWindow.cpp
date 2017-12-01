#include "CivilianWindow.h"
#include "CivilianWindowDefaultState.h"
#include "CivilianWindowThrowPotState.h"
#include "../../MapObjects/PotWeapon.h"
#include "../../MapObjects/PotWeaponEffect.h"
#include "../../Player/Player.h"
#include "../../../GameDefines/GameDefine.h"

CivilianWindow::CivilianWindow(D3DXVECTOR3 position)
{
	mAnimationDefault = new Animation("Resources/Orokus/Civilians/CivilianWindowDefault.png", 1, 1, 1, 0.0f);
	this->SetPosition(position);

	this->mOrokuData = new OrokuData();
	this->mOrokuData->civilianWindow = this;
	this->vx = 0;
	this->vy = 0;


	if (!mPlayer)
	{
		settedPlayer = false;
	}

	this->weapon = new PotWeapon(D3DXVECTOR3(this->GetPosition().x + 20, this->GetPosition().y + 20, 0));
	this->weapon->Tag = Entity::EntityTypes::Pot;

	this->SetState(new CivilianWindowDefaultState(this->mOrokuData));

}

CivilianWindow::~CivilianWindow()
{

}

void CivilianWindow::Update(float dt)
{
	mCurrentAnimation->Update(dt);

	if (this->mOrokuData->state)
	{
		this->mOrokuData->state->Update(dt);
		if (allowDrawWeapon)
		{
			weapon->Update(dt);
			weapon->Entity::Update(dt);
		}
	}

	this->Entity::Update(dt);

	//neu pot va cham voi player thi se bien mat
	if (weapon->collisionWithPlayer || weapon->weaponCollided)
	{
		allowDrawWeapon = false;
		weapon->collisionWithPlayer = false;
		weapon->weaponCollided = false;
		weaponEffect = new PotWeaponEffect(weapon->GetPosition());
		this->mOrokuData->civilianWindow->weapon->SetPosition(D3DXVECTOR3(this->GetPosition().x + 20, this->GetPosition().y + 20, 0));
	}

	if (weaponEffect != nullptr)
	{
		weaponEffect->Update(dt);
		weaponEffect->timeDelayWeaponEffect += dt;
		if (weaponEffect->timeDelayWeaponEffect > 0.2f)
		{
			delete weaponEffect;
			weaponEffect = nullptr;
		}
	}

	if (!allowDefault)
	{
		if ((this->GetPosition().x - this->mPlayer->GetPosition().x > -Define::DANGEROUS_AREA_POT_MAX_X &&
			this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_POT_MAX_X))
		{
			if (mCurrentState == OrokuState::CivilianWindowThrowPot)
				return;
			this->SetState(new CivilianWindowThrowPotState(this->mOrokuData));
		}
		else 
		{
			if (mCurrentState == OrokuState::CivilianWindowDefault)
				return;
			this->SetState(new CivilianWindowThrowPotState(this->mOrokuData));
		}
	}
}

void CivilianWindow::SetState(OrokuState *newState)
{
	delete this->mOrokuData->state;

	this->mOrokuData->state = newState;

	mPreCurrentAnimation = mCurrentAnimation;
	this->changeAnimation(newState->GetState());

	if (mPreCurrentAnimation != nullptr)
		this->posY += (mPreCurrentAnimation->GetHeight() - mCurrentAnimation->GetHeight()) / 2.0f;

	mCurrentState = newState->GetState();
}

void CivilianWindow::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}

void CivilianWindow::SetPlayer(Player *player)
{
	this->mPlayer = player;
}

RECT CivilianWindow::GetBound()
{
	RECT rect;

	rect.left = this->posX - mCurrentAnimation->GetWidth() / 2;
	rect.right = this->posX + mCurrentAnimation->GetWidth() / 2;
	rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
	rect.bottom = this->posY + mCurrentAnimation->GetHeight() / 2;

	return rect;
}

void CivilianWindow::Draw(D3DXVECTOR2 trans)
{
	mCurrentAnimation->FlipVertical(this->mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), trans);
	if (allowDrawWeapon)
	{
		weapon->Draw(D3DXVECTOR3(weapon->posX, weapon->posY, 0), trans);
	}
	if (weaponEffect != nullptr)
	{
		weaponEffect->Draw(D3DXVECTOR3(weaponEffect->posX, weaponEffect->posY, 0), trans);
	}
}

void CivilianWindow::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	this->mOrokuData->state->OnCollision(impactor, side, data);
}

void CivilianWindow::changeAnimation(OrokuState::StateName state)
{
	switch (state)
	{
	case OrokuState::CivilianWindowDefault:
		mCurrentAnimation = mAnimationDefault;
		break;

	case OrokuState::CivilianWindowThrowPot:
		delete mAnimationThrowPot;
		mAnimationThrowPot = new Animation("Resources/Orokus/Civilians/CivilianWindowThrowPot.png", 10, 1, 10, 0.03f);
		mCurrentAnimation = mAnimationThrowPot;
		break;

	default:
		break;
	}

	this->width = mCurrentAnimation->GetWidth();
	this->height = mCurrentAnimation->GetHeight();
}

OrokuState::StateName CivilianWindow::getState()
{
	return mCurrentState;
}