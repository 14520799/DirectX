#pragma once
#include "../MapObject.h"

class FeddlerStanding : public MapObject
{
public:
	FeddlerStanding(D3DXVECTOR3 position);
	FeddlerStanding();
	~FeddlerStanding();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
};