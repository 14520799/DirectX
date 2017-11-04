#include "Oroku.h"

Oroku::Oroku()
{

}

Oroku::~Oroku()
{

}

void Oroku::Update(float dt)
{

}

void Oroku::SetReverse(bool flag)
{

}

void Oroku::SetState(OrokuState *newState)
{

}

void Oroku::Draw(D3DXVECTOR2 trans)
{

}

void Oroku::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{

}

void Oroku::changeAnimation(OrokuState::StateName state)
{
	
}

void Oroku::SetPlayer(Player *player)
{
	this->mPlayer = player;
}

void Oroku::OnNoCollisionWithBottom()
{

}

