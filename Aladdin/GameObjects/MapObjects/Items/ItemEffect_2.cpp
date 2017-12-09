#include "ItemEffect_2.h"

ItemEffect_2::ItemEffect_2(D3DXVECTOR3 position)
{
	init(position);
	this->Id = Entity::EntityId::ItemEffect_2;
}

ItemEffect_2::~ItemEffect_2()
{

}

const char * ItemEffect_2::FileName()
{
	return "Resources/MapObjects/Items/ItemEffect_2.png";
}

int ItemEffect_2::TotalFrame()
{
	return 10;
}

int ItemEffect_2::Row()
{
	return 1;
}

int ItemEffect_2::Column()
{
	return 10;
}

float ItemEffect_2::SecondPerFrame()
{
	return 0.2f;
}