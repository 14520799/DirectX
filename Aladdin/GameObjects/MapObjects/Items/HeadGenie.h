#pragma once
#include "../MapObject.h"

class HeadGenie : public MapObject
{
public:
	HeadGenie(D3DXVECTOR3 position);
	~HeadGenie();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};