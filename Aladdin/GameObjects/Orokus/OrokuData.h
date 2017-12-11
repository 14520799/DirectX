#pragma once
class OrokuState;
class ThinGuard;
class FatGuard;
class StrongGuard;
class Camel;
class CivilianWindow;
class CivilianCircus;
class CivilianBasket;
class Jafar;

class OrokuData
{
public:
	OrokuData();
	~OrokuData();

	OrokuState		*state;
	ThinGuard		*thinGuard;
	FatGuard		*fatGuard;
	StrongGuard		*strongGuard;
	Camel			*camel;
	CivilianWindow	*civilianWindow;
	CivilianCircus	*civilianCircus;
	CivilianBasket	*civilianBasket;
	Jafar			*jafar;

protected:
};