#pragma once
#include "../MapObject.h"

class StarWeaponEffect : public MapObject
{
public:
	StarWeaponEffect(D3DXVECTOR3 position);
	~StarWeaponEffect();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};