#pragma once
#include "Boss.h"

class FatGuard : public Boss
{
public:
	FatGuard(D3DXVECTOR3 position);
    ~FatGuard();

    virtual const char* FileName();
    virtual int TotalFrame();
    virtual int Row();
    virtual int Column();
    virtual float SecondPerFrame();
};