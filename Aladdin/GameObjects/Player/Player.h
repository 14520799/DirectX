#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../../GameComponents/Animation.h"
#include "../../GameComponents/GameGlobal.h"
#include "../../GameComponents/Camera.h"
#include "../../GameComponents/GameMap.h"
#include "../../GameObjects/MapObjects/MapObject.h"
#include "../../GameComponents/Text.h"
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

	void InitPlayer();

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
	void SetAppleFlyLeft(std::vector<MapObject*> &listAppleFly, MapObject *mapObject, int i, float dt);
	void SetAppleFlyRight(std::vector<MapObject*> &listAppleFly, MapObject *mapObject, int i, float dt);

	std::vector<MapObject*> GetListAppleFly();

	bool allowMoveLeft, allowMoveRight, allowMoveUp;
	//state phai duoc thuc hien xong moi chuyen sang state khac sau khi tha phim ra
	bool allowDelayState;

	bool onKeyUpPressing; //thong bao aladdin dang nhin len tren
	bool onKeyDownPressing; //thong bao aladdin dang nhin xuong duoi
	bool collisionItem, collisionSpring, collisionRevitalization, collisionFeddler;
	bool collisionObjectMap;
	bool collisionStarWeapon, collisionFireWeapon;
	bool allowTranslateScene;//chuyen sang scene khac

	int demHurting;//khi player bi trung don thi se chay bien dem nay de the hien player dang bi thuong

	std::vector<MapObject*> mListApplePlayer; //apple cua player dang so huu
	std::vector<MapObject*> mListAppleFly; //apple da duoc player nem di
	std::vector<MapObject*> mListAppleEffect; //hieu ung cua apple truoc khi bi huy

	int mScorePlayer;
	int mRubyPlayer; //ruby cua player dang so huu
	int mLifePlayer; //life cua player dang so huu

	MapObject *apple;
	MapObject *appleEffect;

	PlayerState::StateName mCurrentState, mPreCurrentState;

	GameMap *mMap;

	Animation	*BloodInfo,
				*AppleInfo,
				*RubyInfo,
				*LifeInfo;
	D3DXVECTOR3 BloodInfoPos,
				AppleInfoPos,
				RubyInfoPos,
				LifeInfoPos;

	Text	*TxtScore,
			*TxtApple,
			*TxtRuby,
			*TxtLife;
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
				*mAnimationSomersault,
				*mAnimationStandingAttack,
				*mAnimationSittingAttack,
				*mAnimationJumpingAttack,
				*mAnimationClimbingAttack,
				*mAnimationStandingThrowApple,
				*mAnimationSittingThrowApple,
				*mAnimationJumpingThrowApple,
				*mAnimationClimbingThrowApple,
				*mAnimationDeath,
				*mAnimationRevival;

    void changeAnimation(PlayerState::StateName state);

    //chi cho phep jump khi nhan nhim space, muon nhay lai phai tha phim space roi nhan lai
    bool allowJump, mCurrentReverse;
	float timeImunity; //time duoc mien sat thuong sau khi hoi sinh
	float timeDelayStates; //time delay thuc thi xong state nay roi chuyen sang state khac
	float timeDelayForFalling;
};

