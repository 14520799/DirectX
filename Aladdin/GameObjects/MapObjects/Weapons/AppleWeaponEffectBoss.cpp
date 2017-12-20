#include "AppleWeaponEffectBoss.h"

AppleWeaponEffectBoss::AppleWeaponEffectBoss(D3DXVECTOR3 position)
{
	timeDelayWeaponEffect = 0;
	init(position);
}

AppleWeaponEffectBoss::~AppleWeaponEffectBoss()
{
}


const char * AppleWeaponEffectBoss::FileName()
{
	return "Resources/MapObjects/Weapons/AppleWeaponEffectBoss.png";
}

int AppleWeaponEffectBoss::TotalFrame()
{
	return 8;
}

int AppleWeaponEffectBoss::Row()
{
	return 1;
}

int AppleWeaponEffectBoss::Column()
{
	return 8;
}

float AppleWeaponEffectBoss::SecondPerFrame()
{
	return 0.06f;
}