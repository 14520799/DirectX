#include "HeadGenie.h"

HeadGenie::HeadGenie(D3DXVECTOR3 position)
{
	init(position);
	this->Tag = Entity::EntityTypes::Item;
	this->Id = Entity::EntityId::HeadGenie;
}

HeadGenie::~HeadGenie()
{

}

const char * HeadGenie::FileName()
{
	return "Resources/MapObjects/Items/HeadGenie.png";
}

int HeadGenie::TotalFrame()
{
	return 4;
}

int HeadGenie::Row()
{
	return 1;
}

int HeadGenie::Column()
{
	return 4;
}

float HeadGenie::SecondPerFrame()
{
	return 0.2f;
}