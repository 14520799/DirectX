#pragma once
#include "../MapObject.h"

class RevitalizationAction : public MapObject
{
public:
	RevitalizationAction(D3DXVECTOR3 position);
	RevitalizationAction();
	~RevitalizationAction();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};