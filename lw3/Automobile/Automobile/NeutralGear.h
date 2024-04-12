#pragma once
#include "Gear.h"

class NeutralGear : public Gear
{
private:
	int _number;

public:
	NeutralGear(int number);
	
	virtual bool CheckIfSpeedIsAllowed(int desiredSpeed, int currentCarSpeed) override;
};

