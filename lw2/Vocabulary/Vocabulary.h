#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using Vocabulary = std::multimap<std::string, std::string>;

struct FullVocabulary
{
	Vocabulary main, opposite;
	FullVocabulary() {}
	FullVocabulary(const std::pair<Vocabulary, Vocabulary>& vPair)
	{
		main = vPair.first;
		opposite = vPair.second;
	}
};

// Добавить больше функций по работе со словарем для тестирования
// Убрать функции, которые не нужны для работы словаря
// Не давать пользователю работать со словарём FullV, кпростить логику
bool SavePhrase(const std::string& p, FullVocabulary& v);
FullVocabulary ReadVocabularyFromFile(const std::string& fileName);
void SaveVocabulary(const std::string& fileName, const FullVocabulary& v);