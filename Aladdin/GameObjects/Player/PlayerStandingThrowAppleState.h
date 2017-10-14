#include "Player.h"
#include "PlayerState.h"

class PlayerStandingThrowAppleState : public PlayerState
{
public:
	PlayerStandingThrowAppleState(PlayerData *playerData);
	~PlayerStandingThrowAppleState();

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual PlayerState::StateName GetState();
protected:

};