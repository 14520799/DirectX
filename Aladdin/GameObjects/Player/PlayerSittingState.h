#include "PlayerState.h"
#include "Player.h"

class PlayerSittingState : public PlayerState
{
public:
	PlayerSittingState(PlayerData *playerData);
	~PlayerSittingState();

	void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
};