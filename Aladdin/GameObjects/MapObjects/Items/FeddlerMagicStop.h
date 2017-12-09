#pragma once
#include "../MapObject.h"

class FeddlerMagicStop : public MapObject
{
public:
	FeddlerMagicStop(D3DXVECTOR3 position);
	FeddlerMagicStop();
	~FeddlerMagicStop();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};