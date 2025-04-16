#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../CString/CMyString.h"
#include <string>

TEST_CASE("Default ctor") {
    CMyString str;
    REQUIRE(str.GetLength() == 0);
    REQUIRE(str.GetCapacity() == 1);
    REQUIRE(std::strcmp(str.GetStringData(), "") == 0);
}

TEST_CASE("STL string ctor") {
    CMyString str("pizza");
    REQUIRE(str.GetLength() == 5);
    REQUIRE(str.GetCapacity() == 6);
    REQUIRE(std::strcmp(str.GetStringData(), "pizza") == 0);
}

TEST_CASE("C-string with length ctor") {
    CMyString str("pizza sushi", 5);
    REQUIRE(str.GetLength() == 5);
    REQUIRE(str.GetCapacity() == 6);
    REQUIRE(std::strcmp(str.GetStringData(), "pizza") == 0);
}

TEST_CASE("Copy ctor") {
    CMyString original("test");
    CMyString copy(original);
    REQUIRE(copy.GetLength() == 4);
    REQUIRE(copy.GetCapacity() == 5);
    REQUIRE(std::strcmp(copy.GetStringData(), "test") == 0);
}

TEST_CASE("Move ctor") {
    CMyString original("test");
    CMyString moved(std::move(original));
    REQUIRE(moved.GetLength() == 4);
    REQUIRE(moved.GetCapacity() == 5);
    REQUIRE(std::strcmp(moved.GetStringData(), "test") == 0);
    REQUIRE(original.GetLength() == 0);
    REQUIRE(std::strcmp(original.GetStringData(), "") == 0);
}

TEST_CASE("STL String ctor") {
    std::string stlStr = "test";
    CMyString str(stlStr);
    REQUIRE(str.GetLength() == 4);
    REQUIRE(str.GetCapacity() == 5);
    REQUIRE(std::strcmp(str.GetStringData(), "test") == 0);
}

TEST_CASE("GetLength") {
    CMyString str("pizza");
    REQUIRE(str.GetLength() == 5);

    CMyString empty;
    REQUIRE(empty.GetLength() == 0);
}

TEST_CASE("GetStringData") {
    CMyString str("pizza");
    REQUIRE(std::strcmp(str.GetStringData(), "pizza") == 0);

    CMyString empty;
    REQUIRE(std::strcmp(empty.GetStringData(), "") == 0);
}

TEST_CASE("SubString") {
    CMyString str("pizza sushi");
    CMyString sub = str.SubString(0, 5);
    REQUIRE(sub.GetLength() == 5);
    REQUIRE(std::strcmp(sub.GetStringData(), "pizza") == 0);

    CMyString sub2 = str.SubString(6, 5);
    REQUIRE(std::strcmp(sub2.GetStringData(), "sushi") == 0);

    REQUIRE_THROWS_AS(str.SubString(100, 10), std::out_of_range);
}

TEST_CASE("Clear") {
    CMyString str("pizza");
    str.Clear();
    REQUIRE(str.GetLength() == 0);
    REQUIRE(std::strcmp(str.GetStringData(), "") == 0);
}

TEST_CASE("operator=") {
    CMyString str1("pizza");
    CMyString str2;
    str2 = str1;
    REQUIRE(str2.GetLength() == 5);
    REQUIRE(std::strcmp(str2.GetStringData(), "pizza") == 0);

    str2 = str2;
    REQUIRE(str2.GetLength() == 5);
    REQUIRE(std::strcmp(str2.GetStringData(), "pizza") == 0);
}

TEST_CASE("move operator=") {
    CMyString str1("pizza");
    CMyString str2;
    str2 = std::move(str1);
    REQUIRE(str2.GetLength() == 5);
    REQUIRE(std::strcmp(str2.GetStringData(), "pizza") == 0);
    REQUIRE(str1.GetLength() == 0);
    REQUIRE(std::strcmp(str1.GetStringData(), "") == 0);
}

TEST_CASE("operator+") {
    CMyString str1("pizza");
    CMyString str2(" sushi");
    CMyString result;
    result = str1 + str2;
    REQUIRE(result.GetLength() == 11);
    REQUIRE(std::strcmp(result.GetStringData(), "pizza sushi") == 0);

    result = str1 + std::string(" sushi");
    REQUIRE(std::strcmp(result.GetStringData(), "pizza sushi") == 0);

    result = str1 + " sushi";
    REQUIRE(std::strcmp(result.GetStringData(), "pizza sushi") == 0);
}

TEST_CASE("operator+=") {
    CMyString str("pizza");
    str += CMyString(" sushi");
    REQUIRE(str.GetLength() == 11);
    REQUIRE(std::strcmp(str.GetStringData(), "pizza sushi") == 0);
}

TEST_CASE("Compare operators") {
    CMyString str1("pizza");
    CMyString str2("pizza");
    CMyString str3("sushi");

    REQUIRE(str1 == str2);
    REQUIRE(str1 != str3);
    REQUIRE(str1 < str3);
    REQUIRE(str3 > str1);
    REQUIRE(str1 <= str2);
    REQUIRE(str1 >= str2);
}

TEST_CASE("Index operator") {
    CMyString str("pizza");
    REQUIRE(str[0] == 'p');
    REQUIRE(str[4] == 'a');

    str[0] = 'P';
    REQUIRE(str[0] == 'P');

    char outOfRange;

    REQUIRE_THROWS_AS(str[5], std::out_of_range);
    REQUIRE_THROWS_AS(outOfRange = str[5], std::out_of_range);
}

TEST_CASE("Const index operator") {
    const CMyString str("pizza");
    REQUIRE(str[0] == 'p');
    REQUIRE(str[4] == 'a');

    REQUIRE_THROWS_AS(str[5], std::out_of_range);
}

TEST_CASE("Stream operators") {
    CMyString str("pizza");

    std::ostringstream os;
    os << str;
    REQUIRE(os.str() == "pizza");

    std::istringstream is("sushi");
    CMyString str2;
    is >> str2;
    REQUIRE(std::strcmp(str2.GetStringData(), "sushi") == 0);
}

TEST_CASE("Ctor with null characters")
{
    const char data[] = { 'a', '\0', 'b', '\0', 'c' };
    CMyString str(data, 5);

    REQUIRE(str.GetLength() == 5);
    REQUIRE(str.GetCapacity() == 6);
    REQUIRE(std::memcmp(str.GetStringData(), data, 5) == 0);
    REQUIRE(str.GetStringData()[5] == '\0');
}

TEST_CASE("Concatenation with null characters")
{
    const char data1[] = { 'x', '\0', 'y' };
    const char data2[] = { 'z', '\0', 'w' };
    CMyString str1(data1, 3);
    CMyString str2(data2, 3);
    CMyString result = str1 + str2;

    const char expected[] = { 'x', '\0', 'y', 'z', '\0', 'w' };
    REQUIRE(result.GetLength() == 6);
    REQUIRE(result.GetCapacity() == 7);
    REQUIRE(std::memcmp(result.GetStringData(), expected, 6) == 0);
    REQUIRE(result.GetStringData()[6] == '\0');
}