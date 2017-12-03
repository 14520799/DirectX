#pragma once
#include "../MapObject.h"

class Heart : public MapObject
{
public:
	Heart(D3DXVECTOR3 position);
	~Heart();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};