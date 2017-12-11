#include "Jafar.h"
#include "JafarDefaultState.h"
#include "JafarWitchAttackState.h"
#include "JafarSnakeAttackState.h"
#include "../..//MapObjects/Weapons/FireEffect.h"
#include "../../MapObjects/Weapons/StarWeaponEffect.h"
#include "../../MapObjects/Items/LampEffect.h"
#include "../../Player/Player.h"
#include "../../../GameDefines/GameDefine.h"

Jafar::Jafar(D3DXVECTOR3 position)
{
	this->mOriginPosition = position;
	this->SetPosition(mOriginPosition);
	this->Id = Entity::EntityId::BossJafar;

	this->mOrokuData = new OrokuData();
	this->mOrokuData->jafar = this;
	this->vx = 0;
	this->vy = 0;

	if (!mPlayer)
	{
		settedPlayer = false;
	}

	TransfigureEffect = nullptr;
	this->SetState(new JafarDefaultState(this->mOrokuData));
}

Jafar::~Jafar()
{

}

void Jafar::Update(float dt)
{
	if (this->bloodOfEntity == Define::BOSS_BLOOD / 2 && mCurrentState != OrokuState::JafarSnakeAttack)
	{
		for (size_t i = 0; i < mListWeapon.size(); i++)
		{
			weaponEffect = new StarWeaponEffect(mListWeapon.at(i)->GetPosition());
			mListWeaponEffect.push_back(weaponEffect);
			delete mListWeapon.at(i);
			mListWeapon.at(i) = nullptr;
			mListWeapon.erase(mListWeapon.begin() + i);
			if (mListWeapon.size() == 0)
				break;
			i--;
			continue;
		}
		mListWeapon.clear();
		TransfigureEffect = new LampEffect(this->GetPosition() + D3DXVECTOR3(0, -140, 0));
		this->SetState(new JafarSnakeAttackState(this->mOrokuData));
	}

	if (TransfigureEffect != nullptr)
	{
		TransfigureEffect->Update(dt);
		timeDelayTransfigureEffect += dt;
		if (timeDelayTransfigureEffect > 2.0f)
		{
			delete TransfigureEffect;
			TransfigureEffect = nullptr;
		}
	}

	mCurrentAnimation->Update(dt);

	if (this->mOrokuData->state)
	{
		this->mOrokuData->state->Update(dt);
	}

	this->Entity::Update(dt);

	//neu weapon va cham voi player thi se bien mat
	if (mCurrentState == OrokuState::JafarWitchAttack || mCurrentState == OrokuState::JafarDefault)
	{
		//xu ly nhung starWeapon
		if (mListWeapon.size() > 0)
		{
			for (size_t i = 0; i < mListWeapon.size(); i++)
			{
				if (mListWeapon.at(i)->collisionWithPlayer)
				{
					weaponEffect = new StarWeaponEffect(mPlayer->GetPosition());
					mListWeaponEffect.push_back(weaponEffect);
					delete mListWeapon.at(i);
					mListWeapon.at(i) = nullptr;
					mListWeapon.erase(mListWeapon.begin() + i);
					if (mListWeapon.size() == 0)
						break;
					i--;
					continue;
				}

				//weapon dang o phia tren ben trai
				if (mListWeapon.at(i)->GetPosition().x - mPlayer->GetPosition().x < 0 &&
					mListWeapon.at(i)->GetPosition().y - mPlayer->GetPosition().y < 0)
				{
					mListWeapon.at(i)->AddVx(Define::ITEM_SPEED_X);
					mListWeapon.at(i)->AddVy(Define::ITEM_SPEED_Y);
				}
				//weapon dang o phia tren ben phai
				else if (mListWeapon.at(i)->GetPosition().x - mPlayer->GetPosition().x >= 0 &&
					mListWeapon.at(i)->GetPosition().y - mPlayer->GetPosition().y < 0)
				{
					mListWeapon.at(i)->AddVx(-Define::ITEM_SPEED_X);
					mListWeapon.at(i)->AddVy(Define::ITEM_SPEED_Y);
				}
				//weapon dang o phia duoi ben trai
				else if (mListWeapon.at(i)->GetPosition().x - mPlayer->GetPosition().x < 0 &&
					mListWeapon.at(i)->GetPosition().y - mPlayer->GetPosition().y >= 0)
				{
					mListWeapon.at(i)->AddVx(Define::ITEM_SPEED_X);
					mListWeapon.at(i)->AddVy(-Define::ITEM_SPEED_Y);
				}
				//weapon dang o phia duoi ben phai
				else if (mListWeapon.at(i)->GetPosition().x - mPlayer->GetPosition().x >= 0 &&
					mListWeapon.at(i)->GetPosition().y - mPlayer->GetPosition().y >= 0)
				{
					mListWeapon.at(i)->AddVx(-Define::ITEM_SPEED_X);
					mListWeapon.at(i)->AddVy(-Define::ITEM_SPEED_Y);
				}
				mListWeapon.at(i)->Update(dt);
				mListWeapon.at(i)->Entity::Update(dt);
			}
		}
	}
	else if (mCurrentState == OrokuState::JafarSnakeAttack)
	{
		//xu ly nhung fireWeapon
		if (mListWeapon.size() > 0)
		{
			for (size_t i = 0; i < mListWeapon.size(); i++)
			{
				//xoa ngon lua cua snake khi bay ra duoc 400 pixel
				if (mListWeapon.at(i)->GetPosition().x - this->GetPosition().x > 600 ||
					mListWeapon.at(i)->GetPosition().x - this->GetPosition().x < -600)
				{
					delete mListWeapon.at(i);
					mListWeapon.at(i) = nullptr;
					mListWeapon.erase(mListWeapon.begin() + i);
					if (mListWeapon.size() == 0)
						break;
					i--;
					continue;
				}

				if (mListWeapon.at(i)->directionFireWeapon == Entity::DirectionFireWeapon::DirectionNone)
				{
					//fireWeapon dang o phia ben phai player
					if (mListWeapon.at(i)->GetPosition().x - mPlayer->GetPosition().x >= 0)
					{
						mListWeapon.at(i)->currentObjectReverse = true;
						mListWeapon.at(i)->directionFireWeapon = Entity::DirectionFireWeapon::DirectionLeft;
					}
					//fireWeapon dang o phia ben trai player
					else if (this->GetPosition().x - mPlayer->GetPosition().x < 0)
					{
						mListWeapon.at(i)->currentObjectReverse = false;
						mListWeapon.at(i)->directionFireWeapon = Entity::DirectionFireWeapon::DirectionRight;
					}
				}
				if (mListWeapon.at(i)->directionFireWeapon == Entity::DirectionFireWeapon::DirectionLeft)
					mListWeapon.at(i)->AddVx(-Define::ITEM_SPEED_X / 4);
				else if (mListWeapon.at(i)->directionFireWeapon == Entity::DirectionFireWeapon::DirectionRight)
					mListWeapon.at(i)->AddVx(Define::ITEM_SPEED_X / 4);
				mListWeapon.at(i)->Update(dt);
				mListWeapon.at(i)->Entity::Update(dt);
			}
		}
	}

	//xu ly nhung hieu ung cua starWeapon khi cham vao aladdin
	if (mListWeaponEffect.size() > 0)
	{
		for (size_t i = 0; i < mListWeaponEffect.size(); i++)
		{
			mListWeaponEffect.at(i)->Update(dt);
			mListWeaponEffect.at(i)->timeDelayWeaponEffect += dt;
			if (mListWeaponEffect.at(i)->Id == Entity::EntityId::StarEffect)
			{
				if (mListWeaponEffect.at(i)->timeDelayWeaponEffect > 0.1f)
				{
					delete mListWeaponEffect.at(i);
					mListWeaponEffect.at(i) = nullptr;
					mListWeaponEffect.erase(mListWeaponEffect.begin() + i);
					if (mListWeaponEffect.size() == 0)
						break;
					i--;
				}
			}
			else if (mListWeaponEffect.at(i)->Id == Entity::EntityId::FireEffect)
			{
				if (mListWeaponEffect.at(i)->timeDelayWeaponEffect > 0.5f)
				{
					delete mListWeaponEffect.at(i);
					mListWeaponEffect.at(i) = nullptr;
					mListWeaponEffect.erase(mListWeaponEffect.begin() + i);
					if (mListWeaponEffect.size() == 0)
						break;
					i--;
				}
			}
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
}

void Jafar::SetState(OrokuState *newState)
{
	delete this->mOrokuData->state;

	this->mOrokuData->state = newState;

	mPreCurrentAnimation = mCurrentAnimation;
	this->changeAnimation(newState->GetState());

	if (mPreCurrentAnimation != nullptr)
		this->posY += (mPreCurrentAnimation->GetHeight() - mCurrentAnimation->GetHeight()) / 2.0f;

	mCurrentState = newState->GetState();
}

void Jafar::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}

void Jafar::SetPlayer(Player *player)
{
	this->mPlayer = player;
}

RECT Jafar::GetBound()
{
	RECT rect;

	rect.left = this->posX - mCurrentAnimation->GetWidth() / 10;
	rect.right = this->posX + mCurrentAnimation->GetWidth() / 10;
	rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
	rect.bottom = this->posY + mCurrentAnimation->GetHeight() / 2;

	return rect;
}

void Jafar::Draw(D3DXVECTOR2 trans)
{
	mCurrentAnimation->FlipVertical(this->mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());
	mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), trans);
	if (mListWeapon.size() > 0)
	{
		for (size_t i = 0; i < mListWeapon.size(); i++)
		{
			mListWeapon.at(i)->mAnimation->FlipVertical(mListWeapon.at(i)->currentObjectReverse);
			mListWeapon.at(i)->SetPosition(mListWeapon.at(i)->GetPosition());
			mListWeapon.at(i)->Draw(D3DXVECTOR3(mListWeapon.at(i)->posX, mListWeapon.at(i)->posY, 0), trans);
		}
	}
	if (mListWeaponEffect.size() > 0)
	{
		for (size_t i = 0; i < mListWeaponEffect.size(); i++)
		{
			mListWeaponEffect.at(i)->Draw(D3DXVECTOR3(mListWeaponEffect.at(i)->posX, mListWeaponEffect.at(i)->posY, 0), trans);
		}
	}
	if (TransfigureEffect != nullptr)
		TransfigureEffect->Draw(trans);
}

