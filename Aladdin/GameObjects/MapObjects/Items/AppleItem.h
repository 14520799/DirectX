#pragma once
#include "../MapObject.h"

class AppleItem : public MapObject
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