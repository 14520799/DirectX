#include "Player.h"
#include "PlayerState.h"

class PlayerSittingAttackState : public PlayerState
{
public:
	PlayerSittingAttackState(PlayerData *playerData);
	~PlayerSittingAttackState();

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual PlayerState::StateName GetState();
protected:
};