#include "CivilianCircus.h"
#include "CivilianCircusStandingState.h"
#include "../../MapObjects/Weapons/SwordWeapon.h"
#include "../../Player/Player.h"
#include "../../../GameDefines/GameDefine.h"

CivilianCircus::CivilianCircus(D3DXVECTOR3 position)
{
	this->mOriginPosition = position;
	this->SetPosition(mOriginPosition);
	this->Id = Entity::EntityId::CivilianCircus;

	this->mOrokuData = new OrokuData();
	this->mOrokuData->civilianCircus = this;
	this->vx = 0;
	this->vy = 0;

	if (!mPlayer)
	{
		settedPlayer = false;
	}

	this->weapon = new SwordWeapon(D3DXVECTOR3(this->GetPosition().x, this->GetPosition().y - 20, 0));
	this->weapon->Tag = Entity::EntityTypes::Sword;

	this->SetState(new CivilianCircusStandingState(this->mOrokuData));
}

CivilianCircus::~CivilianCircus()
{

}

void CivilianCircus::Update(float dt)
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
		weapon->SetPosition(weapon->originPos);
		weapon->SetVx(0);
		weapon->SetVy(0);
		allowDrawWeapon = false;
		weapon->collisionWithPlayer = false;
		weapon->weaponCollided = false;
	}

	if (allowImunity)
	{
		timeImunity += dt;

		if (timeImunity > 1.0f)
		{
			allowImunity = false;
			timeImunity = 0;
		}
	}

	//oroku cach player PosY tu -150 --> 150
	if (this->GetPosition().y - this->mPlayer->GetPosition().y > -Define::DANGEROUS_AREA_MAX_Y * 1.5f &&
		this->GetPosition().y - this->mPlayer->GetPosition().y < Define::DANGEROUS_AREA_MAX_Y * 1.5f)
	{
		//oroku cach player PosX tu 0 --> 200
		if (this->GetPosition().x - this->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN_X &&
			this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX_X)
		{
			if (weapon->GetPosition() == weapon->originPos)
			{
				this->weapon->Mode = MapObject::WeaponMode::Nomal;
				this->weapon->currentReverse = false;
				allowDrawWeapon = true;
			}
		}
		//oroku cach player PosX tu -200 --> 0
		else if (this->GetPosition().x - this->mPlayer->GetPosition().x > -Define::DANGEROUS_AREA_MAX_X &&
				this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MIN_X)
		{
			if (weapon->GetPosition() == weapon->originPos)
			{
				this->weapon->Mode = MapObject::WeaponMode::Nomal;
				this->weapon->currentReverse = true;
				allowDrawWeapon = true;
			}
		}
		//oroku cach player PosX tu 200 --> 400
		else if (this->GetPosition().x - this->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN_X &&
				this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX_X * 2)
		{
			if (weapon->GetPosition() == weapon->originPos)
			{
				this->weapon->Mode = MapObject::WeaponMode::Fantastic;
				this->weapon->currentReverse = false;
				allowDrawWeapon = true;
				this->weapon->SetVy(Define::CIVILIAN_SWORD_MIN_VELOCITY);
			}
		}
		//oroku cach player PosX tu -400 --> -200
		else if (this->GetPosition().x - this->mPlayer->GetPosition().x > -Define::DANGEROUS_AREA_MAX_X * 2 &&
				this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MIN_X)
		{
			if (weapon->GetPosition() == weapon->originPos)
			{
				this->weapon->Mode = MapObject::WeaponMode::Fantastic;
				this->weapon->currentReverse = true;
				allowDrawWeapon = true;
				this->weapon->SetVy(Define::CIVILIAN_SWORD_MIN_VELOCITY);
			}
		}
	}
}

void CivilianCircus::SetState(OrokuState *newState)
{
	delete this->mOrokuData->state;

	this->mOrokuData->state = newState;

	mPreCurrentAnimation = mCurrentAnimation;
	this->changeAnimation(newState->GetState());

	if (mPreCurrentAnimation != nullptr)
		this->posY += (mPreCurrentAnimation->GetHeight() - mCurrentAnimation->GetHeight()) / 2.0f;

	mCurrentState = newState->GetState();
}

void CivilianCircus::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}

void CivilianCircus::SetPlayer(Player *player)
{
	this->mPlayer = player;
}

RECT CivilianCircus::GetBound()
{
	RECT rect;

	rect.left = this->posX - mCurrentAnimation->GetWidth() / 10;
	rect.right = this->posX + mCurrentAnimation->GetWidth() / 10;
	rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
	rect.bottom = this->posY + mCurrentAnimation->GetHeight() / 2;

	return rect;
}

void CivilianCircus::Draw(D3DXVECTOR2 trans)
{
	mCurrentAnimation->FlipVertical(this->mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), trans);
	if (allowDrawWeapon)
	{
		weapon->Draw(D3DXVECTOR3(weapon->posX, weapon->posY, 0), trans);
	}
}

void CivilianCircus::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	this->mOrokuData->state->OnCollision(impactor, side, data);
}

void CivilianCircus::changeAnimation(OrokuState::StateName state)
{
	switch (state)
	{
	case OrokuState::CivilianCircusStanding:
		delete mAnimationStanding;
		mAnimationStanding = new Animation("Resources/Orokus/Civilians/CivilianCircusStanding.png", 11, 1, 11, 0.05f);
		mCurrentAnimation = mAnimationStanding;
		break;

	default:
		break;
	}

	this->width = mCurrentAnimation->GetWidth();
	this->height = mCurrentAnimation->GetHeight();
}

OrokuState::StateName CivilianCircus::getState()
{
	return mCurrentState;
}