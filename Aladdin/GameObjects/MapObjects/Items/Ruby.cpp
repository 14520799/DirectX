#include "Ruby.h"

Ruby::Ruby(D3DXVECTOR3 position)
{
	init(position);
	this->Tag = Entity::EntityTypes::Item;
	this->Id = Entity::EntityId::Ruby;
}

Ruby::~Ruby()
{

}

const char * Ruby::FileName()
{
	return "Resources/MapObjects/Items/Ruby.png";
}

int Ruby::TotalFrame()
{
	return 9;
}

int Ruby::Row()
{
	return 1;
}

int Ruby::Column()
{
	return 9;
}

float Ruby::SecondPerFrame()
{
	return 0.05f;
}