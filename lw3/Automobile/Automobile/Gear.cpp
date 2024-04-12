#include "Gear.h"
#include "CommandError.h"
#include "CommandSuccess.h"

CommandError eList;
CommandSuccess sList;

Gear::Gear() {}

Gear::Gear(int number)
{
	m_allowedDirection = m_directionList[1];
	m_number = number;
	m_minSpeed = 0;
	m_maxSpeed = INT_MAX;
}

Gear::Gear(int number, int minSpeed, int maxSpeed, std::string direction)
{
	m_number = number;
	m_minSpeed = minSpeed;
	m_maxSpeed = maxSpeed;
	m_allowedDirection = direction;
}

std::string Gear::GetAllowedDirection()
{
	return m_allowedDirection;
}

int Gear::GetNumber()
{
	return m_number;
}

bool Gear::CheckIfSpeedIsAllowed(int desiredSpeed, int currentCarSpeed)
{
	if (desiredSpeed > currentCarSpeed)
	{
		return eList.NeutralRaiseSpeed();
	}
	else if (desiredSpeed < 0)
	{
		return eList.SetSpeedBelowZero();
	}
	return true;
}

bool Gear::CheckIfSpeedIsAllowed(int speed)
{
	return (speed >= m_minSpeed) && (speed <= m_maxSpeed);
}
