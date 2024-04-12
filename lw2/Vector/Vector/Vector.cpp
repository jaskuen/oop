#include <iostream>
#include <vector>
#include "WorkWithVector.h"

int main(int argc, char* argv[])
{

    std::vector<double> array;
    ReadVectorFromIstream(array, std::cin);
    AddAverageOfPositiveToEachElement(array);
    WriteVectorIntoOstream(array, std::cout);

    return EXIT_SUCCESS;
}


