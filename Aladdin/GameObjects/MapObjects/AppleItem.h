#pragma once
#include "Item.h"

class AppleItem : public Item
{
public:
	AppleItem(D3DXVECTOR3 position);
	~AppleItem();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};