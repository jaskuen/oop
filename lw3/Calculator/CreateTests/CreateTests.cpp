#include <iostream>
#include <fstream>

int main()
{
    int num;
    std::ofstream file;
    file.open("in_million.txt");
    for (num = 3; num <= 1000000; num++)
    {
        file << "fn x" << num << "=x" << num - 1 << "+x" << std::endl;
    }

    file.close();
    return 0;
}