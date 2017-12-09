#pragma once
#include "../MapObject.h"

class ItemEffect_1 : public MapObject
{
public:
	ItemEffect_1(D3DXVECTOR3 position);
	~ItemEffect_1();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};