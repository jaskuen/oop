#include "CommandError.h"
#include "iostream"

bool CommandError::NoSuchCommand()
{
	std::cout << "Не получилось! Такой команды не существует!" << std::endl;
	return false;
}

bool CommandError::NeutralRaiseSpeed()
{
	std::cout << "Не получилось! На нейтральной передаче нельзя набирать скорость!" << std::endl;
	return false;
}

bool CommandError::SetSpeedBelowZero()
{
	std::cout << "Не получилось! Нельзя использовать отрицательные значения скорости!" << std::endl;
	return false;
}

bool CommandError::TurnOffIsImpossible()
{
	std::cout << "Не получилось! Чтобы заглушить двигатель, нужно находиться в покое на нейтральной передаче!" << std::endl;
	return false;
}

bool CommandError::ChangeSpeedNotInRange()
{
	std::cout << "Не получилось! Желаемая скорость не лежит в границах возможной для данной передачи!" << std::endl;
	return false;
}

bool CommandError::ChangeGearNotInRange()
{
	std::cout << "Не получилось! Скорость автомобиля не лежит в допустимых значениях передачи!" << std::endl;
	return false;
}

bool CommandError::ChangeGearToBackwardWhileMoving()
{
	std::cout << "Не получилось! Нельзя включить заднюю передачу в положении движения!" << std::endl;
	return false;
}

bool CommandError::ChangeGearToForwardFromBackwardWhileMoving()
{
	std::cout << "Не получилось! Нельзя включить переднюю передачу с задней в движении!" << std::endl;
	return false;
}

bool CommandError::ChangeGearWhileEngineTurnedOff()
{
	std::cout << "Не получилось! При выключенном двигателе можно находиться только на нейтральной передаче!" << std::endl;
	return false;
}
