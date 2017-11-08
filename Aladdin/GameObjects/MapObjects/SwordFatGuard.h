#pragma once
#include "Brick.h"
class SwordFatGuard : public Brick
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

