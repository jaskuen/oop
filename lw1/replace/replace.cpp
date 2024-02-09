#include "string"
#include "iostream"
#include "fstream"

// Возвращает результат замены всех вхождения строки searchString внутри строки subject на replacementString
// Если строка searchString пустая, то возвращается subject
std::string ReplaceString(const std::string& subject, 
	const std::string& searchString, const std::string& replacementString)
{
	size_t pos = 0;
	// Результат будет записан в новую строку result, оставляя строку subject неизменной
	// Какие преимущества есть у этого способа по сравнению с алгоритмом, выполняющим
	// замену прямо в строке subject?
	std::string result;
	while (pos < subject.length())
	{
		// Находим позицию искомой строки, начиная с pos
		size_t foundPos = subject.find(searchString, pos);
		if (foundPos < subject.length())
		{
			// В результирующую строку записываем текст из диапазона [pos,foundPos)
			result.append(subject, pos, foundPos - pos);
			// Вставляем ту строку, на которую заменяем найденную
			result.append(replacementString);
			// Позицию поиска переносим на позицию после найденной строки foundPos + searchString.length()
			pos = foundPos + searchString.length();
		} 
		else 
		{
			result.append(subject, pos);
			pos = subject.length();
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
	}
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return 1;
	}

	// Самостоятельно выделите код копирования содержимого файла в отдельную функцию CopyFileWithReplacement,
	// принимающую имена файлов, а также строки для поиска и замены
	// Добавьте обработку ошибок

	std::ifstream inputFile;
	inputFile.open(argv[1]);

	bool fErr = false;

	if (!inputFile.is_open()) {
		std::cout << "Error opening input file " << argv[1] << "!";
		fErr = true;
	}

	std::ofstream outputFile;
	outputFile.open(argv[2]);

	if (!fErr) {
		std::string search = argv[3];
		std::string replace = argv[4];

		CopyStreamWithReplacement(inputFile, outputFile, search, replace);
		// Подумайте, для чего здесь вызывается flush?
		outputFile.flush();	
	}

	return 0;
}