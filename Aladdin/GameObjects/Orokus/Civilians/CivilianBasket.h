#pragma once
#include "../../../GameComponents/Animation.h"
#include "../Oroku.h"
#include "../OrokuData.h"
#include "../OrokuState.h"

class CivilianBasket : public Oroku
{
public:
	CivilianBasket(D3DXVECTOR3 position);
	~CivilianBasket();

	void Update(float dt);

	void Draw(D3DXVECTOR2 trans);

	void SetState(OrokuState *newState);

	void SetReverse(bool flag);

	void SetPlayer(Player *player);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	RECT GetBound();

	OrokuState::StateName CivilianBasket::getState();
protected:
	void changeAnimation(OrokuState::StateName state);
};