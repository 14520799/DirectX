#include "Player.h"
#include "PlayerState.h"

class PlayerStandingAttackState : public PlayerState
{
public:
	PlayerStandingAttackState(PlayerData *playerData);
	~PlayerStandingAttackState();

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual PlayerState::StateName GetState();
protected:
};