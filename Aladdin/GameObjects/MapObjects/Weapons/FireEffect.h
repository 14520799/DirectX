#pragma once
#include "../MapObject.h"

class FireEffect : public MapObject
{
public:
	FireEffect(D3DXVECTOR3 position);
	~FireEffect();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};