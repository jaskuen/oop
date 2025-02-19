#include <string>
#include <iostream>
#include <fstream>
#include <optional>
#include <variant>

//enum class
enum ProgramLaunchType
{
	FileInput,
	ManualInput,
	Information,
};

struct Args
{
	ProgramLaunchType launchType;
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replacementString;
};

// Отдельный тип и std::variant

std::optional<Args> ParseCommandLine(int argc, char* argv[])
{
	Args args;
	if (argc == 1)
	{
		args.launchType = ManualInput;

		return args;
	}
	if (argc == 2)
	{
		std::string arg(argv[1]);
		if (arg == "-h")
		{
			args.launchType = Information;
			return args;
		}
		return std::nullopt;
	}
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return std::nullopt;
	}

	args.launchType = FileInput;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replacementString = argv[4];

	return args;
}

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	if (searchString.length() == 0)
	{
		return subject;
	}
	size_t foundPos = 0;
	size_t pos = 0;
	std::string result;
	while (foundPos < subject.size())
	{
		foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);
		if (foundPos < subject.size())
		{
			result.append(replacementString);
			pos = foundPos + searchString.size();
		}
	}
	
	return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;
	//bool started = false;

	while (std::getline(input, line))
	{
		/*if (!started)
		{
			started = true;
		}*/
		output << ReplaceString(line, searchString, replacementString) << std::endl;
		if (output.bad())
		{
			throw std::runtime_error("Failed to write into output file\n");
		}
	}/*
	if (!started)
	{
		throw std::runtime_error("ERROR\n");
	}*/
}

void Replace(const ProgramLaunchType& type, const std::string& inputFile, const std::string& outputFile, 
	const std::string& searchString, const std::string& replacementString)
{
	if (type == Information)
	{
		std::cout << "Replace string program. Replaces all substrings in certain stream with another string.\n"
			<< "File input usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n"
			<< "Manual input usage: replace.exe\n"
			<< "Information: replace.exe -h\n";
		return;
	}
	if (type == ManualInput)
	{
		// Сразу делать в args
		std::string searchString, replacementString;
		std::getline(std::cin, searchString);
		std::getline(std::cin, replacementString);
		CopyStreamWithReplacement(std::cin, std::cout, searchString, replacementString);
		return;
	}
	std::ifstream input(inputFile);
	if (!input.is_open())
	{
		throw std::runtime_error("Failed to open " + inputFile + " for reading\n");
	}

	std::ofstream output(outputFile);
	if (!output.is_open())
	{
		throw std::runtime_error("Failed to open " + outputFile + " for reading\n");
	}
	CopyStreamWithReplacement(input, output, searchString, replacementString);
	if (!output.flush())
	{
		throw std::runtime_error("Failed to save data on disk");
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
		Replace(args->launchType, args->inputFileName, args->outputFileName, args->searchString, args->replacementString);
	}
	catch (const std::exception& exception)
	{
		std::cout << "ERROR" << std::endl;
	}
	return EXIT_SUCCESS;
}