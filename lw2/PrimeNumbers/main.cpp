#include <iostream>
#include "Prime.h"
#include <optional>
#include <string>

struct Args
{
    int upperBound;
};

std::optional<Args> ParseCommandLine(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid argument count\n"
            << "Usage: PrimeNumbers.exe <upperBound>\n";
        return std::nullopt;
    }

    Args args;

    int upperBound = std::stoi(argv[1]);
    if (upperBound < 0)
    {
        throw std::runtime_error("Upper bound is < 0");
    }

    args.upperBound = upperBound;

    return args;
}

int main(int argc, char* argv[])
{
    try
    {
        auto args = ParseCommandLine(argc, argv);
        std::set<int> primes = GeneratePrimeNumbersSet(args->upperBound);
        std::cout << primes.size() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
