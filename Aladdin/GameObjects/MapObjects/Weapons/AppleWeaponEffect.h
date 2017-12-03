#pragma once
#include "../MapObject.h"
class AppleWeaponEffect : public MapObject
{
public:
	~AppleWeaponEffect();

	AppleWeaponEffect(D3DXVECTOR3 position);

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};
