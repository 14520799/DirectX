#include "Bin.h"
#include "../../../GameDefines/GameDefine.h"

Bin::Bin(D3DXVECTOR3 position)
{
	init(position);
	this->Tag = Entity::EntityTypes::Bin;
}

Bin::Bin()
{
	init(D3DXVECTOR3(0, 0, 0));
}

Bin::~Bin()
{

}

const char * Bin::FileName()
{
	return "Resources/MapObjects/ObjectsMap/Bin.png";
}

int Bin::TotalFrame()
{
	return 1;
}

int Bin::Row()
{
	return 1;
}

int Bin::Column()
{
	return 1;
}

float Bin::SecondPerFrame()
{
	return 0.0f;
}