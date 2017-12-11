#pragma once
#include "../../../GameComponents/Animation.h"
#include "../../MapObjects/MapObject.h"
#include "../Oroku.h"
#include "../OrokuData.h"
#include "../OrokuState.h"

class Jafar : public Oroku
{
public:
	Jafar(D3DXVECTOR3 position);
	~Jafar();

	void Update(float dt);

	void Draw(D3DXVECTOR2 trans);

	void SetState(OrokuState *newState);

	void SetReverse(bool flag);

	void SetPlayer(Player *player);

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	RECT GetBound();

	OrokuState::StateName Jafar::getState();

	std::vector<MapObject*> GetListWeapon();

	float timeDelayTransfigureEffect;

	MapObject *weapon;
	MapObject *weaponEffect;
	MapObject *TransfigureEffect;
protected:
	void changeAnimation(OrokuState::StateName state);
};