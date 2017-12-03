#pragma once
#include "../MapObject.h"

class LampEffect : public MapObject
{
public:
	LampEffect(D3DXVECTOR3 position);
	LampEffect();
	~LampEffect();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};