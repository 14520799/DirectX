#include "CivilianBasket.h"
#include "CivilianBasketStandingState.h"
#include "CivilianBasketRunningState.h"
#include "CivilianBasketAttackState.h"
#include "../../Player/Player.h"
#include "../../../GameDefines/GameDefine.h"

CivilianBasket::CivilianBasket(D3DXVECTOR3 position)
{
	this->mOriginPosition = position;
	this->SetPosition(mOriginPosition);
	this->Id = Entity::EntityId::CivilianBasket;

	this->mOrokuData = new OrokuData();
	this->mOrokuData->civilianBasket = this;
	this->vx = 0;
	this->vy = 0;
	this->allowRun = true;

	this->SetState(new CivilianBasketStandingState(this->mOrokuData));

	Mode = RunMode::None;

	if (!mPlayer)
	{
		settedPlayer = false;
	}
}

CivilianBasket::~CivilianBasket()
{

}

void CivilianBasket::Update(float dt)
{
	mCurrentAnimation->Update(dt);

	if (this->mOrokuData->state)
	{
		this->mOrokuData->state->Update(dt);
	}

	this->Entity::Update(dt);

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
	if (this->GetPosition().y - this->mPlayer->GetPosition().y > -Define::DANGEROUS_AREA_MAX_Y &&
		this->GetPosition().y - this->mPlayer->GetPosition().y < Define::DANGEROUS_AREA_MAX_Y)
	{
#pragma region OROKU RUN TO ATTACK PLAYER
		// khi co khoang cach voi player 0 < player < 200 thi oroku se chay toi tan cong player
		if (this->GetPosition().x - this->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MIN_X &&
			this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX_X &&
			!settingAttack && Mode != Oroku::RunMode::RunComeback)
		{
			Mode = RunMode::RunAttack;

			if (mSettingRightRun)
				mSettingRightRun = false;
			//neu oroku dang di sang ben trai thi return k can set state lai nua
			if (mSettingLeftRun)
			{
				return;
			}
			this->SetReverse(true);
			this->mSettingLeftRun = true;
			if (mPreCurrentReverse != mCurrentReverse || allowRun)
			{
				allowRun = true;
				this->SetState(new CivilianBasketRunningState(this->mOrokuData));
			}
		}
		else if (this->GetPosition().x - this->mPlayer->GetPosition().x > -Define::DANGEROUS_AREA_MAX_X &&
			this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MIN_X &&
			!settingAttack && Mode != Oroku::RunMode::RunComeback)
		{
			Mode = RunMode::RunAttack;

			if (mSettingLeftRun)
				mSettingLeftRun = false;
			//neu oroku dang di sang ben phai thi return k can set state lai nua
			if (mSettingRightRun)
			{
				return;
			}
			this->SetReverse(false);
			this->mSettingRightRun = true;
			if (mPreCurrentReverse != mCurrentReverse || allowRun)
			{
				allowRun = true;
				this->SetState(new CivilianBasketRunningState(this->mOrokuData));
			}
		}
#pragma endregion

#pragma region OROKU STANDING
		// khi co khoang cach voi player -400 --> 400 thi oroku se dung lai
		else if (this->GetPosition().x - this->mPlayer->GetPosition().x > -Define::DANGEROUS_AREA_MAX_X * 2 &&
			this->GetPosition().x - this->mPlayer->GetPosition().x < Define::DANGEROUS_AREA_MAX_X * 2 && !settingAttack &&
			Mode != Oroku::RunMode::RunComeback)
		{
			if (mCurrentState != OrokuState::CivilianBasketStanding)
				this->SetState(new CivilianBasketStandingState(this->mOrokuData));
		}
#pragma endregion

#pragma region OROKU RUN COMEBACK
		// khi co khoang cach voi player -600 --> 600 thi oroku se quay ve cho cu
		else if ((this->GetPosition().x - this->mPlayer->GetPosition().x < -Define::DANGEROUS_AREA_MAX_X * 2 ||
			this->GetPosition().x - this->mPlayer->GetPosition().x > Define::DANGEROUS_AREA_MAX_X * 2) &&
			Mode == Oroku::RunMode::RunAttack)
		{
			Mode = Oroku::RunMode::RunComeback;
			this->SetState(new CivilianBasketRunningState(this->mOrokuData));
		}
#pragma endregion
	}
}

void CivilianBasket::SetState(OrokuState *newState)
{
	delete this->mOrokuData->state;

	this->mOrokuData->state = newState;

	mPreCurrentAnimation = mCurrentAnimation;
	this->changeAnimation(newState->GetState());

	if (mPreCurrentAnimation != nullptr)
		this->posY += (mPreCurrentAnimation->GetHeight() - mCurrentAnimation->GetHeight()) / 2.0f;

	mCurrentState = newState->GetState();
}

void CivilianBasket::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}

void CivilianBasket::SetPlayer(Player *player)
{
	this->mPlayer = player;
}

RECT CivilianBasket::GetBound()
{
	RECT rect;

	if (mCurrentState == OrokuState::CivilianBasketAttack)
	{
		rect.left = this->posX - mCurrentAnimation->GetWidth() / 2;
		rect.right = rect.left + mCurrentAnimation->GetWidth();
		rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
		rect.bottom = rect.top + mCurrentAnimation->GetHeight();
	}
	else
	{
		rect.left = this->posX - mCurrentAnimation->GetWidth() / 10;
		rect.right = this->posX + mCurrentAnimation->GetWidth() / 10;
		rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
		rect.bottom = rect.top + mCurrentAnimation->GetHeight();
	}

	return rect;
}

void CivilianBasket::Draw(D3DXVECTOR2 trans)
{
	mCurrentAnimation->FlipVertical(this->mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), trans);
}

void CivilianBasket::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	this->mOrokuData->state->OnCollision(impactor, side, data);
}

void CivilianBasket::changeAnimation(OrokuState::StateName state)
{
	switch (state)
	{
	case OrokuState::CivilianBasketStanding:
		delete mAnimationStanding;
		mAnimationStanding = new Animation("Resources/Orokus/Civilians/CivilianBasketStanding.png", 6, 1, 6, 0.4f);
		mCurrentAnimation = mAnimationStanding;
		break;

	case OrokuState::CivilianBasketRunning:
		delete mAnimationRunning;
		mAnimationRunning = new Animation("Resources/Orokus/Civilians/CivilianBasketRunning.png", 12, 1, 12, 0.2f);
		mCurrentAnimation = mAnimationRunning;
		break;

	case OrokuState::CivilianBasketAttack:
		delete mAnimationAttack;
		mAnimationAttack = new Animation("Resources/Orokus/Civilians/CivilianBasketAttack.png", 4, 1, 4, 0.2f);
		mCurrentAnimation = mAnimationAttack;
		break;

	Standing:
		break;
	}

	this->width = mCurrentAnimation->GetWidth();
	this->height = mCurrentAnimation->GetHeight();
}

OrokuState::StateName CivilianBasket::getState()
{
	return mCurrentState;
}
