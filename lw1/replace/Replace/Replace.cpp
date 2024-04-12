#include <string>
#include <iostream>
#include <fstream>
#include <optional>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replacementString;
};

std::optional<Args> ParseCommandLine(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return std::nullopt;
	}

	Args args;

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
	while (foundPos < subject.length())
	{
		foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);
		if (foundPos < subject.length())
		{
			result.append(replacementString);
			pos = foundPos + searchString.length();
		}
	}
	
	return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << "\n";
		if (output.bad())
		{
			throw std::runtime_error("Failed to write into output file\n");
		}
	}
	if (!output.eof())
	{
		throw std::runtime_error("Failed to reach end of file\n");
	}
}

void Replace(const std::string& inputFile, const std::string& outputFile, 
	const std::string& searchString, const std::string& replacementString)
{
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
		Replace(args->inputFileName, args->outputFileName, args->searchString, args->replacementString);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}
	return EXIT_SUCCESS;
}