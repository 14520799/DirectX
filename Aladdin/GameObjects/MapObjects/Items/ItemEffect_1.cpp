#include "ItemEffect_1.h"

ItemEffect_1::ItemEffect_1(D3DXVECTOR3 position)
{
	init(position);
	this->Id = Entity::EntityId::ItemEffect_1;
}

ItemEffect_1::~ItemEffect_1()
{

}

const char * ItemEffect_1::FileName()
{
	return "Resources/MapObjects/Items/ItemEffect_1.png";
}

int ItemEffect_1::TotalFrame()
{
	return 2;
}

int ItemEffect_1::Row()
{
	return 1;
}

int ItemEffect_1::Column()
{
	return 2;
}

float ItemEffect_1::SecondPerFrame()
{
	return 0.2f;
}