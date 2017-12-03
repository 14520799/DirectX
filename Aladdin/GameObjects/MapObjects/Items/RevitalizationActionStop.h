#pragma once
#include "../MapObject.h"

class RevitalizationActionStop : public MapObject
{
public:
	RevitalizationActionStop(D3DXVECTOR3 position);
	RevitalizationActionStop();
	~RevitalizationActionStop();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};