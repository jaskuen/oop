#include "gtest/gtest.h"
#include "../CStringList/CStringList.h"

class CStringListTest : public testing::Test
{
};

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(CStringListTest, DefaultConstructor) 
{
    CStringList list;
    EXPECT_EQ(list.Size(), 0);
}

TEST_F(CStringListTest, CopyConstructor) 
{
    CStringList list1;
    list1.PushBack("Test1");
    list1.PushBack("Test2");

    CStringList list2(list1);
    EXPECT_EQ(list2.Size(), 2);
    EXPECT_EQ(*list2.begin(), "Test1");
    EXPECT_EQ(*(list2.begin() + 1), "Test2");
}

TEST_F(CStringListTest, MoveConstructor) 
{
    CStringList list1;
    list1.PushBack("Test1");
    list1.PushBack("Test2");

    CStringList list2(std::move(list1));
    EXPECT_EQ(list2.Size(), 2);
    EXPECT_EQ(*list2.begin(), "Test1");
    EXPECT_EQ(*(list2.begin() + 1), "Test2");
    EXPECT_EQ(list1.Size(), 0); // list1 должен быть пуст после перемещения
}

TEST_F(CStringListTest, CopyAssignment) 
{
    CStringList list1;
    list1.PushBack("Test1");
    list1.PushBack("Test2");

    CStringList list2;
    list2 = list1;
    EXPECT_EQ(list2.Size(), 2);
    EXPECT_EQ(*list2.begin(), "Test1");
    EXPECT_EQ(*(list2.begin() + 1), "Test2");
}

TEST_F(CStringListTest, MoveAssignment) 
{
    CStringList list1;
    list1.PushBack("Test1");
    list1.PushBack("Test2");

    CStringList list2;
    list2 = std::move(list1);
    EXPECT_EQ(list2.Size(), 2);
    EXPECT_EQ(*list2.begin(), "Test1");
    EXPECT_EQ(*(list2.begin() + 1), "Test2");
    EXPECT_EQ(list1.Size(), 0); // list1 должен быть пуст после перемещения
}

TEST_F(CStringListTest, PushBack) 
{
    CStringList list;
    list.PushBack("Test1");
    list.PushBack("Test2");

    EXPECT_EQ(list.Size(), 2);
    EXPECT_EQ(*list.begin(), "Test1");
    EXPECT_EQ(*(list.begin() + 1), "Test2");
}

TEST_F(CStringListTest, PushFront) 
{
    CStringList list;
    list.PushFront("Test1");
    list.PushFront("Test2");

    EXPECT_EQ(list.Size(), 2);
    EXPECT_EQ(*list.begin(), "Test2");
    EXPECT_EQ(*(list.begin() + 1), "Test1");
}

TEST_F(CStringListTest, Clear) 
{
    CStringList list;
    list.PushBack("Test1");
    list.PushBack("Test2");

    list.Clear();
    EXPECT_EQ(list.Size(), 0);
}

TEST_F(CStringListTest, Iterators) 
{
    CStringList list;
    list.PushBack("Test1");
    list.PushBack("Test2");

    std::string* it = list.begin();
    EXPECT_EQ(*it, "Test1");
    it++;
    EXPECT_EQ(*it, "Test2");
    EXPECT_EQ(it, list.end() - 1);

    const CStringList constList = list;
    const std::string* cit = constList.cbegin();
    EXPECT_EQ(*cit, "Test1");
    cit++;
    EXPECT_EQ(*cit, "Test2");
    EXPECT_EQ(cit, constList.cend() - 1);
}

TEST_F(CStringListTest, ReverseIterators) 
{
    CStringList list;
    list.PushBack("Test1");
    list.PushBack("Test2");

    std::reverse_iterator<std::string*> rit = list.rbegin();
    EXPECT_EQ(*rit, "Test2");
    rit++;
    EXPECT_EQ(*rit, "Test1");
    EXPECT_EQ(rit, list.rend() - 1);

    const CStringList constList = list;
    std::reverse_iterator<const std::string*> crit = constList.crbegin();
    EXPECT_EQ(*crit, "Test2");
    crit++;
    EXPECT_EQ(*crit, "Test1");
    EXPECT_EQ(crit, constList.crend() - 1);
}

TEST_F(CStringListTest, ExceptionTests) 
{
    CStringList list;
    // Попытка доступа к элементам пустого списка
    EXPECT_THROW(list.begin(), std::out_of_range);
    EXPECT_THROW(list.end(), std::out_of_range);
}