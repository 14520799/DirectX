#pragma once
#include "../../../GameComponents/Animation.h"
#include "../Oroku.h"
#include "../OrokuData.h"
#include "../OrokuState.h"

class CivilianWindow : public Oroku
{
public:
	CivilianWindow(D3DXVECTOR3 position);
	~CivilianWindow();

	void Update(float dt);

	void Draw(D3DXVECTOR2 trans);

	void SetState(OrokuState *newState);

	void SetReverse(bool flag);

	void SetPlayer(Player *player);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	RECT GetBound();

	OrokuState::StateName CivilianWindow::getState();

	float timeDelayDefaultState;
protected:
	void changeAnimation(OrokuState::StateName state);
};