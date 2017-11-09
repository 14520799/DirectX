#include "AppleEffect.h"

AppleEffect::AppleEffect(D3DXVECTOR3 position)
{
	timeDelayAppleEffect = 0;
	init(position);
}

AppleEffect::~AppleEffect()
{
}


const char * AppleEffect::FileName()
{
	return "Resources/Aladdin/AppleEffect.png";
}

int AppleEffect::TotalFrame()
{
	return 5;
}

int AppleEffect::Row()
{
	return 1;
}

int AppleEffect::Column()
{
	return 5;
}

float AppleEffect::SecondPerFrame()
{
	return 0.04f;
}