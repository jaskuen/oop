#include "CommandError.h"
#include "iostream"

bool CommandError::NoSuchCommand()
{
	std::cout << "�� ����������! ����� ������� �� ����������!" << std::endl;
	return false;
}

bool CommandError::NeutralRaiseSpeed()
{
	std::cout << "�� ����������! �� ����������� �������� ������ �������� ��������!" << std::endl;
	return false;
}

bool CommandError::SetSpeedBelowZero()
{
	std::cout << "�� ����������! ������ ������������ ������������� �������� ��������!" << std::endl;
	return false;
}

bool CommandError::TurnOffIsImpossible()
{
	std::cout << "�� ����������! ����� ��������� ���������, ����� ���������� � ����� �� ����������� ��������!" << std::endl;
	return false;
}

bool CommandError::ChangeSpeedNotInRange()
{
	std::cout << "�� ����������! �������� �������� �� ����� � �������� ��������� ��� ������ ��������!" << std::endl;
	return false;
}

bool CommandError::ChangeGearNotInRange()
{
	std::cout << "�� ����������! �������� ���������� �� ����� � ���������� ��������� ��������!" << std::endl;
	return false;
}

bool CommandError::ChangeGearToBackwardWhileMoving()
{
	std::cout << "�� ����������! ������ �������� ������ �������� � ��������� ��������!" << std::endl;
	return false;
}

bool CommandError::ChangeGearToForwardFromBackwardWhileMoving()
{
	std::cout << "�� ����������! ������ �������� �������� �������� � ������ � ��������!" << std::endl;
	return false;
}

bool CommandError::ChangeGearWhileEngineTurnedOff()
{
	std::cout << "�� ����������! ��� ����������� ��������� ����� ���������� ������ �� ����������� ��������!" << std::endl;
	return false;
}
