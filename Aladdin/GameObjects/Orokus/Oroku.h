﻿#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "../../GameComponents/Animation.h"
#include "OrokuData.h"
#include "OrokuState.h"
#include "../Player/Player.h"
#include "../../GameComponents/QuadTree.h"
#include "../../GameObjects/MapObjects/MapObject.h"

class Oroku : public Entity
{
public:
	Oroku();
    ~Oroku();

	enum RunMode
	{
		None,
		RunAttack,
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

	virtual std::vector<MapObject*> GetListWeapon();

	bool mCurrentReverse, mPreCurrentReverse, settingAttack;
	bool allowDrawWeapon, allowDefault;
	bool settedPlayer; //da xet player cho oroku
	bool collisionFire; //xy ly khi oroku cham vao lua se chuyen sang state default
	bool collisionAppleWeapon;

	MapObject	*weapon,
				*weaponEffect;

	Player		*mPlayer;

	std::vector<MapObject*>	mListWeapon;
	std::vector<MapObject*>	mListWeaponEffect;
	std::vector<MapObject*> mListFireDecoration;//dung lua trang tri xung quanh cho boss snake;
protected:
	OrokuData *mOrokuData;

	Animation	*mCurrentAnimation,
				*mPreCurrentAnimation,
				*mAnimationDefault,
				*mAnimationLying,
				*mAnimationStanding,
				*mAnimationRunning,
				*mAnimationRunningFire,
				*mAnimationAttack,
				*mAnimationAttack2,
				*mAnimationHurting,
				*mAnimationThrowPot;

	virtual void changeAnimation(OrokuState::StateName state);

	OrokuState::StateName mCurrentState;

	float timeImunity;
};
