#include "AppleWeaponEffect.h"

AppleWeaponEffect::AppleWeaponEffect(D3DXVECTOR3 position)
{
	timeDelayWeaponEffect = 0;
	init(position);
}

AppleWeaponEffect::~AppleWeaponEffect()
{
}


const char * AppleWeaponEffect::FileName()
{
	return "Resources/Items/Apple/AppleWeaponEffect.png";
}

int AppleWeaponEffect::TotalFrame()
{
	return 5;
}

int AppleWeaponEffect::Row()
{
	return 1;
}

int AppleWeaponEffect::Column()
{
	return 5;
}

float AppleWeaponEffect::SecondPerFrame()
{
	return 0.04f;
}