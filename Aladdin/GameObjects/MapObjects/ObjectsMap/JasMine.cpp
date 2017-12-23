#include "JasMine.h"
#include "../../../GameDefines/GameDefine.h"

JasMine::JasMine(D3DXVECTOR3 position)
{
	init(position);
	this->Tag = Entity::EntityTypes::JasMine;
}

JasMine::JasMine()
{
	init(D3DXVECTOR3(0, 0, 0));
}

JasMine::~JasMine()
{

}

const char * JasMine::FileName()
{
	return "Resources/MapObjects/ObjectsMap/JasMine.png";
}

int JasMine::TotalFrame()
{
	return 1;
}

int JasMine::Row()
{
	return 1;
}

int JasMine::Column()
{
	return 1;
}

float JasMine::SecondPerFrame()
{
	return 0.0f;
}