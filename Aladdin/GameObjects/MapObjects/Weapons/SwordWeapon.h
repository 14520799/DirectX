#pragma once
#include "../MapObject.h"
class SwordWeapon : public MapObject
{
public:
    ~SwordWeapon();

	SwordWeapon(D3DXVECTOR3 position);

    virtual const char* FileName();
    virtual int TotalFrame();
    virtual int Row();
    virtual int Column();
    virtual float SecondPerFrame();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
};

