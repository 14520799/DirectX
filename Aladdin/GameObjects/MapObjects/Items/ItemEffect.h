#pragma once
#include "../MapObject.h"

class ItemEffect : public MapObject
{
public:
	ItemEffect(D3DXVECTOR3 position);
	~ItemEffect();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};