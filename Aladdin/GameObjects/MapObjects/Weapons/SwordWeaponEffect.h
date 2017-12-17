#pragma once
#include "../MapObject.h"
class SwordWeaponEffect : public MapObject
{
public:
	~SwordWeaponEffect();

	SwordWeaponEffect(D3DXVECTOR3 position);

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};