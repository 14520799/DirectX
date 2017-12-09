#include "PotWeaponEffect.h"

PotWeaponEffect::PotWeaponEffect(D3DXVECTOR3 position)
{
	timeDelayWeaponEffect = 0;
	init(position);
}

PotWeaponEffect::~PotWeaponEffect()
{

}

const char * PotWeaponEffect::FileName()
{
	return "Resources/MapObjects/Weapons/PotWeaponEffect.png";
}

int PotWeaponEffect::TotalFrame()
{
	return 8;
}

int PotWeaponEffect::Row()
{
	return 1;
}

int PotWeaponEffect::Column()
{
	return 8;
}

float PotWeaponEffect::SecondPerFrame()
{
	return 0.01f;
}