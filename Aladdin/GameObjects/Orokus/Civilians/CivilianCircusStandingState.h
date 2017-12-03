#pragma once
#include "CivilianCircus.h"
#include "../OrokuState.h"

class CivilianCircusStandingState : public OrokuState
{
public:
	CivilianCircusStandingState(OrokuData *orokuData);
	~CivilianCircusStandingState();

	void Update(float dt);

	virtual StateName GetState();

protected:
};