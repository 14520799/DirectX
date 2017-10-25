#include "Player.h"
#include "PlayerState.h"

class PlayerJumpingThrowAppleState : public PlayerState
{
public:
	PlayerJumpingThrowAppleState(PlayerData *playerData);
	~PlayerJumpingThrowAppleState();

	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual PlayerState::StateName GetState();
protected:
	bool noPressed;
	bool allowMoveRight, allowMoveLeft;
};