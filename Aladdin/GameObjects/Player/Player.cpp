#include "Player.h"
#include "PlayerDefaultState..h"
#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerSittingState.h"
#include "PlayerVerticalClimbingState.h"
#include "PlayerStandingAttackState.h"
#include "PlayerSittingAttackState.h"
#include "PlayerStandingThrowAppleState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"

Player::Player()
{
	mAnimationDefault = new Animation("Resources/Aladdin/Default.png", 1, 1, 1, 0.0f);
	mAnimationStanding = new Animation("Resources/Aladdin/Standing.png", 32, 2, 16, 0.05f);
	mAnimationJumping = new Animation("Resources/Aladdin/Jumping.png", 1, 1, 1, 0.0f);
	mAnimationFalling = new Animation("Resources/Aladdin/Falling.png", 1, 1, 1, 0.0f);
	mAnimationRunning = new Animation("Resources/Aladdin/Running.png", 13, 1, 13, 0.02f);
	mAnimationSitting = new Animation("Resources/Aladdin/Sitting.png", 1, 1, 1, 0.0f);
	mAnimationVerticalClimbing = new Animation("Resources/Aladdin/VerticalClimbing.png", 10, 1, 10, 0.05f);
	mAnimationHorizontalClimbing = new Animation("Resources/Aladdin/HorizontalClimbing.png", 10, 1, 10, 0.05f);
	mAnimationStandingAttack = new Animation("Resources/Aladdin/Attack/StandingAttack.png", 5, 1, 5, 0.03f);
	mAnimationSittingAttack = new Animation("Resources/Aladdin/Attack/SittingAttack.png", 6, 1, 6, 0.03f);
	mAnimationStandingThrowApple = new Animation("Resources/Aladdin/Attack/StandingThrowApple.png", 6, 1, 6, 0.02f);
	mAnimationDeath = new Animation("Resources/Aladdin/Death.png", 13, 1, 13, 0.1f);

	this->mPlayerData = new PlayerData();
	this->mPlayerData->player = this;
	this->vx = 0;
	this->vy = 0;
	this->SetState(new PlayerFallingState(this->mPlayerData));

	allowJump = true;
	allowDeath = true;
	allowDelayState = true;
	timeDeath = 0; //time duoc mien sat thuong sau khi hoi sinh
	timeDelayStates = 0; //time delay de thuc thi xong state nay roi chuyen sang state khac

	collisionApple = false; //cham vao qua tao
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	//animation cua player chay
	mCurrentAnimation->Update(dt);
	//them toc do cho player tuy vao state
	if (this->mPlayerData->state)
	{
		this->mPlayerData->state->Update(dt);
	}
	//player di chuyen sau khi tang toc do
	Entity::Update(dt);
	// neu list co qua tao dang duoc nem di thi set toc do cho qua tao
	if (mListAppleFly.size() > 0)
	{
		for (size_t i = 0; i < mListAppleFly.size(); i++)
		{
			mListAppleFly.at(i)->AddVx(Define::APPLE_SPEED);
			mListAppleFly.at(i)->Entity::Update(dt);
			//sau khi apple bay toc do max se bien mat
			if (mListAppleFly.at(i)->GetVx() >= Define::APPLE_MAX_SPEED)
			{
				Brick *temp = mListAppleFly.at(i);
				mListAppleFly.erase(mListAppleFly.begin() + i);
				delete temp;
				i--;
			}
		}
	}
	//state phai duoc thuc hien xong moi chuyen sang state khac sau khi tha phim ra
	if (allowDelayState)
	{
		switch (mCurrentState)
		{
		case PlayerState::Default:
			timeDelayStates += dt;
			if (timeDelayStates > 2.0f)			
				this->SetState(new PlayerStandingState(this->mPlayerData));
			break;

		case PlayerState::StandingAttack:
			timeDelayStates += dt;
			if (timeDelayStates > 0.17f)			
				this->SetState(new PlayerDefaultState(this->mPlayerData));
			break;

		case PlayerState::SittingAttack:
			timeDelayStates += dt;
			if (timeDelayStates > 0.2f)
				this->SetState(new PlayerSittingState(this->mPlayerData));
			break;

		case PlayerState::StandingThrowApple:
			timeDelayStates += dt;
			if (timeDelayStates > 0.17f)			
				this->SetState(new PlayerDefaultState(this->mPlayerData));
			break;

		default:
			break;
		}
	}
	//duoc mien sat thuong sau khi hoi sinh
	if (!allowDeath)
	{
		timeDeath += dt;

		if (timeDeath > 3.0f)
		{
			allowDeath = true;
			timeDeath = 0;
		}
	}
}

void Player::HandleKeyboard(std::map<int, bool> keys)
{
	if (this->mPlayerData->state)
	{
		this->mPlayerData->state->HandleKeyboard(keys);
	}
}

