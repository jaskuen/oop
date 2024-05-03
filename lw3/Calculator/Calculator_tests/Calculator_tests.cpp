#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Calculator/UserInterface.h"
#include "../Calculator/Calculator.h"
#include "../Calculator/Function.h"
#include "../Calculator/Variable.h"
#include "../Calculator/OperationList.h"

CCalculator calculator;

SCENARIO("Creating variables")
{
	calculator.CreateVariable("a");
	REQUIRE(calculator.GetValue("a") != calculator.GetValue("a"));
	calculator.SetValueToVariable("b", 1.0);
	REQUIRE(calculator.GetValue("b") == 1.0);
	calculator.SetValueToVariable("a", -1.5);
	REQUIRE(calculator.GetValue("a") == -1.5);
	WHEN("Variable created with value from another variable")
	{
		calculator.SetValueToVariable("c", "b");
		REQUIRE(calculator.GetValue("c") == calculator.GetValue("b"));
		calculator.SetValueToVariable("b", 100.0); // changing value of "b", that currently has value as "c"
		REQUIRE_FALSE(calculator.GetValue("c") == calculator.GetValue("b"));// it does not change "c" value
	}
}

SCENARIO("Creating functions")
{
	// a:-1.5
	// b:100.0
	// c:1.0
	calculator.CreateFunction("A", "a");
	REQUIRE(calculator.GetValue("A") == calculator.GetValue("a"));
	calculator.SetValueToVariable("a", 15.0); // changing value of "a", that is a dependency of "A" func
	// a:15.0
	REQUIRE(calculator.GetValue("A") == calculator.GetValue("a")); // function value updates after changing its dependensies value
	calculator.CreateFunction("BC", "b", "c", '*');
	REQUIRE(calculator.GetValue("BC") == (calculator.GetValue("b") * calculator.GetValue("c")));
	THEN("There are many functions that depend on the same element")
	{
		// b:100.0
		// BC:100.0
		calculator.CreateFunction("D", "b", "BC", '+');
		REQUIRE(calculator.GetValue("D") == 200.0);
		calculator.SetValueToVariable("b", 10.0);
		// b:10.0
		// BC:10.0
		// Expected D:20.0
		REQUIRE(calculator.GetValue("D") == 20.0);
	}
}

SCENARIO("Million functions")
{
	std::ifstream in;
	in.open("in_million.txt");
	CUserInterface UI(calculator, in, std::cout);
	std::string command;
	unsigned int start_time = clock();
	while (std::getline(in, command))
	{
		UI.HandleCommand(command);
	}
	unsigned int end_time = clock();
	REQUIRE(end_time - start_time < 2000); // check speed of counting result
	REQUIRE(calculator.GetValue("x1000000") == calculator.GetValue("x") * 1000000.0); // value of 1.000.000 functions
}

SCENARIO("First 50 Fibonacci numbers")
{
	std::ifstream in;
	in.open("in_fibon.txt");
	CUserInterface UI(calculator, in, std::cout);
	std::string command;
	unsigned int start_time = clock();
	while (std::getline(in, command))
	{
		UI.HandleCommand(command);
	}
	unsigned int end_time = clock();
	REQUIRE(end_time - start_time < 100); // check speed of counting result
	REQUIRE(calculator.GetValue("fib50") == 12586269025.0); // value of 51-st Fibonacci number
}


