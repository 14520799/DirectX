#pragma once
#include "../MapObject.h"

class Stairs : public MapObject
{
public:
	Stairs(D3DXVECTOR3 position);
	Stairs();
	~Stairs();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
};