#include <iostream>
#include <optional>

struct Args
{
    std::string sourceStr;
    std::string destinationStr;
    std::string valueStr;
};

std::optional<Args> ParseCommandLine(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cout << "Invalid argument count\n"
            << "Usage: radix.exe <source notation> <destination notation> <value>\n";
        return std::nullopt;
    }

    Args args;

    args.sourceStr = argv[1];
    args.destinationStr = argv[2];
    args.valueStr = argv[3];

    return args;
}

int CharToInt(const char& ch, int radix)
{
    int code = (int)ch;
    if (code > 47 && code < 58)
    {
        return code - 48;
    }
    else
    {
        if (code > 64 && code < 91)
        {
            return code - 55;
        }
    }
    throw std::runtime_error("Incorrect symbol entered.\n");
}

// Подобрать нормальное название функции MultAndAdd(factor1, factor2, adden)
bool MultAndAdd(int factor1, int factor2, int adden)
{

}

bool OutOfIntRange(int n, int radix, int intFromChar, int sign)
{
    if (sign >= 0)
    {
        return (n > (INT_MAX - intFromChar) / radix);
    }
    else
    {
        return (n < (INT_MIN + intFromChar) / radix);
    }
}

// Временная зависимость этой
int StringToInt(const std::string& str, int radix)
{
    int result = 0;
    size_t counter = 0;
    int sign = 1;
    // Если строка пустая, будет exception: out of range
    if (str.at(0) == '-')
    {
        counter++;
        sign = -1;
    }
    int intFromChar;
    while (counter < str.length())
    {
        intFromChar = CharToInt(str.at(counter++), radix);
        if (OutOfIntRange(result, radix, intFromChar, sign))
        {
            throw std::runtime_error("Result out if range.\n");
        }
        result = result * radix + intFromChar * sign;
    }
    return result;
}

char IntToChar(int n, int radix)
{
    std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (n >= radix)
    {
        throw std::runtime_error("Incorrect number and radix combination.\n");
    }
    return chars.at(abs(n));
}

int GetDegree(int n, int radix)
{
    int degree = 0;
    while (n / radix > 0)
    {
        n = n / radix;
        degree++;
    }
    return degree;
}

int Power(int n, int degree)
{
    int result = 1;
    while (degree > 0)
    {
        result = result * n;
        degree -= 1;
    }
    return result;
}

std::string IntToString(int n, int radix)
{
    std::string result = "";
    int num = 0;
    bool resultIsMinInt = false;
   
    if (n < 0)
    {
        if (n == INT_MIN)
        {
            n++;
            resultIsMinInt = true;
        }
        n *= -1;
        result = "-";
    }
    int resultLength = GetDegree(n, radix);

    for (int i = resultLength; i >= 0; i--)
    {
        num = n / Power(radix, i);
        n -= num * Power(radix, i);
        if (i == 0 && resultIsMinInt)
        {
            num += 1;
        }
        result += IntToChar(num, radix);
    }

    return result;
}

void CheckRadix(int source, int destination)
{
    if (source < 2 || source > 36)
    {
        throw std::runtime_error("Source radix is not correct. It should be between 2 and 36.\n");
    }
    if (destination < 2 || destination > 36)
    {
        throw std::runtime_error("Destination radix is not correct. It should be between 2 and 36.\n");
    }
}

// Переименовать ConvertNotation
// Просмотреть лекцию, узнать, когда передавать ссылки, объяснить преподавателю
// Подавать в функцию сразу число(система счисления)
void ConvertNotation(std::string sourceStr, std::string destinationStr, std::string valueStr)
{
    bool error = false;

    int source = StringToInt(sourceStr, 10);
    int destination = StringToInt(destinationStr, 10);
    CheckRadix(source, destination);

    int result = StringToInt(valueStr, source);
    
    std::cout << IntToString(result, destination) << std::endl;
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
        ConvertNotation(args->sourceStr, args->destinationStr, args->valueStr);
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
    }

    return EXIT_SUCCESS;
}

