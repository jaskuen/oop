#include "CommandSuccess.h"
#include <iostream>

bool CommandSuccess::EngineTurnedOn()
{
    std::cout << "�������! ��������� ��� �������!" << std::endl;
    return true;
}

bool CommandSuccess::EngineTurnedOff()
{
    std::cout << "�������! ��������� ��� ��������!" << std::endl;
    return true;
}

bool CommandSuccess::GearChanged()
{
    std::cout << "�������! �� ������� ��������!" << std::endl;
    return true;
}

bool CommandSuccess::SpeedChanged()
{
    std::cout << "�������! �� �������� ��������!" << std::endl;
    return true;
}
