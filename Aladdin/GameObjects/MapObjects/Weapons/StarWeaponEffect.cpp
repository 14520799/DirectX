#include "StarWeaponEffect.h"

StarWeaponEffect::StarWeaponEffect(D3DXVECTOR3 position)
{
	init(position);
	this->Id = Entity::EntityId::StarEffect;
}

StarWeaponEffect::~StarWeaponEffect()
{

}

const char * StarWeaponEffect::FileName()
{
	return "Resources/MapObjects/Weapons/StarWeaponEffect.png";
}

int StarWeaponEffect::TotalFrame()
{
	return 4;
}

int StarWeaponEffect::Row()
{
	return 1;
}

int StarWeaponEffect::Column()
{
	return 4;
}

float StarWeaponEffect::SecondPerFrame()
{
	return 0.025f;
}