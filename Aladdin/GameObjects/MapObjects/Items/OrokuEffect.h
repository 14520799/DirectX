#pragma once
#include "../MapObject.h"

class OrokuEffect : public MapObject
{
public:
	OrokuEffect(D3DXVECTOR3 position);
	~OrokuEffect();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};