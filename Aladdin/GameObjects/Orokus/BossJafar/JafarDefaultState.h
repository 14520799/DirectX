#pragma once
#include "Jafar.h"
#include "../OrokuState.h"

class JafarDefaultState : public OrokuState
{
public:
	JafarDefaultState(OrokuData *orokuData);
	~JafarDefaultState();

	void Update(float dt);

	virtual StateName GetState();

protected:
};