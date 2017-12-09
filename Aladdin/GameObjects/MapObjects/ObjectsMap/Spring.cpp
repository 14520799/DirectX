#include "Spring.h"
#include "../../../GameDefines/GameDefine.h"

Spring::Spring(D3DXVECTOR3 position)
{
	init(position);
	this->Tag = Entity::EntityTypes::Spring;
}

Spring::Spring()
{
	init(D3DXVECTOR3(0, 0, 0));
}

Spring::~Spring()
{

}

const char * Spring::FileName()
{
	return "Resources/MapObjects/ObjectsMap/Spring.png";
}

int Spring::TotalFrame()
{
	return 1;
}

int Spring::Row()
{
	return 1;
}

int Spring::Column()
{
	return 1;
}

float Spring::SecondPerFrame()
{
	return 0.0f;
}
