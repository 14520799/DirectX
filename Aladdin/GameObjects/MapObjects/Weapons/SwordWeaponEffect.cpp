#include "SwordWeaponEffect.h"

SwordWeaponEffect::SwordWeaponEffect(D3DXVECTOR3 position)
{
	timeDelayWeaponEffect = 0;
	init(position);
}

SwordWeaponEffect::~SwordWeaponEffect()
{
}


const char * SwordWeaponEffect::FileName()
{
	return "Resources/MapObjects/Weapons/SwordWeaponEffect.png";
}

int SwordWeaponEffect::TotalFrame()
{
	return 2;
}

int SwordWeaponEffect::Row()
{
	return 1;
}

int SwordWeaponEffect::Column()
{
	return 2;
}

float SwordWeaponEffect::SecondPerFrame()
{
	return 0.2f;
}