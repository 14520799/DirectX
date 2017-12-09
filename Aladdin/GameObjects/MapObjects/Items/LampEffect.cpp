#include "LampEffect.h"

LampEffect::LampEffect(D3DXVECTOR3 position)
{
	init(position);
}

LampEffect::LampEffect()
{
	init(D3DXVECTOR3(0, 0, 0));
}

LampEffect::~LampEffect()
{

}

const char * LampEffect::FileName()
{
	return "Resources/MapObjects/Items/LampEffect.png";
}

int LampEffect::TotalFrame()
{
	return 14;
}

int LampEffect::Row()
{
	return 1;
}

int LampEffect::Column()
{
	return 14;
}

float LampEffect::SecondPerFrame()
{
	return 0.14f;
}