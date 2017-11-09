#pragma once
#include "Item.h"
class AppleEffect : public Item
{
public:
	~AppleEffect();

	AppleEffect(D3DXVECTOR3 position);

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};
