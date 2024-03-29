#include "RevitalizationDefault.h"

RevitalizationDefault::RevitalizationDefault(D3DXVECTOR3 position)
{
	init(position);
	this->Tag = Entity::EntityTypes::Item;
	this->Id = Entity::EntityId::Revitalization_Default;
}

RevitalizationDefault::RevitalizationDefault()
{
	init(D3DXVECTOR3(0, 0, 0));
}

RevitalizationDefault::~RevitalizationDefault()
{

}

const char * RevitalizationDefault::FileName()
{
	return "Resources/MapObjects/Items/RevitalizationDefault.png";
}

int RevitalizationDefault::TotalFrame()
{
	return 1;
}

int RevitalizationDefault::Row()
{
	return 1;
}

int RevitalizationDefault::Column()
{
	return 1;
}

float RevitalizationDefault::SecondPerFrame()
{
	return 0.0f;
}

void RevitalizationDefault::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (impactor->Tag == Entity::EntityTypes::Aladdin)
	{
		this->collisionWithPlayer = true;
	}
}