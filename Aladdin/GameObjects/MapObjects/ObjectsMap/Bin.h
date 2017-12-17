#pragma once
#include "../MapObject.h"

class Bin : public MapObject
{
public:
	Bin(D3DXVECTOR3 position);
	Bin();
	~Bin();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};