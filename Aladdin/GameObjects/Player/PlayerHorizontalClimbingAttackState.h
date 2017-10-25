#include "Player.h"
#include "PlayerState.h"

class PlayerHorizontalClimbingAttackState: public PlayerState
{
public:
	PlayerHorizontalClimbingAttackState(PlayerData *playerData);
	~PlayerHorizontalClimbingAttackState();

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual PlayerState::StateName GetState();
protected:
};