void Jafar::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	this->mOrokuData->state->OnCollision(impactor, side, data);
}

void Jafar::changeAnimation(OrokuState::StateName state)
{
	switch (state)
	{
	case OrokuState::JafarDefault:
		delete mAnimationDefault;
		mAnimationDefault = new Animation("Resources/Orokus/Jafar/JafarDefault.png", 1, 1, 1, 0.0f);
		mCurrentAnimation = mAnimationDefault;
		break;
	case OrokuState::JafarWitchAttack:
		delete mAnimationAttack;
		mAnimationAttack = new Animation("Resources/Orokus/Jafar/JafarWitchAttack.png", 8, 1, 8, 0.05f);
		mCurrentAnimation = mAnimationAttack;
		break;
	case OrokuState::JafarSnakeAttack:
		delete mAnimationAttack2;
		mAnimationAttack2 = new Animation("Resources/Orokus/Jafar/JafarSnakeAttack.png", 11, 1, 11, 0.04f);
		mCurrentAnimation = mAnimationAttack2;
		break;

	default:
		break;
	}

	this->width = mCurrentAnimation->GetWidth();
	this->height = mCurrentAnimation->GetHeight();
}

OrokuState::StateName Jafar::getState()
{
	return mCurrentState;
}

std::vector<MapObject*> Jafar::GetListWeapon()
{
	return mListWeapon;
}