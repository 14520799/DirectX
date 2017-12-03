#pragma once
#include "../MapObject.h"

class RevitalizationDefault : public MapObject
{
public:
	RevitalizationDefault(D3DXVECTOR3 position);
	RevitalizationDefault();
	~RevitalizationDefault();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
};