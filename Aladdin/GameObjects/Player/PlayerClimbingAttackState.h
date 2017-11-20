#include "Player.h"
#include "PlayerState.h"

class PlayerClimbingAttackState: public PlayerState
{
public:
	PlayerClimbingAttackState(PlayerData *playerData);
	~PlayerClimbingAttackState();

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual PlayerState::StateName GetState();
protected:
};