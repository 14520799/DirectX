#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../../GameComponents/Animation.h"
#include "../../GameComponents/GameGlobal.h"
#include "../../GameComponents/Camera.h"
#include "../../GameObjects/MapObjects/Brick.h"
#include "PlayerData.h"
#include "PlayerState.h"
#include "PlayerRunningState.h"

class Player : public Entity
{
public:
    Player();
    ~Player();

    enum MoveDirection
    {
        MoveToLeft, //chay tu phai sang trai
        MoveToRight, //chay tu trai sang phai
        None //dung im
    };

    void SetCamera(Camera *camera);

    void Update(float dt);

    void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

    void SetState(PlayerState *newState);

    void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

    void OnNoCollisionWithBottom();

	void AddListApple(Brick *brick);

    MoveDirection getMoveDirection();

    RECT GetBound();     

    PlayerState::StateName Player::getState();

    //xu ly input
    //gom 256 key tuong ung true = dang dc nhan, false = khong dc nhan
    void HandleKeyboard(std::map<int, bool> keys);

    void OnKeyPressed(int key);

    void OnKeyUp(int key);

    //true thi se lat nguoc anh theo truc y
    void SetReverse(bool flag);

	//set huong bay cua apple sau khi duoc nem ra
	void SetAppleFlyLeft(std::vector<Brick*> &listAppleFly, Brick *brick, int i, float dt);
	void SetAppleFlyRight(std::vector<Brick*> &listAppleFly, Brick *brick, int i, float dt);

    bool allowMoveLeft;
    bool allowMoveRight;
	bool allowMoveUp;
	bool allowDeath;
	bool allowDelayState;

	bool collisionApple; //kiem tra xem player da cham apple hay chua
protected:

    Camera      *mCamera;

    PlayerData *mPlayerData;

    Animation	*mCurrentAnimation,
				*mAnimationDefault,
                *mAnimationStanding,
                *mAnimationRunning,
                *mAnimationJumping,
				*mAnimationFalling,
				*mAnimationSitting,
				*mAnimationVerticalClimbing,
				*mAnimationHorizontalClimbing,
				*mAnimationStandingAttack,
				*mAnimationSittingAttack,
				*mAnimationJumpingAttack,
				*mAnimationHorizontalClimbingAttack,
				*mAnimationStandingThrowApple,
				*mAnimationSittingThrowApple,
				*mAnimationJumpingThrowApple,
				*mAnimationHorizontalClimbingThrowApple,
				*mAnimationDeath;

	std::vector<Brick*> mListApplePlayer; //apple cua player dang so huu
	std::vector<Brick*> mListAppleFly; //apple da duoc player nem di

    void changeAnimation(PlayerState::StateName state);

    PlayerState::StateName mCurrentState;

    //chi cho phep jump khi nhan nhim space, muon nhay lai phai tha phim space roi nhan lai
    bool allowJump, removedApple, mCurrentReverse;
	float timeDeath;
	float timeDelayStates;

	Brick *apple;
};

