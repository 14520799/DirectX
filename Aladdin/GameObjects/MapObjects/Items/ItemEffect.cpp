#include "ItemEffect.h"

ItemEffect::ItemEffect(D3DXVECTOR3 position)
{
	init(position);
}

ItemEffect::~ItemEffect()
{

}

const char * ItemEffect::FileName()
{
	return "Resources/Items/ItemEffect.png";
}

int ItemEffect::TotalFrame()
{
	return 2;
}

int ItemEffect::Row()
{
	return 1;
}

int ItemEffect::Column()
{
	return 2;
}

float ItemEffect::SecondPerFrame()
{
	return 0.5f;
}