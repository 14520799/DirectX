#include "PlayerState.h"
#include "Player.h"

class PlayerLevelCompleteState : public PlayerState
{
public:
	PlayerLevelCompleteState(PlayerData *playerData);
	~PlayerLevelCompleteState();

	void Update(float dt);

	virtual PlayerState::StateName GetState();
protected:
	float timeDelay;
};