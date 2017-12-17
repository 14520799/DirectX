#include "FatGuard.h"
#include "FatGuardStandingState.h"
#include "FatGuardRunningState.h"
#include "FatGuardAttackState.h"
#include "FatGuardDefaultState.h"
#include "FatGuardHurtingState.h"
#include "../../Player/Player.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../MapObjects/Weapons/SwordWeapon.h"
#include "../../MapObjects/Weapons/SwordWeaponEffect.h"

FatGuard::FatGuard(D3DXVECTOR3 position)
{
	mAnimationDefault = new Animation("Resources/Orokus/Guards/FatGuardDefault.png", 1, 1, 1, 0.0f);

	this->mOriginPosition = position;
	this->SetPosition(mOriginPosition);
	this->Id = Entity::EntityId::Guard;

	this->mOrokuData = new OrokuData();
	this->mOrokuData->fatGuard = this;
	this->vx = 0;
	this->vy = 0;

	this->SetState(new FatGuardStandingState(this->mOrokuData));

	Mode = RunMode::None;

	if (!mPlayer)
	{
		settedPlayer = false;
	}

	this->weapon = new SwordWeapon(D3DXVECTOR3(this->GetPosition().x, this->GetPosition().y - this->mOrokuData->fatGuard->GetHeight() / 2, 0));
	this->weapon->Tag = Entity::EntityTypes::Sword;
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
		if (allowDrawWeapon)
		{
			weapon->Update(dt);
			weapon->Entity::Update(dt);
		}
	}

	this->Entity::Update(dt);

	//neu sword va cham voi player thi se bien mat
	if (weapon->collisionWithPlayer || weapon->weaponCollided)
	{
		weaponEffect = new SwordWeaponEffect(weapon->GetPosition());
		allowDrawWeapon = false;
		weapon->SetPosition(0, 0);
		weapon->collisionWithPlayer = false;
		weapon->weaponCollided = false;
	}

	if (weaponEffect != nullptr)
	{
		weaponEffect->timeDelayWeaponEffect += dt;
		weaponEffect->Update(dt);
		if (weaponEffect->timeDelayWeaponEffect > 0.4f)
		{
			delete weaponEffect;
			weaponEffect = nullptr;
		}
	}

	if (allowImunity)
	{
		timeImunity += dt;

		if (timeImunity > 0.5f)
		{
			allowImunity = false;
			timeImunity = 0;
		}
	}

	//xet khoach cach voi player theo truc y -150 -> 150
	if (this->GetPosition().y - this->mPlayer->GetPosition().y > -Define::DANGEROUS_AREA_MAX_Y / 8 &&
		this->GetPosition().y - this->mPlayer->GetPosition().y < Define::DANGEROUS_AREA_MAX_Y)
	{
		//delay 1 khoang time de thuc hien statedefault
		if (!allowDefault)
		{
#pragma region OROKU ATTACK PLAYER
			// khi co khoang cach voi player 0 < player < 200 thi oroku se tan cong player
			if ((this->GetPosition().x - this->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN_X &&
				this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX_X))
			{
				Mode = RunMode::None;

				//khi cay kiem dang bay ra theo huong nao thi se tiep tuc bay theo huong do 
				//cho du player co di qua phia ben kia cua fatguard
				if (this->weapon->mSettingLeftItem)
				{
					this->weapon->AddVx(-Define::ITEM_SPEED_X);
					//xu ly Vy
					if (this->mOrokuData->fatGuard->weapon->GetVy() <= Define::ITEM_MIN_VELOCITY || this->mOrokuData->fatGuard->weapon->DirectionDown)
					{
						this->mOrokuData->fatGuard->weapon->AddVy(Define::ITEM_SPEED_Y);
						this->mOrokuData->fatGuard->weapon->DirectionDown = true;
					}
					else if (this->mOrokuData->fatGuard->weapon->GetVy() > Define::ITEM_MIN_VELOCITY)
						this->mOrokuData->fatGuard->weapon->AddVy(-Define::ITEM_SPEED_Y);
					this->timeDelayDefaultState += dt;
					if (this->timeDelayDefaultState > 0.8f)
					{
						this->timeDelayDefaultState = 0;
						this->SetState(new FatGuardDefaultState(this->mOrokuData));
					}
					return;
				}
				else if (this->weapon->mSettingRightItem)
				{
					this->weapon->AddVx(Define::ITEM_SPEED_X);
					if (this->mOrokuData->fatGuard->weapon->GetVy() <= Define::ITEM_MIN_VELOCITY || this->mOrokuData->fatGuard->weapon->DirectionDown)
					{
						this->mOrokuData->fatGuard->weapon->AddVy(Define::ITEM_SPEED_Y);
						this->mOrokuData->fatGuard->weapon->DirectionDown = true;
					}
					else if (this->mOrokuData->fatGuard->weapon->GetVy() > Define::ITEM_MIN_VELOCITY)
						this->mOrokuData->fatGuard->weapon->AddVy(-Define::ITEM_SPEED_Y);					this->timeDelayDefaultState += dt;
					if (this->timeDelayDefaultState > 0.8f)
					{
						this->timeDelayDefaultState = 0;
						this->SetState(new FatGuardDefaultState(this->mOrokuData));
					}
					return;
				}

				if (mSettingRightAttack)
					mSettingRightAttack = false;
				//neu oroku dang di sang ben trai thi return k can set state lai nua
				if (mSettingLeftAttack)
				{
					return;
				}
				this->SetReverse(false);
				this->allowDrawWeapon = true;
				this->timeDelayDefaultState = 0;
				this->SetState(new FatGuardAttackState(this->mOrokuData));
				this->mSettingLeftAttack = true;
			}
			else if ((this->GetPosition().x - this->mPlayer->GetPosition().x) > -Define::DANGEROUS_AREA_MAX_X &&
				(this->GetPosition().x - this->mPlayer->GetPosition().x) < Define::DANGEROUS_AREA_MIN_X)
			{
				Mode = RunMode::None;

				if (this->weapon->mSettingLeftItem)
				{
					this->weapon->AddVx(-Define::ITEM_SPEED_X);
					if (this->mOrokuData->fatGuard->weapon->GetVy() <= Define::ITEM_MIN_VELOCITY || this->mOrokuData->fatGuard->weapon->DirectionDown)
					{
						this->mOrokuData->fatGuard->weapon->AddVy(Define::ITEM_SPEED_Y);
						this->mOrokuData->fatGuard->weapon->DirectionDown = true;
					}
					else if (this->mOrokuData->fatGuard->weapon->GetVy() > Define::ITEM_MIN_VELOCITY)
						this->mOrokuData->fatGuard->weapon->AddVy(-Define::ITEM_SPEED_Y);
					this->timeDelayDefaultState += dt;
					if (this->timeDelayDefaultState > 0.8f)
					{
						this->timeDelayDefaultState = 0;
						this->SetState(new FatGuardDefaultState(this->mOrokuData));
					}
					return;
				}
				else if (this->weapon->mSettingRightItem)
				{
					this->weapon->AddVx(Define::ITEM_SPEED_X);
					if (this->mOrokuData->fatGuard->weapon->GetVy() <= Define::ITEM_MIN_VELOCITY || this->mOrokuData->fatGuard->weapon->DirectionDown)
					{
						this->mOrokuData->fatGuard->weapon->AddVy(Define::ITEM_SPEED_Y);
						this->mOrokuData->fatGuard->weapon->DirectionDown = true;
					}
					else if (this->mOrokuData->fatGuard->weapon->GetVy() > Define::ITEM_MIN_VELOCITY)
						this->mOrokuData->fatGuard->weapon->AddVy(-Define::ITEM_SPEED_Y);
					this->timeDelayDefaultState += dt;
					if (this->timeDelayDefaultState > 0.8f)
					{
						this->timeDelayDefaultState = 0;
						this->SetState(new FatGuardDefaultState(this->mOrokuData));
					}
					return;
				}
				if (mSettingLeftAttack)
					mSettingLeftAttack = false;
				//neu oroku dang di sang ben phai thi return k can set state lai nua
				if (mSettingRightAttack)
				{
					return;
				}
				this->SetReverse(true);
				this->allowDrawWeapon = true;
				this->timeDelayDefaultState = 0;
				this->SetState(new FatGuardAttackState(this->mOrokuData));
				this->mSettingRightAttack = true;
			}
#pragma endregion

#pragma region OROKU DEFAULT
			else if (((this->GetPosition().x - this->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN_X &&
				this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX_X * 1.2f)
				||
				(this->GetPosition().x - this->mPlayer->GetPosition().x > -Define::DANGEROUS_AREA_MAX_X * 1.2f &&
					this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MIN_X))
				&& Mode != Oroku::RunMode::RunAttack)
			{
				if (this->weapon->mSettingLeftItem)
				{
					this->weapon->AddVx(-Define::ITEM_SPEED_X);
					if (this->mOrokuData->fatGuard->weapon->GetVy() <= Define::ITEM_MIN_VELOCITY || this->mOrokuData->fatGuard->weapon->DirectionDown)
					{
						this->mOrokuData->fatGuard->weapon->AddVy(Define::ITEM_SPEED_Y);
						this->mOrokuData->fatGuard->weapon->DirectionDown = true;
					}
					else if (this->mOrokuData->fatGuard->weapon->GetVy() > Define::ITEM_MIN_VELOCITY)
						this->mOrokuData->fatGuard->weapon->AddVy(-Define::ITEM_SPEED_Y);					
					this->timeDelayDefaultState += dt;
					if (this->timeDelayDefaultState > 0.8f)
					{
						this->timeDelayDefaultState = 0;
						this->SetState(new FatGuardDefaultState(this->mOrokuData));
					}
					return;
				}
				else if (this->weapon->mSettingRightItem)
				{
					this->weapon->AddVx(Define::ITEM_SPEED_X);
					if (this->mOrokuData->fatGuard->weapon->GetVy() <= Define::ITEM_MIN_VELOCITY || this->mOrokuData->fatGuard->weapon->DirectionDown)
					{
						this->mOrokuData->fatGuard->weapon->AddVy(Define::ITEM_SPEED_Y);
						this->mOrokuData->fatGuard->weapon->DirectionDown = true;
					}
					else if (this->mOrokuData->fatGuard->weapon->GetVy() > Define::ITEM_MIN_VELOCITY)
						this->mOrokuData->fatGuard->weapon->AddVy(-Define::ITEM_SPEED_Y);					
					this->timeDelayDefaultState += dt;
					if (this->timeDelayDefaultState > 0.8f)
					{
						this->timeDelayDefaultState = 0;
						this->SetState(new FatGuardDefaultState(this->mOrokuData));
					}
					return;
				}
			}
#pragma endregion

#pragma region OROKU RUN TO ATTACK PLAYER
			// khi co khoang cach voi player -30 < player < 200 thi oroku se chay toi tan cong player
			else if (this->GetPosition().x - this->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN_X &&
				this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX_X * 1.4f)
			{
				Mode = RunMode::RunAttack;

				if (mSettingRightRun)
					mSettingRightRun = false;
				//neu oroku dang di sang ben trai thi return k can set state lai nua
				if (mSettingLeftRun)
				{
					return;
				}
				this->SetReverse(false);
				this->timeDelayDefaultState = 0;
				this->mSettingLeftRun = true;
				if (mPreCurrentReverse != mCurrentReverse || !collisionFire)
				{
					collisionFire = false;
					this->SetState(new FatGuardRunningState(this->mOrokuData));
				}
			}
			else if ((this->GetPosition().x - this->mPlayer->GetPosition().x) > -Define::DANGEROUS_AREA_MAX_X * 1.4f &&
				(this->GetPosition().x - this->mPlayer->GetPosition().x) < Define::DANGEROUS_AREA_MIN_X)
			{
				Mode = RunMode::RunAttack;

				if (mSettingLeftRun)
					mSettingLeftRun = false;
				//neu oroku dang di sang ben phai thi return k can set state lai nua
				if (mSettingRightRun)
				{
					return;
				}
				this->SetReverse(true);
				this->timeDelayDefaultState = 0;
				this->mSettingRightRun = true;
				if (mPreCurrentReverse != mCurrentReverse || !collisionFire)
				{
					collisionFire = false;
					this->SetState(new FatGuardRunningState(this->mOrokuData));
				}
			}
#pragma endregion

#pragma region OROKU RUN COMEBACK
			// khi co khoang cach voi player < -500 hoac > 500 thi oroku se quay ve cho cu
			else if ((this->GetPosition().x - this->mPlayer->GetPosition().x < -Define::DANGEROUS_AREA_MAX_X * 2 ||
				this->GetPosition().x - this->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MAX_X * 2) &&
				Mode == Oroku::RunMode::RunAttack)
			{
				Mode = Oroku::RunMode::RunComeback;
				mSettingRightRun = false;
				mSettingLeftRun = false;
				this->allowDrawWeapon = false;
				this->SetState(new FatGuardRunningState(this->mOrokuData));
			}
#pragma endregion
		}
	}
}

