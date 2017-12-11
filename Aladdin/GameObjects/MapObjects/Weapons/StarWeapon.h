#pragma once
#include "../MapObject.h"

class StarWeapon : public MapObject
{
public:
	StarWeapon(D3DXVECTOR3 position);
	StarWeapon();
	~StarWeapon();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
};