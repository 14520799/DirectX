#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "../../GameComponents/Animation.h"
#include "OrokuData.h"
#include "OrokuState.h"
#include "../Player/Player.h"

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

	bool mCurrentReverse, settedPlayer, settedAttack;

	Player *mPlayer;

	D3DXVECTOR3 mOriginPosition;
protected:
	OrokuData *mOrokuData;

	Animation	*mCurrentAnimation,
				*mAnimationStanding,
				*mAnimationRunning,
				*mAnimationAttack;

	virtual void changeAnimation(OrokuState::StateName state);

	OrokuState::StateName mCurrentState;
};
