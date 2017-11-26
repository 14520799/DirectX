#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../../GameComponents/Animation.h"
#include "../../GameComponents/GameGlobal.h"
#include "../../GameComponents/Camera.h"
#include "../../GameComponents/GameMap.h"
#include "../../GameObjects/MapObjects/Item.h"
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

	void SetMap(GameMap *map);

    void Update(float dt);

    void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

    void SetState(PlayerState *newState);

    void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

    void OnNoCollisionWithBottom();

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
	bool GetReverse();

	//set huong bay cua apple sau khi duoc nem ra
	void SetAppleFlyLeft(std::vector<Item*> &listAppleFly, Item *item, int i, float dt);
	void SetAppleFlyRight(std::vector<Item*> &listAppleFly, Item *item, int i, float dt);

	std::vector<Item*> GetListAppleFly();

	bool allowMoveLeft;
	bool allowMoveRight;
	bool allowMoveUp;
	bool allowDeath;
	bool allowDelayState;

	bool onKeyUpPressing; //thong bao aladdin dang nhin len tren
	bool collisionAppleItem;

	std::vector<Item*> mListApplePlayer; //apple cua player dang so huu

	Item *apple;
	Item *appleEffect;

	GameMap *mMap;
protected:
    Camera      *mCamera;

    PlayerData	*mPlayerData;

    Animation	*mCurrentAnimation,
				*mPreCurrentAnimation,
				*mAnimationDefault,
                *mAnimationStanding,
				*mAnimationStandingUp,
				*mAnimationStandingUpStop,
                *mAnimationRunning,
				*mAnimationRunningStop,
				*mAnimationFalling,
				*mAnimationFallingStop,
				*mAnimationSitting,
				*mAnimationPushing,
				*mAnimationVerticalClimbing,
				*mAnimationVerticalClimbingDefault,
				*mAnimationHorizontalClimbing,
				*mAnimationHorizontalClimbingDefault,
				*mAnimationStandingJump,
				*mAnimationRunningJump,
				*mAnimationVerticalClimbingJump,
				*mAnimationStandingAttack,
				*mAnimationSittingAttack,
				*mAnimationJumpingAttack,
				*mAnimationClimbingAttack,
				*mAnimationStandingThrowApple,
				*mAnimationSittingThrowApple,
				*mAnimationJumpingThrowApple,
				*mAnimationClimbingThrowApple,
				*mAnimationDeath;

	std::vector<Item*> mListAppleFly; //apple da duoc player nem di
	std::vector<Item*> mListAppleEffect; //hieu ung cua apple truoc khi bi huy

    void changeAnimation(PlayerState::StateName state);

    PlayerState::StateName mCurrentState, mPreCurrentState;

    //chi cho phep jump khi nhan nhim space, muon nhay lai phai tha phim space roi nhan lai
    bool allowJump, removedApple, mCurrentReverse;
	float timeDeath;
	float timeDelayStates;
};

