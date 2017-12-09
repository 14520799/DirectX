#pragma once
#include "../MapObject.h"

class Ruby : public MapObject
{
public:
	Ruby(D3DXVECTOR3 position);
	~Ruby();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};