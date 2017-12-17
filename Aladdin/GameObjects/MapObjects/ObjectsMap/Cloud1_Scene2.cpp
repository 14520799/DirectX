#include "Cloud1_Scene2.h"
#include "../../../GameDefines/GameDefine.h"

Cloud1_Scene2::Cloud1_Scene2(D3DXVECTOR3 position)
{
	init(position);
}

Cloud1_Scene2::Cloud1_Scene2()
{
	init(D3DXVECTOR3(0, 0, 0));
}

Cloud1_Scene2::~Cloud1_Scene2()
{

}

const char * Cloud1_Scene2::FileName()
{
	return "Resources/MapObjects/ObjectsMap/Cloud1_Scene2.png";
}

int Cloud1_Scene2::TotalFrame()
{
	return 1;
}

int Cloud1_Scene2::Row()
{
	return 1;
}

int Cloud1_Scene2::Column()
{
	return 1;
}

float Cloud1_Scene2::SecondPerFrame()
{
	return 0.0f;
}