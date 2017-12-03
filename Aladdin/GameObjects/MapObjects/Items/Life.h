#pragma once
#include "../MapObject.h"

class Life : public MapObject
{
public:
	Life(D3DXVECTOR3 position);
	~Life();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};