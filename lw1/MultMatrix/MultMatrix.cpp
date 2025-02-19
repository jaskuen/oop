#include <iostream>
#include <optional>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <array>
#include <iomanip>
#include <stdexcept>

const int MATRIX_SIZE = 3;

enum class ProgramMode { File, Manual };
struct Args
{
	ProgramMode launchType;
	std::string inputFileName;
	std::string outputFileName;
};

struct ErrorException : std::exception
{
private:
	std::ostringstream m_messageStream;
public:
	ErrorException(std::ostream& output, const std::string& message)
	{
		output << message << std::endl;
	}
	virtual const char* what() const noexcept override {
		return m_messageStream.str().c_str();
	}
};

using Matrix = std::array<std::array<float, MATRIX_SIZE>, MATRIX_SIZE>;

std::optional<Args> ParseCommandLine(int argc, char* argv[])
{
	Args args;
	if (argc == 1)
	{
		args.launchType = ProgramMode::Manual;

		return args;
	}
	if (argc != 3)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: multmatrix.exe <inputFile> <outputFile>\n";
		return std::nullopt;
	}

	args.launchType = ProgramMode::File;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];

	return args;
}

Matrix ReadMatrix(std::istream& input, std::ostream& output)
{
	Matrix matrix;
	std::string line;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		if (!std::getline(input, line))
		{
			throw ErrorException(output, "ERROR");
		}
		std::istringstream stringStream(line);
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			if (!(stringStream >> matrix[i][j]))
			{
				throw ErrorException(output, "ERROR");
			}
		}
	}
	std::getline(input, line);
	return matrix;
}

void WriteMatrix(const Matrix& matrix, std::ostream& output)
{
	int roundTo = 3;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			output << std::fixed << std::setprecision(roundTo) << matrix[i][j] << " ";
		}
		output << std::endl;
	}
}

void MultiplyMatrices(const Matrix& matrix1, const Matrix& matrix2, std::ostream& output)
{
	Matrix finalMatrix;
	for (int row = 0; row < MATRIX_SIZE; row++)
	{
		for (int column = 0; column < MATRIX_SIZE; column++)
		{
			finalMatrix[row][column] = float(0);
			for (int delta = 0; delta < MATRIX_SIZE; delta++)
			{
				finalMatrix[row][column] += matrix1[row][delta] * matrix2[delta][column];
			}
		}
	}

	WriteMatrix(finalMatrix, output);
}

void ReadAndMultiplyMatrices(std::istream& input, std::ostream& output)
{
	Matrix matrix1, matrix2;
	matrix1 = ReadMatrix(input, output);
	matrix2 = ReadMatrix(input, output);
	MultiplyMatrices(matrix1, matrix2, output);
}

void ParseStreamsInfoAndFill(ProgramMode mode, const std::string& inputFileName, const std::string& outputFileName)
{
	if (mode == ProgramMode::Manual)
	{
		ReadAndMultiplyMatrices(std::cin, std::cout);
		return;
	}

	std::ifstream input(inputFileName);
	if (!input.is_open())
	{
		throw std::runtime_error("Failed to open " + inputFileName + " for reading\n");
	}

	std::ofstream output(outputFileName);
	if (!output.is_open())
	{
		throw std::runtime_error("Failed to open " + outputFileName + " for writing\n");
	}

	ReadAndMultiplyMatrices(input, output);
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
		ParseStreamsInfoAndFill(args->launchType, args->inputFileName, args->outputFileName);
	}
	catch (const ErrorException& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return EXIT_SUCCESS;
}