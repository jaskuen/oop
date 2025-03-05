#include <iostream>
#include <optional>
#include <Windows.h>
#include "Vocabulary.h"

struct Args
{
    std::string vocabularyFileName;
};

std::optional<Args> ParseCommandLine(int argc, char* argv[])
{
    Args args;
    if (argc == 1)
    {
        args.vocabularyFileName = "";
    }
    else
    {
        if (argc == 2)
        {
            args.vocabularyFileName = argv[1];
        }
        else
        {
            std::cout << "Invalid argument count\n"
                << "Usage: Vocabulary.exe <vocabularyFileName> or Vocabulary.exe\n";
            return std::nullopt;
        }
    }

    return args;
}

int main(int argc, char* argv[])
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    try
    {
        auto args = ParseCommandLine(argc, argv);
        FullVocabulary v;
        if (args->vocabularyFileName != "")
        {
            std::ifstream file = OpenFileForReading(args->vocabularyFileName);
            v = ReadVocabularyFromFile(file);
        }
        std::string line;
        while (std::getline(std::cin, line))
        {
            if (!ReadPhrase(line, v))
            {
                break;
            }
        }
        AskUserToSaveVocabulary(args->vocabularyFileName, v);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

