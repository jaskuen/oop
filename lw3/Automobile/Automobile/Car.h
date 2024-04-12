#pragma once

#include "Gear.h"
#include <vector>
#include <map> 

const int SpeedGearCount = 6;
// ������� ��������� ������� ����� ���������, ����� ��� ���� � ������� �������
class CCar
{
	// ��������� ����� � �����, ��������� � ������
private:
	static const int MinGearNumber = -1;
	static const int MaxGearNumber = 5;

	bool m_engineIsWorking; // mm_...
	Gear m_currentGear;
	std::string m_currentDirection;//enum ������ string
	int m_currentSpeed;
	// ������� ���� �����������
	std::map<int, Gear> m_gearMap;
	
	void AddNewGear(Gear gear);
	void InitGearList();

public:
	CCar();
	// ?? const void
	// ��������� ����� � UI
	const void Info();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gearNumber);
	bool SetSpeed(int speed);
};

