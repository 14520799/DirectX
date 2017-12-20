#include "PlayerState.h"
#include "Player.h"

class PlayerScene18PlusStopState : public PlayerState
{
public:
	PlayerScene18PlusStopState(PlayerData *playerData);
	~PlayerScene18PlusStopState();

	void Update(float dt);

	virtual PlayerState::StateName GetState();
protected:
	float timeDelay;
};