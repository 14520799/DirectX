#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "../../GameComponents/Animation.h"
#include "OrokuData.h"
#include "OrokuState.h"
#include "../Player/Player.h"
#include "../../GameComponents/QuadTree.h"
#include "../../GameObjects/MapObjects/Item.h"

class Oroku : public Entity
{
public:
	Oroku();
    ~Oroku();

	enum RunMode
	{
		None,
		RunAttack,
		RunAround,
		RunComeback
	};

	RunMode Mode;

    virtual void Update(float dt);
        
	virtual void Draw(D3DXVECTOR2 transform);

	virtual void SetState(OrokuState *newState);

	virtual void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	virtual OrokuState::StateName getState() = 0;

	virtual RECT GetBound() = 0;

	virtual void SetReverse(bool flag);

	virtual void SetPlayer(Player *player);

	virtual void SetQuadTree(QuadTree *quadTree);

	virtual void OnNoCollisionWithBottom();

	bool mCurrentReverse, settedPlayer, settingAttack;
	bool allowDrawSword, allowDefault;

	Player *mPlayer;

	Item *sword;

	QuadTree *mQuadTree;

	D3DXVECTOR3 mOriginPosition;
protected:
	OrokuData *mOrokuData;

	Animation	*mCurrentAnimation,
				*mPreCurrentAnimation,
				*mAnimationDefault,
				*mAnimationStanding,
				*mAnimationRunning,
				*mAnimationAttack,
				*mAnimationHurting;

	virtual void changeAnimation(OrokuState::StateName state);

	OrokuState::StateName mCurrentState;
};
