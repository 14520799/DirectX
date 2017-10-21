#include "FatGuard.h"

FatGuard::FatGuard(D3DXVECTOR3 position)
{
    init(position);
}

FatGuard::~FatGuard()
{
	if (mAnimation)
	{
		delete mAnimation;
		mAnimation = nullptr;
	}
}

const char * FatGuard::FileName()
{
    return "Resources/Boss/FatGuard.png";
}

int FatGuard::TotalFrame()
{
    return 5;
}

int FatGuard::Row()
{
    return 1;
}

int FatGuard::Column()
{
    return 5;
}

float FatGuard::SecondPerFrame()
{
    return 0.001f;
}
