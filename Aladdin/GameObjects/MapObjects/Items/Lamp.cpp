#include "Lamp.h"

Lamp::Lamp(D3DXVECTOR3 position)
{
	init(position);
	this->Tag = Entity::EntityTypes::Item;
	this->Id = Entity::EntityId::Lamp;
}

Lamp::Lamp()
{
	init(D3DXVECTOR3(0, 0, 0));
}

Lamp::~Lamp()
{

}

const char * Lamp::FileName()
{
	return "Resources/MapObjects/Items/Lamp.png";
}

int Lamp::TotalFrame()
{
	return 1;
}

int Lamp::Row()
{
	return 1;
}

int Lamp::Column()
{
	return 1;
}

float Lamp::SecondPerFrame()
{
	return 0.0f;
}