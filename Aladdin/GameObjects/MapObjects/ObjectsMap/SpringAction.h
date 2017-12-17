#pragma once
#include "../MapObject.h"

class SpringAction : public MapObject
{
public:
	SpringAction(D3DXVECTOR3 position);
	SpringAction();
	~SpringAction();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};