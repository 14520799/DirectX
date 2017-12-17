#include "Cloud2_Scene2.h"
#include "../../../GameDefines/GameDefine.h"

Cloud2_Scene2::Cloud2_Scene2(D3DXVECTOR3 position)
{
	init(position);
}

Cloud2_Scene2::Cloud2_Scene2()
{
	init(D3DXVECTOR3(0, 0, 0));
}

Cloud2_Scene2::~Cloud2_Scene2()
{

}

const char * Cloud2_Scene2::FileName()
{
	return "Resources/MapObjects/ObjectsMap/Cloud2_Scene2.png";
}

int Cloud2_Scene2::TotalFrame()
{
	return 1;
}

int Cloud2_Scene2::Row()
{
	return 1;
}

int Cloud2_Scene2::Column()
{
	return 1;
}

float Cloud2_Scene2::SecondPerFrame()
{
	return 0.0f;
}