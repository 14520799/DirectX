#include "Player.h"
#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerSittingState.h"
#include "PlayerVerticalClimbingState.h"
#include "PlayerStandingAttackState.h"
#include "PlayerSittingAttackState.h"
#include "PlayerStandingThrowAppleState.h"
#include "../../GameComponents/GameCollision.h"

Player::Player()
{
	mAnimationStanding = new Animation("Resources/Aladdin/Standing.png", 32, 2, 16, 0.05f);
	mAnimationJumping = new Animation("Resources/Aladdin/Jumping.png", 1, 1, 1, 0.0f);
	mAnimationFalling = new Animation("Resources/Aladdin/Falling.png", 1, 1, 1, 0.0f);
	mAnimationRunning = new Animation("Resources/Aladdin/Running.png", 13, 1, 13, 0.02f);
	mAnimationSitting = new Animation("Resources/Aladdin/Sitting.png", 1, 1, 1, 0.0f);
	mAnimationVerticalClimbing = new Animation("Resources/Aladdin/VerticalClimbing.png", 10, 1, 10, 0.05f);
	mAnimationHorizontalClimbing = new Animation("Resources/Aladdin/HorizontalClimbing.png", 10, 1, 10, 0.05f);
	mAnimationStandingAttack = new Animation("Resources/Aladdin/Attack/StandingAttack.png", 5, 1, 5, 0.01f);
	mAnimationSittingAttack = new Animation("Resources/Aladdin/Attack/SittingAttack.png", 6, 1, 6, 0.01f);
	mAnimationStandingThrowApple = new Animation("Resources/Aladdin/Attack/StandingThrowApple.png", 6, 1, 6, 0.01f);

	this->mPlayerData = new PlayerData();
	this->mPlayerData->player = this;
	this->vx = 0;
	this->vy = 0;
	this->SetState(new PlayerFallingState(this->mPlayerData));

	allowJump = true;
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	mCurrentAnimation->Update(dt);

	if (this->mPlayerData->state)
	{
		this->mPlayerData->state->Update(dt);
	}

	Entity::Update(dt);
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
			if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing || mCurrentState == PlayerState::Sitting || mCurrentState == PlayerState::VerticalClimbing ||
				mCurrentState == PlayerState::StandingAttack || mCurrentState == PlayerState::SittingAttack)
			{
				this->SetState(new PlayerJumpingState(this->mPlayerData));
			}

			allowJump = false;
		}
	}
	else if (key == VK_DOWN)
	{
		if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing || mCurrentState == PlayerState::StandingAttack)
		{
			this->SetState(new PlayerSittingState(this->mPlayerData));
		}
	}
	else if (key == 0x41) //tan cong bang phim A
	{
		if (mCurrentState == PlayerState::Standing || mCurrentState == PlayerState::Running)
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
		if (mCurrentState == PlayerState::Standing || mCurrentState == PlayerState::StandingAttack || mCurrentState == PlayerState::Running)
		{
			this->SetState(new PlayerStandingThrowAppleState(this->mPlayerData));
		}
	}
}

void Player::OnKeyUp(int key)
{
	if (key == VK_SPACE)
	{
		allowJump = true;
	}
	else if (key == 0x41)
	{
		if (mCurrentState == PlayerState::SittingAttack)
		{
			this->SetState(new PlayerSittingState(this->mPlayerData));
		}
		else if (mCurrentState == PlayerState::StandingAttack)
		{
			this->SetState(new PlayerStandingState(this->mPlayerData));
		}
	}
	else if (key == 0x53)
	{
		if (mCurrentState == PlayerState::StandingThrowApple)
		{
			this->SetState(new PlayerStandingState(this->mPlayerData));
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

void Player::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mCurrentAnimation->FlipVertical(mCurrentReverse);
	mCurrentAnimation->SetPosition(this->GetPosition());

	if (mCamera)
	{
		D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
			GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);

		mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
	}
	else
	{
		mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0));
	}
}

void Player::SetState(PlayerState *newState)
{
	allowMoveLeft = true;
	allowMoveRight = true;
	allowMoveUp = true;

	delete this->mPlayerData->state;

	this->mPlayerData->state = newState;

	this->changeAnimation(newState->GetState());

	mCurrentState = newState->GetState();
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