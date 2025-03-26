#include "Vocabulary.h"
#include "Vocabulary-tools.h"

const std::string LEAVE_PHRASE = "...";

void ToLower(std::string& s)
{
	const unsigned char jot = 168; // символ Ё
	std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { 
		std::string ru = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
		if (ru.find(c) != std::string::npos)
		{
			return int(c + 32);
		}
		if (c == jot)
		{
			return int('ё');
		}
		return std::tolower(c); 
	});
}

bool IsMainVocabularyPhrase(const std::string& phrase)
{
	std::string lower = phrase;
	ToLower(lower);
	const char* enSymbols = "abcdefghijklmnopqrstuvwxyz";
	if (std::any_of(lower.begin(), lower.end(), [enSymbols](char c) { return std::strchr(enSymbols, c) != nullptr; }))
	{
		return true;
	}
	return false;
}

void WritePhraseTranslations(const std::string& phrase, const Vocabulary& v)
{
	std::string result;
	for (const auto& pair : v)
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

bool CheckPhrase(const std::string& phrase, const FullVocabulary& v)
{
	if (v.main.contains(phrase))
	{
		WritePhraseTranslations(phrase, v.main);
		return true;
	}

	if (v.opposite.contains(phrase))
	{
		WritePhraseTranslations(phrase, v.opposite);
		return true;
	}

	if (phrase == LEAVE_PHRASE)
	{
		return false;
	}
}

bool SaveNewTranslation(const std::string& phrase, std::string& translation)
{
	std::cout << "Неизвестная фраза \"" << phrase << "\".Введите перевод или пустую строку для отказа." << std::endl;
	std::string translation;
	std::getline(std::cin, translation);

	if (translation.size() == 0)
	{
		std::cout << "Фраза \"" << phrase << "\" проигнорирована." << std::endl;
		return true;
	}
	if (translation == LEAVE_PHRASE)
	{
		return false;
	}

	if (IsMainVocabularyPhrase(phrase))
	{
		SavePhraseInVocabularies(phrase, translation, v.main, v.opposite);
	}
	else
	{
		SavePhraseInVocabularies(phrase, translation, v.opposite, v.main);
	}
	std::cout << "Фраза \"" << phrase << "\" сохранена в словаре как \"" << translation << "\"." << std::endl;
	return true;
}

// Передать по const& и создать копию
bool SavePhrase(const std::string& p, FullVocabulary& v)
{
	std::string phrase = p;
	ToLower(phrase);
	if (!CheckPhrase(phrase, v))
	{
		return false;
	}

	if (!SaveNewTranslation(phrase))
	{
		return false;
	}

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

FullVocabulary ReadVocabularyFromFile(const std::string& fileName)
{
	std::ifstream file = OpenFileForReading(fileName);
	FullVocabulary v;
	std::string phrase, translation;
	// В файл записываем сначала фразу на английском, а потом перевод на русский
	while (std::getline(file, phrase))
	{
		std::getline(file, translation);
		v.main.insert({ phrase, translation });
		v.opposite.insert({ translation, phrase });
	}
	return v;
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
		SaveVocabulary(fileName, v);
	}
	
}

void SaveVocabulary(const std::string& fileName, const FullVocabulary& v)
{
	std::ofstream file = OpenFileForWriting(fileName);
	for (const auto& pair : v.main)
	{
		file << pair.first << std::endl << pair.second << std::endl;
	}
}
