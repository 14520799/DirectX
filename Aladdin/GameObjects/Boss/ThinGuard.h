#pragma once
#include "Boss.h"

class ThinGuard : public Boss
{
public:
	ThinGuard(D3DXVECTOR3 position);
    ~ThinGuard();

    virtual const char* FileName();
    virtual int TotalFrame();
    virtual int Row();
    virtual int Column();
    virtual float SecondPerFrame();
};