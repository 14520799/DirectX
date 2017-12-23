#pragma once
#include "../MapObject.h"

class JasMine : public MapObject
{
public:
	JasMine(D3DXVECTOR3 position);
	JasMine();
	~JasMine();

	virtual const char* FileName();
	virtual int TotalFrame();
	virtual int Row();
	virtual int Column();
	virtual float SecondPerFrame();
};