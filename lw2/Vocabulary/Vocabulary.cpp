#include "Vocabulary.h"

const std::string LEAVE_PHRASE = "...";

void ToLower(std::string& s)
{
	std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { 
		std::string ru = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
		if (ru.find(c) != std::string::npos)
		{
			return int(c + 32);
		}
		if (c == 168)
		{
			return int('ё');
		}
		return std::tolower(c); 
	});
}

Language GetPhraseLanguage(const std::string& phrase)
{
	std::string lower = phrase;
	ToLower(lower);
	const char* enSymbols = "abcdefghijklmnopqrstuvwxyz";
	if (std::any_of(lower.begin(), lower.end(), [enSymbols](char c) { return std::strchr(enSymbols, c) != nullptr; }))
	{
		return Language::EN;
	}
	return Language::RU;
}

void WritePhraseTranslations(const std::string& phrase, const Vocabulary& v)
{
	std::string result;
	for (auto pair : v)
	{
		if (pair.first == phrase)
		{
			if (result == "")
			{
				result = pair.second;
				continue;
			}
			result += ", " + pair.second;
		}
	}
	std::cout << result << std::endl;
}

// Первый словарь в списке аргументов - основной, т.е. тот, который в ключе содержит слова языка, схожего с языком фразы
void SavePhraseInVocabularies(const std::string& phrase, const std::string& translation, Vocabulary& main, Vocabulary& opposite)
{
	main.insert({ phrase, translation });
	opposite.insert({ translation, phrase });
}

bool ReadPhrase(std::string phrase, FullVocabulary& v)
{
	ToLower(phrase);
	if (v.enRu.contains(phrase))
	{
		WritePhraseTranslations(phrase, v.enRu);
		return true;
	}

	if (v.ruEn.contains(phrase))
	{
		WritePhraseTranslations(phrase, v.ruEn);
		return true;
	}

	if (phrase == LEAVE_PHRASE)
	{
		return false;
	}

	std::cout << "Неизвестная фраза \"" << phrase << "\".Введите перевод или пустую строку для отказа." << std::endl;
	std::string translation;
	std::getline(std::cin, translation);
	ToLower(translation);

	if (translation.size() == 0)
	{
		std::cout << "Фраза \"" << phrase << "\" проигнорирована." << std::endl;
		return true;
	}
	if (translation == LEAVE_PHRASE)
	{
		return false;
	}

	if (GetPhraseLanguage(phrase) == Language::EN)
	{
		SavePhraseInVocabularies(phrase, translation, v.enRu, v.ruEn);
	}
	else
	{
		SavePhraseInVocabularies(phrase, translation, v.ruEn, v.enRu);
	}

	std::cout << "Фраза \"" << phrase << "\" сохранена в словаре как \"" << translation << "\"." << std::endl;
	return true;
}

std::ifstream OpenFileForReading(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open " + fileName + " for reading");
	}
	return file;
}

std::ofstream OpenFileForWriting(const std::string& fileName)
{
	std::ofstream file(fileName);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open " + fileName + " for writing");
	}
	return file;
}

std::pair<Vocabulary, Vocabulary> ReadVocabularyFromFile(std::ifstream& file)
{
	Vocabulary ruEn, enRu;
	std::string phrase, translation;
	// В файл записываем сначала фразу на английском, а потом перевод на русский
	while (std::getline(file, phrase))
	{
		std::getline(file, translation);
		enRu.insert({ phrase, translation });
		ruEn.insert({ translation, phrase });
	}
	return { enRu, ruEn };
}

void AskUserToSaveVocabulary(std::string fileName, const FullVocabulary& v)
{
	std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << std::endl;
	char answer;
	std::cin >> answer;
	if (std::tolower(answer) == 'y')
	{
		if (fileName == "")
		{
			std::cout << "Введите имя файла для данного словаря: " << std::endl;
			std::getline(std::cin, fileName);
			std::getline(std::cin, fileName);
		}
		SaveVocabulary(fileName, v.enRu);
	}
	
}

void SaveVocabulary(const std::string& fileName, const Vocabulary& v)
{
	std::ofstream file = OpenFileForWriting(fileName);
	for (const auto& pair : v)
	{
		file << pair.first << std::endl << pair.second << std::endl;
	}
}
