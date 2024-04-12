#pragma once
class CommandError
{
public:
	bool NoSuchCommand();
	bool NeutralRaiseSpeed();
	bool SetSpeedBelowZero();
	bool TurnOffIsImpossible();
	bool ChangeSpeedNotInRange();
	bool ChangeGearNotInRange();
	bool ChangeGearToBackwardWhileMoving();
	bool ChangeGearToForwardFromBackwardWhileMoving();
	bool ChangeGearWhileEngineTurnedOff();
};

