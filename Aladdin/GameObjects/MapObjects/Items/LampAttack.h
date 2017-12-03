#pragma once
#include "../MapObject.h"

class LampAttack : public MapObject
{
public:
	LampAttack(D3DXVECTOR3 position);
	LampAttack();
	~LampAttack();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
};