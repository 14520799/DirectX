#include "Cloud2_Scene1.h"
#include "../../../GameDefines/GameDefine.h"

Cloud2_Scene1::Cloud2_Scene1(D3DXVECTOR3 position)
{
	init(position);
}

Cloud2_Scene1::Cloud2_Scene1()
{
	init(D3DXVECTOR3(0, 0, 0));
}

Cloud2_Scene1::~Cloud2_Scene1()
{

}

const char * Cloud2_Scene1::FileName()
{
	return "Resources/MapObjects/ObjectsMap/Cloud2_Scene1.png";
}

int Cloud2_Scene1::TotalFrame()
{
	return 1;
}

int Cloud2_Scene1::Row()
{
	return 1;
}

int Cloud2_Scene1::Column()
{
	return 1;
}

float Cloud2_Scene1::SecondPerFrame()
{
	return 0.0f;
}