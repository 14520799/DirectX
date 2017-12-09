#pragma once
#include "../MapObject.h"

class ItemEffect_2 : public MapObject
{
public:
	ItemEffect_2(D3DXVECTOR3 position);
	~ItemEffect_2();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};