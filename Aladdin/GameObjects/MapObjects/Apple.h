#pragma once
#include "Brick.h"

class Apple : public Brick
{
public:
	Apple(D3DXVECTOR3 position);
    ~Apple();

    virtual const char* FileName();
    virtual int TotalFrame();
    virtual int Row();
    virtual int Column();
    virtual float SecondPerFrame();
};