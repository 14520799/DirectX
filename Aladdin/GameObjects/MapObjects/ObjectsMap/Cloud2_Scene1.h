#pragma once
#include "../MapObject.h"

class Cloud2_Scene1 : public MapObject
{
public:
	Cloud2_Scene1(D3DXVECTOR3 position);
	Cloud2_Scene1();
	~Cloud2_Scene1();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};