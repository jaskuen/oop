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

int CharToInt(char ch, int radix)
{
    //48 и 55 в символы
    if (ch >= '0' && ch <= '9')
    {
        return ch - 48;
    }
    else
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            return ch - 55;
        }
    }
    throw std::runtime_error("Incorrect symbol entered.\n");
}

// Подобрать нормальное название функции MultAndAdd(factor1, factor2, adden)
bool MultAndAdd(int factor1, int factor2, int adden)
{
    return true;
}

bool OutOfIntRange(int originalNumber, int radix, int intFromChar, int sign)
{
    // Можно  упростить return использование тернарного оператора
    if (sign >= 0)
    {
        return (originalNumber > (INT_MAX - intFromChar) / radix);
    }
    return (originalNumber < (INT_MIN + intFromChar) / radix);
}

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
    while (counter < str.size())
    {
        intFromChar = CharToInt(str.at(counter++), radix);
        if (OutOfIntRange(result, radix, intFromChar, sign))
        {
            throw std::runtime_error("Result is out of range.\n");
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

std::string IntToString(int originalNumber, int radix)
{
    std::string result;
    int num = 0;
    bool resultIsMinInt = false;
   
    if (originalNumber < 0)
    {
        if (originalNumber == INT_MIN)
        {
            originalNumber++;
            resultIsMinInt = true;
        }
        originalNumber *= -1;
        result = "-";
    }
    int resultLength = GetDegree(originalNumber, radix);

    for (int i = resultLength; i >= 0; i--)
    {
        // Работать сразу с originalNumber, постепенно разбирая его
        // Избавитсья от Power и GetDegree
        num = originalNumber / Power(radix, i);
        originalNumber -= num * Power(radix, i);
        if (i == 0 && resultIsMinInt)
        {
            num += 1;
        }
        result += IntToChar(num, radix);
    }

    return result;
}

void ValidateRadixParameters(int source, int destination)
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

void ChangeNumberRadix(const std::string& sourceStr, const std::string& destinationStr, const std::string& valueStr)
{
    int source = StringToInt(sourceStr, 10);
    int destination = StringToInt(destinationStr, 10);
    ValidateRadixParameters(source, destination);

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
        ChangeNumberRadix(args->sourceStr, args->destinationStr, args->valueStr);
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

