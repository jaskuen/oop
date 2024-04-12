#include "string"
#include "iostream"
#include "fstream"
#include "cassert"

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
		else // Больше не найдено совпадений
		{
			// Копируем остаток строки
			result.append(subject, pos);
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

	ifstream input(argv[1]);

	// Открываем файлы для чтения и записи и проверяем на ошибки

	if (!input.is_open()) 
	{
		std::cout << "Failed to open " << argv[1] << "for reading\n";
		return 1;
	}

	ofstream output(argv[2]);

	if (!output.is_open())
	{
		std::cout << "Failed to open " << argv[1] << "for writing\n";
		return 1;
	}

	std::string search = argv[3];
	std::string replace = argv[4];

	CopyStreamWithReplacement(inputFile, outputFile, search, replace);
	// Подумайте, для чего здесь вызывается flush?
	outputFile.flush();	

	return 0;
}