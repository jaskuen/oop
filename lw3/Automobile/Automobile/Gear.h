#include "Direction.h"
#include <string>
#include <array>
#pragma once

class Gear
{
private:
	//
	int m_number;
	int m_minSpeed;
	int m_maxSpeed;
	std::string m_allowedDirection;
	std::array<std::string, 3> m_directionList = {Direction::Backward, Direction::Still, Direction::Forward};
public:
	Gear();
	Gear(int number);
	Gear(int number, int minSpeed, int maxSpeed, std::string direction);
	int GetNumber();
	std::string GetAllowedDirection();

	bool CheckIfSpeedIsAllowed(int speed);
	bool CheckIfSpeedIsAllowed(int desiredSpeed, int currentCarSpeed);
};

