#include "Player.h"
#include "PlayerState.h"

class PlayerClimbingThrowAppleState : public PlayerState
{
public:
	PlayerClimbingThrowAppleState(PlayerData *playerData);
	~PlayerClimbingThrowAppleState();

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual PlayerState::StateName GetState();
protected:
};