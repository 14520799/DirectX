#pragma once
#include "../../../GameComponents/Animation.h"
#include "../Oroku.h"
#include "../OrokuData.h"
#include "../OrokuState.h"

class CivilianCircus : public Oroku
{
public:
	CivilianCircus(D3DXVECTOR3 position);
	~CivilianCircus();

	void Update(float dt);

	void Draw(D3DXVECTOR2 trans);

	void SetState(OrokuState *newState);

	void SetReverse(bool flag);

	void SetPlayer(Player *player);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	RECT GetBound();

	OrokuState::StateName CivilianCircus::getState();

protected:
	void changeAnimation(OrokuState::StateName state);
};