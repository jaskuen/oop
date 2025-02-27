#pragma once
#include <map>
#include <vector>
#include <string>
#include <fstream>

enum class Language
{
	RU,
	EN
};

struct Word
{
	std::string word;
	Language lang;
};

struct Translations
{
	std::vector<std::string> english, russian;
};
using WordToId = std::map<std::string, int>;
using Vocabulary = std::map<int, Translations>;

std::string ReadWord(std::ifstream& file)
{

}

Vocabulary ReadVocabularyFromFile(const std::string fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open " + fileName + " for reading");
	}
	std::string line;
	while (std::getline(file, line))
	{

	}
}