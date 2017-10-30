#pragma once
#include "../../../GameComponents/Animation.h"
#include "../Oroku.h"
#include "../OrokuData.h"
#include "../OrokuState.h"

class FatGuard : public Oroku
{
public:
	FatGuard(D3DXVECTOR3 position);
    ~FatGuard();

	void Update(float dt);

	void Draw(D3DXVECTOR2 trans);

	void SetState(OrokuState *newState);

	void SetReverse(bool flag);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions);

	RECT GetBound();
	
	OrokuState::StateName FatGuard::getState();
protected:
	void changeAnimation(OrokuState::StateName state);
};