void FatGuard::SetState(OrokuState *newState)
{
	delete this->mOrokuData->state;

	this->mOrokuData->state = newState;

	mPreCurrentAnimation = mCurrentAnimation;
	this->changeAnimation(newState->GetState());

	if (mPreCurrentAnimation != nullptr)
		this->posY += (mPreCurrentAnimation->GetHeight() - mCurrentAnimation->GetHeight()) / 2.0f;

	mCurrentState = newState->GetState();
}

void FatGuard::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}

RECT FatGuard::GetBound()
{
	RECT rect;

	rect.left = this->posX - mCurrentAnimation->GetWidth() / 4;
	rect.right = this->posX + mCurrentAnimation->GetWidth() / 4;
	rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
	rect.bottom = rect.top + mCurrentAnimation->GetHeight();

	return rect;
}

bool FatGuard::GetReverse()
{
	return mCurrentReverse;
}

void FatGuard::Draw(D3DXVECTOR2 trans)
{
	mCurrentAnimation->FlipVertical(this->mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), trans);
	if (allowDrawWeapon)
	{
		weapon->Draw(D3DXVECTOR3(weapon->posX, weapon->posY, 0), trans);
	}
	if (weaponEffect != nullptr)
		weaponEffect->Draw(D3DXVECTOR3(weaponEffect->posX, weaponEffect->posY, 0), trans);
}

