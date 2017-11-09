#pragma once
#include "Item.h"
class SwordFatGuard : public Item
{
public:
    ~SwordFatGuard();

	SwordFatGuard(D3DXVECTOR3 position);

    virtual const char* FileName();
    virtual int TotalFrame();
    virtual int Row();
    virtual int Column();
    virtual float SecondPerFrame();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
};

