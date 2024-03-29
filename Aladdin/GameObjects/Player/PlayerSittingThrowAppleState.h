#include "Player.h"
#include "PlayerState.h"

class PlayerSittingThrowAppleState : public PlayerState
{
public:
	PlayerSittingThrowAppleState(PlayerData *playerData);
	~PlayerSittingThrowAppleState();

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual PlayerState::StateName GetState();
protected:
};