#pragma once
#include "Gear.h"
class SpeedGear : public Gear
{
private:
	int _minSpeed;
	int _maxSpeed;

public:
	SpeedGear(int number, int minSpeed, int maxSpeed, int index);

	virtual bool CheckIfSpeedIsAllowed(int speed) override;
};

