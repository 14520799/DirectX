#include "PlayerState.h"
#include "Player.h"

class PlayerMoveMoonState : public PlayerState
{
public:
	PlayerMoveMoonState(PlayerData *playerData);
	~PlayerMoveMoonState();

	void Update(float dt);

	virtual PlayerState::StateName GetState();
protected:
	float timeDelay;
};