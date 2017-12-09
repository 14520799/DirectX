#pragma once
#include "../MapObject.h"

class FeddlerMagic : public MapObject
{
public:
	FeddlerMagic(D3DXVECTOR3 position);
	FeddlerMagic();
	~FeddlerMagic();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};