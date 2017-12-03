#pragma once
#include "../MapObject.h"

class AppleWeapon : public MapObject
{
public:
	AppleWeapon(D3DXVECTOR3 position);
	AppleWeapon();
    ~AppleWeapon();

    virtual const char* FileName();
    virtual int TotalFrame();
    virtual int Row();
    virtual int Column();
    virtual float SecondPerFrame();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
};