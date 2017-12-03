#include "PlayerDeathState.h"
#include "PlayerRunningState.h"

PlayerDeathState::PlayerDeathState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
	this->mPlayerData->player->allowImunity = true;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
	allowDelayHurting = true; //dang trong khoang thoi gian thuc hien animationDeath
	timeDelayHurting = 0;
}


PlayerDeathState::~PlayerDeathState()
{
}

void PlayerDeathState::Update(float dt)
{
	if (allowDelayHurting)
	{
		timeDelayHurting += dt;

		if (timeDelayHurting > 0.5f)
		{
			allowDelayHurting = false;
			timeDelayHurting = 0;
		}
	}
}

void PlayerDeathState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_LEFT] || keys[VK_RIGHT])
    {
		//cho phep thuc hien animation khac khi animationDeath thuc hien xong
		if (!allowDelayHurting)
		{
			this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
			return;
		}
    }
}

PlayerState::StateName PlayerDeathState::GetState()
{
    return PlayerState::Death;
}