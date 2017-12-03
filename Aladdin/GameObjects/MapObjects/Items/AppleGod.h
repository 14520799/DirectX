#pragma once
#include "../MapObject.h"

class AppleGod : public MapObject
{
public:
	AppleGod(D3DXVECTOR3 position);
	~AppleGod();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};