void Player::OnKeyPressed(int key)
{
	if (key == VK_SPACE)
	{
		if (allowJump)
		{
			if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing || mCurrentState == PlayerState::Sitting ||
				mCurrentState == PlayerState::Default || mCurrentState == PlayerState::StandingAttack || mCurrentState == PlayerState::SittingAttack)
			{
				this->SetState(new PlayerJumpingState(this->mPlayerData));
			}

			allowJump = false;
		}
	}
	else if (key == VK_DOWN)
	{
		if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing ||
			mCurrentState == PlayerState::Default || mCurrentState == PlayerState::StandingAttack)
		{
			this->SetState(new PlayerSittingState(this->mPlayerData));
		}
	}
	else if (key == 0x41) //tan cong bang phim A
	{
		if (mCurrentState == PlayerState::Standing || mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Default)
		{
			this->SetState(new PlayerStandingAttackState(this->mPlayerData));
		}
		else if (mCurrentState == PlayerState::Sitting)
		{
			this->SetState(new PlayerSittingAttackState(this->mPlayerData));
		}
	}
	else if (key == 0x53) //tan cong bang phim S
	{
		if (mCurrentState == PlayerState::Standing || mCurrentState == PlayerState::StandingAttack || 
			mCurrentState == PlayerState::Default || mCurrentState == PlayerState::Running)
		{
			this->SetState(new PlayerStandingThrowAppleState(this->mPlayerData));
		}

		if (mListApplePlayer.size() > 0)
		{
			apple = mListApplePlayer.at(mListApplePlayer.size() - 1);
			apple->SetPosition(this->GetPosition());
			mListAppleFly.push_back(apple); //lay ra qua tao trong player roi dua vao listapple quan ly viec bay ra ngoai
			mListApplePlayer.pop_back(); //lay qua tao ra khoi listapple cua player sau khi nem ra ngoai
		}
	}
}

void Player::OnKeyUp(int key)
{
	if (key == VK_SPACE)
	{
		allowJump = true;
	}
	else if (key == VK_DOWN)
	{
		this->SetState(new PlayerDefaultState(this->mPlayerData));
	}
	else if (key == 0x41 || key == 0x53)
	{
		if (mCurrentState == PlayerState::SittingAttack || mCurrentState == PlayerState::StandingAttack || mCurrentState == PlayerState::StandingThrowApple)
		{
			allowDelayState = true;
		}
	}
}

void Player::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}

void Player::SetCamera(Camera *camera)
{
	this->mCamera = camera;
}

void Player::AddListApple(Brick *brick)
{
	// neu va cham voi apple thi apple se duoc dua vao listapple cua player
	if (collisionApple)
	{
		mListApplePlayer.push_back(brick);
	}
}

void Player::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mCurrentAnimation->FlipVertical(mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());

	if (mCamera)
	{
		D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
			GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);
		//ve player theo state
		mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
		//ve qua tao bay ra
		if (mListAppleFly.size() > 0)
		{
			for (size_t i = 0; i < mListAppleFly.size(); i++)
			{
				mListAppleFly.at(i)->Draw(D3DXVECTOR3(mListAppleFly.at(i)->posX, mListAppleFly.at(i)->posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
			}
		}
	}
	else
	{
		mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0));

		if (mListAppleFly.size() > 0)
		{
			for (size_t i = 0; i < mListAppleFly.size(); i++)
			{
				mListAppleFly.at(i)->Draw(D3DXVECTOR3(mListAppleFly.at(i)->posX, mListAppleFly.at(i)->posY, 0));
			}
		}
	}

	
}

void Player::SetState(PlayerState *newState)
{
	allowMoveLeft = true;
	allowMoveRight = true;
	allowMoveUp = true;
	allowDelayState = false;
	collisionApple = false;
	timeDelayStates = 0;

	delete this->mPlayerData->state;

	this->mPlayerData->state = newState;

	this->changeAnimation(newState->GetState());

	mCurrentState = newState->GetState();

	if (mCurrentState == PlayerState::Default)
		allowDelayState = true;
}

void Player::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions size)
{
	this->mPlayerData->state->OnCollision(impactor, size, data);
}

RECT Player::GetBound()
{
	RECT rect;
	rect.left = this->posX - mCurrentAnimation->GetWidth() / 2;
	rect.right = rect.left + mCurrentAnimation->GetWidth();
	rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
	rect.bottom = rect.top + mCurrentAnimation->GetHeight();

	return rect;
}

void Player::changeAnimation(PlayerState::StateName state)
{
	switch (state)
	{
	case PlayerState::Default:
		mCurrentAnimation = mAnimationDefault;
		break;

	case PlayerState::Running:
		mCurrentAnimation = mAnimationRunning;
		break;

	case PlayerState::Standing:
		mCurrentAnimation = mAnimationStanding;
		break;

	case PlayerState::Falling:
		mCurrentAnimation = mAnimationFalling;
		break;

	case PlayerState::Jumping:
		mCurrentAnimation = mAnimationJumping;
		break;

	case PlayerState::Sitting:
		mCurrentAnimation = mAnimationSitting;
		break;

	case PlayerState::VerticalClimbing:
		mCurrentAnimation = mAnimationVerticalClimbing;
		break;

	case PlayerState::HorizontalClimbing:
		mCurrentAnimation = mAnimationHorizontalClimbing;
		break;

	case PlayerState::StandingAttack:
		mCurrentAnimation = mAnimationStandingAttack;
		break;

	case PlayerState::SittingAttack:
		mCurrentAnimation = mAnimationSittingAttack;
		break;

	case PlayerState::StandingThrowApple:
		mCurrentAnimation = mAnimationStandingThrowApple;
		break;

	case PlayerState::Death:
		mCurrentAnimation = mAnimationDeath;
		break;

	default:
		break;
	}

	this->width = mCurrentAnimation->GetWidth();
	this->height = mCurrentAnimation->GetHeight();
}

Player::MoveDirection Player::getMoveDirection()
{
	if (this->vx > 0)
	{
		return MoveDirection::MoveToRight;
	}
	else if (this->vx < 0)
	{
		return MoveDirection::MoveToLeft;
	}

	return MoveDirection::None;
}

void Player::OnNoCollisionWithBottom()
{
	if (mCurrentState != PlayerState::Jumping && mCurrentState != PlayerState::Falling && 
		mCurrentState != PlayerState::VerticalClimbing && mCurrentState != PlayerState::HorizontalClimbing)
	{
		this->SetState(new PlayerFallingState(this->mPlayerData));
	}
}

PlayerState::StateName Player::getState()
{
	return mCurrentState;
}