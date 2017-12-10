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

	void SetPlayer(Player *player);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	RECT GetBound();

	OrokuState::StateName StrongGuard::getState();

	bool runningFire;
	bool allowRun;
protected:
	Animation *mAnimationHurting;

	void changeAnimation(OrokuState::StateName state);
	//time delay de oroku ra khoi dong lua hoan toan vi khi chay ra khoi lua thi se chuyen sang state running
	//khi do no van chua ra khoi lua hoan toan va lai cham vao lua chuyen sang state runFire
	//vi the ta can keo dai time ra them 1 chut de oroku ra khoi lua hoan toan 
	float timeDelay;
};