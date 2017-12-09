#include "AppleItem.h"

AppleItem::AppleItem(D3DXVECTOR3 position)
{
	init(position);
	this->Tag = Entity::EntityTypes::Item;
	this->Id = Entity::EntityId::AppleItem;
}

AppleItem::~AppleItem()
{

}

const char * AppleItem::FileName()
{
	return "Resources/MapObjects/Items/AppleItem.png";
}

int AppleItem::TotalFrame()
{
	return 1;
}

int AppleItem::Row()
{
	return 1;
}

int AppleItem::Column()
{
	return 1;
}

float AppleItem::SecondPerFrame()
{
	return 0.0f;
}