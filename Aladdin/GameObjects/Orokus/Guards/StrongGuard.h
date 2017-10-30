#pragma once
#include "../../../GameComponents/Animation.h"
#include "../Oroku.h"
#include "../OrokuData.h"
#include "../OrokuState.h"

class StrongGuard : public Oroku
{
public:
	StrongGuard(D3DXVECTOR3 position);
	~StrongGuard();

	void Update(float dt);

	void Draw(D3DXVECTOR2 trans);

	void SetState(OrokuState *newState);

	void SetReverse(bool flag);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	RECT GetBound();

	OrokuState::StateName StrongGuard::getState();
protected:
	void changeAnimation(OrokuState::StateName state);
};