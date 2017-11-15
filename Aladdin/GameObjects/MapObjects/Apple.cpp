#include "Apple.h"

Apple::Apple(D3DXVECTOR3 position)
{
    init(position);
}

Apple::~Apple()
{

}

const char * Apple::FileName()
{
    return "Resources/Aladdin/Apple/Apple.png";
}

int Apple::TotalFrame()
{
    return 1;
}

int Apple::Row()
{
    return 1;
}

int Apple::Column()
{
    return 1;
}

float Apple::SecondPerFrame()
{
    return 0.0f;
}

void Apple::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (impactor->Tag == Entity::EntityTypes::Guard)
	{
		this->collisionWithOroku = true;
	}
}
