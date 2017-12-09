#include "OrokuEffect.h"

OrokuEffect::OrokuEffect(D3DXVECTOR3 position)
{
	init(position);
	this->Id = Entity::EntityId::OrokuEffect;
}

OrokuEffect::~OrokuEffect()
{

}

const char * OrokuEffect::FileName()
{
	return "Resources/MapObjects/Items/OrokuEffect.png";
}

int OrokuEffect::TotalFrame()
{
	return 6;
}

int OrokuEffect::Row()
{
	return 1;
}

int OrokuEffect::Column()
{
	return 6;
}

float OrokuEffect::SecondPerFrame()
{
	return 0.07f;
}