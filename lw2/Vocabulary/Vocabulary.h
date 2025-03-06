#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

enum class Language
{
	RU,
	EN
};

using Vocabulary = std::multimap<std::string, std::string>;
struct FullVocabulary
{
	Vocabulary ruEn, enRu;
	FullVocabulary() {}
	// Первый словарь в паре - Англ -> Рус, второй - Рус -> Англ
	FullVocabulary(std::pair<Vocabulary, Vocabulary> vPair)
	{
		enRu = vPair.first;
		ruEn = vPair.second;
	}
};

void ToLower(std::string& s);
Language GetPhraseLanguage(const std::string& phrase);
bool ReadPhrase(std::string phrase, FullVocabulary& v);
void SavePhraseInVocabularies(const std::string& phrase, const std::string& translation, Vocabulary& main, Vocabulary& opposite);
std::ifstream OpenFileForReading(const std::string& fileName);
std::ofstream OpenFileForWriting(const std::string& fileName);
std::pair<Vocabulary, Vocabulary> ReadVocabularyFromFile(std::ifstream& file);
void AskUserToSaveVocabulary(std::string fileName, const FullVocabulary& v);
void SaveVocabulary(const std::string& fileName, const Vocabulary& v);