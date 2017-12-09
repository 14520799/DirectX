#pragma once
#include "../MapObject.h"

class Spring : public MapObject
{
public:
	Spring(D3DXVECTOR3 position);
	Spring();
	~Spring();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};