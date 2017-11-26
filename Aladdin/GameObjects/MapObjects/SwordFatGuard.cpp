#include "SwordFatGuard.h"

SwordFatGuard::SwordFatGuard(D3DXVECTOR3 position)
{
    init(position);
}

SwordFatGuard::~SwordFatGuard()
{
}


const char * SwordFatGuard::FileName()
{
    return "Resources/Orokus/Guards/Sword.png";
}

int SwordFatGuard::TotalFrame()
{
    return 7;
}

int SwordFatGuard::Row()
{
    return 1;
}

int SwordFatGuard::Column()
{
    return 7;
}

float SwordFatGuard::SecondPerFrame()
{
    return 0.05f;
}

void SwordFatGuard::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (impactor->Tag == Entity::EntityTypes::Aladdin)
	{
		this->collisionWithPlayer = true;
	}
	else if (impactor->Tag != Entity::EntityTypes::Guard && impactor->Tag != Entity::EntityTypes::AppleItem)
	{
		this->weaponCollided = true;
	}
}