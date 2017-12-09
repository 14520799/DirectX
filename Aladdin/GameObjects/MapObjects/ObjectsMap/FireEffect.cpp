#include "FireEffect.h"

FireEffect::FireEffect(D3DXVECTOR3 position)
{
	init(position);
	this->Id = Entity::EntityId::FireEffect;
}

FireEffect::~FireEffect()
{

}

const char * FireEffect::FileName()
{
	return "Resources/MapObjects/ObjectsMap/FireEffect.png";
}

int FireEffect::TotalFrame()
{
	return 5;
}

int FireEffect::Row()
{
	return 1;
}

int FireEffect::Column()
{
	return 5;
}

float FireEffect::SecondPerFrame()
{
	return 0.1f;
}