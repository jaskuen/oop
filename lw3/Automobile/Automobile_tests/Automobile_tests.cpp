#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Automobile/Car.h"
#include "../Automobile/CommandError.h"
#include "../Automobile/CommandSuccess.h"
#include "../Automobile/Direction.h"
#include "../Automobile/Gear.h"
#include "../Automobile/UserInterface.h"



SCENARIO("Working with car correctly")
{
	CCar car;
	GIVEN("Car with engine turned off")
	{
		car.TurnOffEngine();
		REQUIRE(car.TurnOffEngine());
		WHEN("We want to move forward")
		{
			car.TurnOnEngine();
			car.SetGear(1);
			THEN("We change gear to further to increase speed")
			{
				car.SetSpeed(30);
				REQUIRE(car.SetGear(2));
				REQUIRE(car.SetSpeed(50));
				AND_THEN("We reach top speed")
				{
					REQUIRE(car.SetGear(5));
					REQUIRE(car.SetSpeed(150));
				}
			}
			THEN("We want to go back to zero")
			{
				REQUIRE(car.SetGear(0));
				REQUIRE(car.SetSpeed(10));
				WHEN("We want to check if we can go from neutral to another if we are in the allowed speed range")
				{
					REQUIRE(car.SetGear(1));
					THEN("Go back to neutral")
					{
						REQUIRE(car.SetGear(0));
					}
				}
				REQUIRE(car.SetSpeed(0));
			}
		}
		WHEN("We want to move backward")
		{
			car.TurnOnEngine();
			car.SetGear(-1);
			THEN("We move backward")
			{
				REQUIRE(car.SetSpeed(20));
			}
		}
	}
	system("cls");
}

SCENARIO("Working with car incorrectly")
{
	CCar car;
	WHEN("We have car engine turned off")
	{
		car.TurnOffEngine();
		THEN("We want to set to any gear except neutral")
		{
			REQUIRE_FALSE(car.SetGear(-1));
			REQUIRE_FALSE(car.SetGear(1));
			REQUIRE_FALSE(car.SetGear(2));
			REQUIRE_FALSE(car.SetGear(3));
			REQUIRE_FALSE(car.SetGear(4));
			REQUIRE_FALSE(car.SetGear(5));
		}
	}
	WHEN("We have car engine turned on with neutral gear")
	{
		car.TurnOnEngine();
		car.SetGear(0);
		THEN("We want to increase speed")
		{
			REQUIRE_FALSE(car.SetSpeed(10));
		}
	}
	WHEN("We have car engine turned on with 1 gear, 20 speed")
	{
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		THEN("We want to set gear with current speed not in range")
		{
			REQUIRE_FALSE(car.SetGear(5));
		}
	}
	system("cls");
}


