#include "ThinGuard.h"

ThinGuard::ThinGuard(D3DXVECTOR3 position)
{
    init(position);
}

ThinGuard::~ThinGuard()
{
	if (mAnimation)
	{
		delete mAnimation;
		mAnimation = nullptr;
	}
}

const char * ThinGuard::FileName()
{
    return "Resources/Boss/ThinGuard.png";
}

int ThinGuard::TotalFrame()
{
    return 6;
}

int ThinGuard::Row()
{
    return 1;
}

int ThinGuard::Column()
{
    return 6;
}

float ThinGuard::SecondPerFrame()
{
    return 0.001f;
}
