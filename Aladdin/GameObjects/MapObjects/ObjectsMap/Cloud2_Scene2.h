#pragma once
#include "../MapObject.h"

class Cloud2_Scene2 : public MapObject
{
public:
	Cloud2_Scene2(D3DXVECTOR3 position);
	Cloud2_Scene2();
	~Cloud2_Scene2();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};