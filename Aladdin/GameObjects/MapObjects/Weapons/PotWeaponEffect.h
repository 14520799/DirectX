#pragma once
#include "../MapObject.h"
class PotWeaponEffect : public MapObject
{
public:
	~PotWeaponEffect();

	PotWeaponEffect(D3DXVECTOR3 position);

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};