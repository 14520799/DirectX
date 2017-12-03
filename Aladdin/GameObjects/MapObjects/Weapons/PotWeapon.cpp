#include "PotWeapon.h"

PotWeapon::PotWeapon(D3DXVECTOR3 position)
{
	init(position);
}

PotWeapon::~PotWeapon()
{

}

const char * PotWeapon::FileName()
{
	return "Resources/Orokus/Civilians/PotWeaponFalling.png";
}

int PotWeapon::TotalFrame()
{
	return 6;
}

int PotWeapon::Row()
{
	return 1;
}

int PotWeapon::Column()
{
	return 6;
}

float PotWeapon::SecondPerFrame()
{
	return 0.01f;
}

void PotWeapon::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (impactor->Tag == Entity::EntityTypes::Aladdin)
	{
		this->collisionWithPlayer = true;
	}
	else if (impactor->Tag == Entity::EntityTypes::Ground)
	{
 		this->weaponCollided = true;
	}
}