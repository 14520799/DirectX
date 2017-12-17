#pragma once
#include "../MapObject.h"

class Cloud1_Scene1 : public MapObject
{
public:
	Cloud1_Scene1(D3DXVECTOR3 position);
	Cloud1_Scene1();
	~Cloud1_Scene1();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};