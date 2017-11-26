#include "AppleItem.h"

AppleItem::AppleItem(D3DXVECTOR3 position)
{
	init(position);
}

AppleItem::~AppleItem()
{

}

const char * AppleItem::FileName()
{
	return "Resources/Aladdin/Apple/AppleItem.png";
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