#include "FeddlerStanding.h"

FeddlerStanding::FeddlerStanding(D3DXVECTOR3 position)
{
	init(position);
	this->Tag = Entity::EntityTypes::Item;
	this->Id = Entity::EntityId::Feddler_Standing;
}

FeddlerStanding::FeddlerStanding()
{
	init(D3DXVECTOR3(0, 0, 0));
}

FeddlerStanding::~FeddlerStanding()
{

}

const char * FeddlerStanding::FileName()
{
	return "Resources/MapObjects/Items/FeddlerStanding.png";
}

int FeddlerStanding::TotalFrame()
{
	return 7;
}

int FeddlerStanding::Row()
{
	return 1;
}

int FeddlerStanding::Column()
{
	return 7;
}

float FeddlerStanding::SecondPerFrame()
{
	return 0.2f;
}

void FeddlerStanding::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (impactor->Tag == Entity::EntityTypes::Aladdin)
	{
		this->collisionWithPlayer = true;
	}
}