#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <optional>
#include <string>
#include <algorithm>

struct Args
{
    std::string matrixFile;
};

using IntMatrix = std::vector<std::vector<int> >;
using DoubleMatrix = std::vector<std::vector<double> >;

std::optional<Args> ParseCommandLine(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid argument count\n"
            << "Usage: invert.exe <matrix file1>\n";
        return std::nullopt;
    }

    Args args;

    args.matrixFile = argv[1];

    return args;
}

int Factorial(int i)
{
    if (i == 0) return 1;
    else return i * Factorial(i - 1);
}

std::vector<int> ParseLineIntoNumArray(std::string line)
{
    int num;
    std::istringstream str(line);
    std::vector<int> result;
    while (str >> num)
    {
        result.push_back(num);
    }
    return result;
}

int InverseCount(std::vector<int> permutation)
{
    int result = 1;
    for (int i = 0; i < permutation.size(); i++)
    {
        for (int j = i + 1; j < permutation.size(); j++)
        {
            if (permutation[i] > permutation[j])
            {
                result *= -1;
            }
        }
    }
    return result;
}

int MatrixDeterminant(IntMatrix matrixArr)
{
    std::vector<int> permutation;
    for (int i = 0; i < matrixArr.size(); i++)
    {
        permutation.push_back(i);
    }
    int countOfOperations = Factorial(matrixArr.size());
    int result = 0;
    int element;
    for (int i = 0; i < countOfOperations; i++)
    {
        element = 1;
        for (int j = 0; j < matrixArr.size(); j++)
        {
            element *= matrixArr[permutation[j]][j];
        }
        result += element * InverseCount(permutation);
        std::next_permutation(permutation.begin(), permutation.end());
    }
    return result;
}

int Minor(size_t line, size_t column, IntMatrix matrixArr)
{
    IntMatrix matrixPartArr = matrixArr;
    matrixPartArr.erase(matrixPartArr.begin() + line);
    for (int i = 0; i < matrixPartArr.size(); i++)
    {
        matrixPartArr[i].erase(matrixPartArr[i].begin() + column);
    }
    return MatrixDeterminant(matrixPartArr);
}

void ParseFileIntoMatrixArray(std::string matrixFile, IntMatrix& matrixArr)
{
    std::ifstream sourceMatrix(matrixFile);
    if (!sourceMatrix.is_open())
    {
        throw std::runtime_error("Failed to open " + matrixFile + " for reading\n");
    }
    std::string line;

    while (std::getline(sourceMatrix, line))
    {
        matrixArr.push_back(ParseLineIntoNumArray(line));
    }
}

int Power(int n, int degree)
{
    int result = 1;
    while (degree > 0)
    {
        result = result * n;
        degree -= 1;
    }
    return result;
}

void RoundNumber(double& number, int count)
{
    number = round(number * Power(10, count)) / (Power(10, count) + 0.);
}

void CheckIfMatrixIsSquare(IntMatrix matrixArr)
{
    int matrixSize = matrixArr.size();
    for (int i = 0; i < matrixSize; i++)
    {
        if (matrixArr[i].size() != matrixSize)
        {
            throw (std::runtime_error("Matrix is not square. Impossible to find an inverted matrix."));
        }
    }
}

void InvertAndOutput(std::string matrixFile)
{
    IntMatrix matrixArr;
    ParseFileIntoMatrixArray(matrixFile, matrixArr);
    CheckIfMatrixIsSquare(matrixArr);
    DoubleMatrix invertedMatrix;
    std::vector<double> matrixLine;
    int determinant = MatrixDeterminant(matrixArr);
    if (determinant == 0)
    {
        throw std::runtime_error("Determinant of this matrix is 0. Impossible to find an inverted matrix.");
    }
    double matrixElement;

    for (int i = 0; i < matrixArr.size(); i++)
    {
        for (int j = 0; j < matrixArr.size(); j++)
        {
            matrixElement = (Minor(j, i, matrixArr) / (determinant + 0.)) * Power(-1, i + j);
            RoundNumber(matrixElement, 3);
            matrixLine.push_back(matrixElement);
            std::cout << matrixElement << " ";
        }
        std::cout << std::endl;
        invertedMatrix.push_back(matrixLine);
    }
}

int main(int argc, char* argv[])
{
    auto args = ParseCommandLine(argc, argv);
    if (!args)
    {
        return EXIT_FAILURE;
    }
    try
    {
        InvertAndOutput(args->matrixFile);
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
    }
    return EXIT_SUCCESS;
}

