#include <iostream>
#include <optional>
#include <fstream>
#include <vector>
#include <string>

const int MAX_MATRIX_SIZE = 100;

enum class ProgramMode { File, Manual, Info };
enum class FillCharTypes
{
	Empty = ' ',
	Filled = '.',
	Source = 'O',
	Border = '#',
};

using Matrix = std::vector<std::vector<char>>;
struct Position
{
	int x, y;
	Position()
	{
		x = 0;
		y = 0;
	}
	Position(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

struct Args
{
	ProgramMode launchType;
	std::string inputFileName;
	std::string outputFileName;
};

std::optional<Args> ParseCommandLine(int argc, char* argv[])
{
	Args args;
	if (argc == 1)
	{
		args.launchType = ProgramMode::Manual;

		return args;
	}
	if (argc == 2)
	{
		std::string arg(argv[1]);
		if (arg == "-h")
		{
			args.launchType = ProgramMode::Info;
			return args;
		}
		return std::nullopt;
	}
	if (argc != 3)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: fill.exe <inputFile> <outputFile>\n";
		return std::nullopt;
	}

	args.launchType = ProgramMode::File;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];

	return args;
}

void TrimEnd(std::string& s) {
	const char* ws = " \t\n\r\f\v";
	s.erase(s.find_last_not_of(ws) + 1);
}

bool PositionInsideField(const Position& position)
{
	return (position.x >= 0 && position.x < 100) && (position.y >= 0 && position.y < 100);
}

void WriteMatrix(const Matrix& matrix, std::ostream& output)
{
	for (int j = 0; j < matrix.size(); j++)
	{
		std::string currentLine;
		for (int i = 0; i < matrix[j].size(); i++)
		{
			if (matrix[j][i] == 0)
			{
				break;
			}
			currentLine += matrix[j][i];
		}
		TrimEnd(currentLine);
		if (currentLine.size() == 0)
		{
			continue;
		}
		output << currentLine << std::endl;
	}
}

void Fill(const Matrix& matrix, const std::vector<Position>& startPoints, std::ostream& output)
{
	std::vector<Position> wave = startPoints;
	Matrix matrixToFill = matrix;
	while (wave.size() > 0)
	{
		std::vector<Position> newWave;
		for (Position pos : wave)
		{
			for (Position possibleWay : 
				{ Position(pos.x + 1, pos.y), Position(pos.x - 1, pos.y), 
				  Position(pos.x, pos.y + 1), Position(pos.x, pos.y - 1) })
			{
				if (PositionInsideField(possibleWay))
				{
					if (matrixToFill[possibleWay.y][possibleWay.x] != char(FillCharTypes::Border)
						&& matrixToFill[possibleWay.y][possibleWay.x] != char(FillCharTypes::Filled)
						&& matrixToFill[possibleWay.y][possibleWay.x] != char(FillCharTypes::Source))
					{
						newWave.push_back(possibleWay);
						matrixToFill[possibleWay.y][possibleWay.x] = char(FillCharTypes::Filled);
					}
				}
			}
		}
		wave = newWave;
	}

	WriteMatrix(matrixToFill, output);
}

void GetMatrixAndFill(std::istream& input, std::ostream& output)
{
	std::vector<std::vector<char>> matrix;
	std::vector<Position> sources;
	std::string line;
	matrix.resize(MAX_MATRIX_SIZE);
	bool eof = false;
	for (int j = 0; j < MAX_MATRIX_SIZE; j++)
	{
		matrix[j].resize(MAX_MATRIX_SIZE);
		if (!std::getline(input, line))
		{
			eof = true;
		}
		if (!eof)
		{
			for (int i = 0; i < std::min(int(line.size()), MAX_MATRIX_SIZE); i++)
			{
				matrix[j][i] = line[i];
				if (line[i] == char(FillCharTypes::Source))
				{
					sources.push_back(Position(i, j));
				}
			}
		}
	}
	Fill(matrix, sources, output);
}

void ParseStreamsInfoAndFill(ProgramMode type, const std::string& inputFileName, const std::string& outputFileName)
{
	switch (type)
	{
	case ProgramMode::Info:
		std::cout << "Fill program. Fills area from points defined as wave sources.\n"
			<< "File input usage: fill.exe <inputFile> <outputFile>\n"
			<< "Manual input usage: fill.exe\n"
			<< "Information: fill.exe -h\n";
		return;
	case ProgramMode::Manual:
		GetMatrixAndFill(std::cin, std::cout);
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

	GetMatrixAndFill(input, output);
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
	catch (const std::exception& exception)
	{
		std::cout << "ERROR" << std::endl;
	}
	return EXIT_SUCCESS;
}
