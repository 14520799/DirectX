#pragma once
#include "../MapObject.h"

class Lamp : public MapObject
{
public:
	Lamp(D3DXVECTOR3 position);
	Lamp();
	~Lamp();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};