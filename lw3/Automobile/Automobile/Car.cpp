#include "Car.h"
#include "Gear.h"
#include "Direction.h"
#include "CommandError.h"
#include "CommandSuccess.h"
#include <iostream>
#include <map>

CommandError errorList;
CommandSuccess successList;

void CCar::InitGearList()
{
	// -1 - задняя передача
	//  0 - нейтральная передача
	//  1 - передняя передача
	Gear gearNeutral(0);
	Gear gearBackward(-1, 0, 20, Direction::Backward);
	Gear gearFirst(1, 0, 30, Direction::Forward);
	Gear gearSecond(2, 20, 50, Direction::Forward);
	Gear gearThird(3, 30, 60, Direction::Forward);
	Gear gearFourth(4, 40, 90, Direction::Forward);
	Gear gearFifth(5, 50, 150, Direction::Forward);
	CCar::m_gearMap.insert({ gearBackward.GetNumber(), gearBackward });
	CCar::m_gearMap.insert({ 0, gearNeutral  });
	CCar::m_gearMap.insert({ gearFirst.   GetNumber(), gearFirst    });
	CCar::m_gearMap.insert({ gearSecond.  GetNumber(), gearSecond   });
	CCar::m_gearMap.insert({ gearThird.   GetNumber(), gearThird    });
	CCar::m_gearMap.insert({ gearFourth.  GetNumber(), gearFourth   });
	CCar::m_gearMap.insert({ gearFifth.   GetNumber(), gearFifth    });
}

void CCar::AddNewGear(Gear gear)
{
	CCar::m_gearMap.insert({ gear.GetNumber(), gear });
}

CCar::CCar()
{
	InitGearList();
	m_currentDirection = Direction::Still;
	m_engineIsWorking = false;
	m_currentGear = m_gearMap.at(0);
}

const void CCar::Info()
{
	std::string engineState = m_engineIsWorking ? "включен" : "выключен";
	std::cout << "Состояние двигателя: " << engineState <<
		"\nТекущая передача: " << m_currentGear.GetNumber() <<
		"\nТекущая скорость: " << m_currentSpeed <<
		"\nНаправление движения: " << m_currentDirection << std::endl;
}

bool CCar::TurnOnEngine()
{
	CCar::m_engineIsWorking = true;
	return successList.EngineTurnedOn();
}

bool CCar::TurnOffEngine()
{
	if (m_currentSpeed != 0 || m_currentGear.GetNumber() != 0)
	{
		return errorList.TurnOffIsImpossible();
	}
	CCar::m_engineIsWorking = false;
	return successList.EngineTurnedOff();
}

bool CCar::SetGear(int gearNumber)
{
	if (gearNumber < 0 && m_currentSpeed > 0) // переключение на заднюю с ненулевой скоростью
	{
		return errorList.ChangeGearToBackwardWhileMoving();
	}
	if (!m_engineIsWorking && gearNumber != 0) // переключение на ненулевую передачу, когда двигатель выключен
	{
		return errorList.ChangeGearWhileEngineTurnedOff();
	}
	if (m_currentDirection == Direction::Backward && gearNumber > 0)
	{
		return errorList.ChangeGearToForwardFromBackwardWhileMoving();
	}
	if (!m_gearMap.at(gearNumber).CheckIfSpeedIsAllowed(m_currentSpeed))
	{
		return false;
	}
	m_currentGear = m_gearMap.at(gearNumber);
	return successList.GearChanged();
}

bool CCar::SetSpeed(int speed)
{
	if (m_currentGear.GetNumber() == 0 && !m_currentGear.CheckIfSpeedIsAllowed(speed, m_currentSpeed))
	{
		return errorList.NeutralRaiseSpeed();
	}
	else if (!m_currentGear.CheckIfSpeedIsAllowed(speed))
	{
		return errorList.ChangeSpeedNotInRange();
	}
	
	m_currentSpeed = speed;
	if (m_currentSpeed == 0)
	{
		m_currentDirection = Direction::Still;
	}
	else if (m_currentDirection == Direction::Still && m_currentGear.GetNumber() != 0)
	{
		m_currentDirection = m_currentGear.GetAllowedDirection();
	}
	return successList.SpeedChanged();
}
