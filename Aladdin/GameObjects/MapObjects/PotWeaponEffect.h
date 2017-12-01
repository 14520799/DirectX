#pragma once
#include "Item.h"
class PotWeaponEffect : public Item
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