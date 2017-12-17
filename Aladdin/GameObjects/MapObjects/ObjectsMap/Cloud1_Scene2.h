#pragma once
#include "../MapObject.h"

class Cloud1_Scene2 : public MapObject
{
public:
	Cloud1_Scene2(D3DXVECTOR3 position);
	Cloud1_Scene2();
	~Cloud1_Scene2();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};