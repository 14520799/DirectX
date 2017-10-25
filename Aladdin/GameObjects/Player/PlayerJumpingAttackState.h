#include "Player.h"
#include "PlayerState.h"

class PlayerJumpingAttackState : public PlayerState
{
public:
	PlayerJumpingAttackState(PlayerData *playerData);
	~PlayerJumpingAttackState();

	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual PlayerState::StateName GetState();
protected:
	bool noPressed;
	bool allowMoveRight, allowMoveLeft;
};