void FatGuard::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if ((this->allowImunity || this->collisionAppleWeapon) && mCurrentState != OrokuState::FatGuardHurting)
	{
		this->collisionAppleWeapon = false;
		this->SetState(new FatGuardHurtingState(this->mOrokuData));
		return;
	}
	this->mOrokuData->state->OnCollision(impactor, side, data);
}

void FatGuard::changeAnimation(OrokuState::StateName state)
{
	switch (state)
	{
	case OrokuState::FatGuardDefault:
		mCurrentAnimation = mAnimationDefault;
		break;

	case OrokuState::FatGuardStanding:
		delete mAnimationStanding;
		mAnimationStanding = new Animation("Resources/Orokus/Guards/FatGuardStanding.png", 7, 1, 7, 0.15f);
		mCurrentAnimation = mAnimationStanding;
		break;

	case OrokuState::FatGuardRunning:
		delete mAnimationRunning;
		mAnimationRunning = new Animation("Resources/Orokus/Guards/FatGuardRunning.png", 8, 1, 8, 0.1f);
		mCurrentAnimation = mAnimationRunning;
		break;

	case OrokuState::FatGuardAttack:
		delete mAnimationAttack;
		mAnimationAttack = new Animation("Resources/Orokus/Guards/FatGuardAttack.png", 5, 1, 5, 0.1f);
		mCurrentAnimation = mAnimationAttack;
		break;

	case OrokuState::FatGuardHurting:
		delete mAnimationHurting;
		mAnimationHurting = new Animation("Resources/Orokus/Guards/FatGuardHurting.png", 7, 1, 7, 0.1f);
		mCurrentAnimation = mAnimationHurting;
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


