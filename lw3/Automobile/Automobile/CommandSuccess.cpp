#include "CommandSuccess.h"
#include <iostream>

bool CommandSuccess::EngineTurnedOn()
{
    std::cout << "Успешно! Двигатель был включен!" << std::endl;
    return true;
}

bool CommandSuccess::EngineTurnedOff()
{
    std::cout << "Успешно! Двигатель был выключен!" << std::endl;
    return true;
}

bool CommandSuccess::GearChanged()
{
    std::cout << "Успешно! Вы сменили передачу!" << std::endl;
    return true;
}

bool CommandSuccess::SpeedChanged()
{
    std::cout << "Успешно! Вы изменили скорость!" << std::endl;
    return true;
}
