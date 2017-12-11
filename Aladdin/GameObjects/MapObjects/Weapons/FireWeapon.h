#pragma once
#include "../MapObject.h"

class FireWeapon : public MapObject
{
public:
	FireWeapon(D3DXVECTOR3 position);
	FireWeapon();
	~FireWeapon();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
};