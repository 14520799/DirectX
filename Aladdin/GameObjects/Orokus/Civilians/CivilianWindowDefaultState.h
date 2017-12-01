#pragma once
#include "CivilianWindow.h"
#include "../OrokuState.h"

class CivilianWindowDefaultState : public OrokuState
{
public:
	CivilianWindowDefaultState(OrokuData *orokuData);
	~CivilianWindowDefaultState();

	void Update(float dt);

	virtual StateName GetState();

protected:
	float timeDelay;
};