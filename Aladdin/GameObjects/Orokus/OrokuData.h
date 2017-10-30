#pragma once
class OrokuState;
class ThinGuard;
class FatGuard;
class StrongGuard;

class OrokuData
{
public:
	OrokuData();
	~OrokuData();

	OrokuState	*state;
	ThinGuard	*thinGuard;
	FatGuard	*fatGuard;
	StrongGuard	*strongGuard;

protected:
};