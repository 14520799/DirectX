#pragma once
#include "Item.h"
class PotWeapon : public Item
{
public:
	~PotWeapon();

	PotWeapon(D3DXVECTOR3 position);

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
};
