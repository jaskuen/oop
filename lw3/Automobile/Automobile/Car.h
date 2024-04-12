#pragma once

#include "Gear.h"
#include <vector>
#include <map> 

const int SpeedGearCount = 6;
// сделать структуру проекта менее ветвистой, чтобы все было в бытсром доступе
class CCar
{
	// приватная часть в конце, публичная в начале
private:
	static const int MinGearNumber = -1;
	static const int MaxGearNumber = 5;

	bool m_engineIsWorking; // mm_...
	Gear m_currentGear;
	std::string m_currentDirection;//enum вместо string
	int m_currentSpeed;
	// сделать поле статическим
	std::map<int, Gear> m_gearMap;
	
	void AddNewGear(Gear gear);
	void InitGearList();

public:
	CCar();
	// ?? const void
	// перенести метод в UI
	const void Info();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gearNumber);
	bool SetSpeed(int speed);
};

