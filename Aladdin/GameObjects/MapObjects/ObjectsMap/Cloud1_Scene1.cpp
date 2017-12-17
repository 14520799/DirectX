#include "Cloud1_Scene1.h"
#include "../../../GameDefines/GameDefine.h"

Cloud1_Scene1::Cloud1_Scene1(D3DXVECTOR3 position)
{
	init(position);
}

Cloud1_Scene1::Cloud1_Scene1()
{
	init(D3DXVECTOR3(0, 0, 0));
}

Cloud1_Scene1::~Cloud1_Scene1()
{

}

const char * Cloud1_Scene1::FileName()
{
	return "Resources/MapObjects/ObjectsMap/Cloud1_Scene1.png";
}

int Cloud1_Scene1::TotalFrame()
{
	return 1;
}

int Cloud1_Scene1::Row()
{
	return 1;
}

int Cloud1_Scene1::Column()
{
	return 1;
}

float Cloud1_Scene1::SecondPerFrame()
{
	return 0.0f;
}