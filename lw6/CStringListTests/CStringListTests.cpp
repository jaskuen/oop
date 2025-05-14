#include "gtest/gtest.h"
#include "../CStringList/CStringList.h"

class CStringListTest : public testing::Test {};

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

    auto it = list2.begin();
    EXPECT_EQ(*it, "Test1");
    ++it;
    EXPECT_EQ(*it, "Test2");
}

TEST_F(CStringListTest, MoveConstructor)
{
    CStringList list1;
    list1.PushBack("Test1");
    list1.PushBack("Test2");

    CStringList list2(std::move(list1));
    EXPECT_EQ(list2.Size(), 2);

    auto it = list2.begin();
    EXPECT_EQ(*it, "Test1");
    ++it;
    EXPECT_EQ(*it, "Test2");

    EXPECT_EQ(list1.Size(), 0); // После перемещения
}

TEST_F(CStringListTest, CopyAssignment)
{
    CStringList list1;
    list1.PushBack("Test1");
    list1.PushBack("Test2");

    CStringList list2;
    list2 = list1;
    EXPECT_EQ(list2.Size(), 2);

    auto it = list2.begin();
    EXPECT_EQ(*it, "Test1");
    ++it;
    EXPECT_EQ(*it, "Test2");
}

TEST_F(CStringListTest, MoveAssignment)
{
    CStringList list1;
    list1.PushBack("Test1");
    list1.PushBack("Test2");

    CStringList list2;
    list2 = std::move(list1);
    EXPECT_EQ(list2.Size(), 2);

    auto it = list2.begin();
    EXPECT_EQ(*it, "Test1");
    ++it;
    EXPECT_EQ(*it, "Test2");

    EXPECT_EQ(list1.Size(), 0); // После перемещения
}

TEST_F(CStringListTest, PushBack)
{
    CStringList list;
    list.PushBack("Test1");
    list.PushBack("Test2");

    EXPECT_EQ(list.Size(), 2);

    auto it = list.begin();
    EXPECT_EQ(*it, "Test1");
    ++it;
    EXPECT_EQ(*it, "Test2");
}

TEST_F(CStringListTest, PushFront)
{
    CStringList list;
    list.PushFront("Test1");
    list.PushFront("Test2");

    EXPECT_EQ(list.Size(), 2);

    auto it = list.begin();
    EXPECT_EQ(*it, "Test2");
    ++it;
    EXPECT_EQ(*it, "Test1");
}

TEST_F(CStringListTest, Clear)
{
    CStringList list;
    list.PushBack("Test1");
    list.PushBack("Test2");

    list.Clear();
    EXPECT_EQ(list.Size(), 0);
    EXPECT_EQ(list.begin(), list.end());
}

TEST_F(CStringListTest, Iterators)
{
    CStringList list;
    list.PushBack("Test1");
    list.PushBack("Test2");

    auto it = list.begin();
    EXPECT_EQ(*it, "Test1");
    ++it;
    EXPECT_EQ(*it, "Test2");

    auto end = list.end();
    it++;
    EXPECT_EQ(it, end);

    const CStringList constList = list;
    auto cit = constList.cbegin();
    EXPECT_EQ(*cit, "Test1");
    ++cit;
    EXPECT_EQ(*cit, "Test2");
}

TEST_F(CStringListTest, ReverseIterators)
{
    CStringList list;
    list.PushBack("Test1");
    list.PushBack("Test2");

    auto rit = list.rbegin();
    EXPECT_EQ(*rit, "Test2");
    ++rit;
    EXPECT_EQ(*rit, "Test1");

    auto rend = list.rend();
    rit++;
    EXPECT_EQ(rit, rend);

    const CStringList constList = list;
    auto crit = constList.crbegin();
    EXPECT_EQ(*crit, "Test2");
    ++crit;
    EXPECT_EQ(*crit, "Test1");
    crit++;
    EXPECT_EQ(crit, constList.crend());
}

TEST_F(CStringListTest, InsertByIterator)
{
    CStringList list;
    list.PushBack("A");
    list.PushBack("C");

    auto it = list.begin();
    ++it; // указывает на "C"
    list.Insert(it, "B"); // между A и C

    auto iter = list.begin();
    EXPECT_EQ(*iter, "A");
    ++iter;
    EXPECT_EQ(*iter, "B");
    ++iter;
    EXPECT_EQ(*iter, "C");
}

TEST_F(CStringListTest, InsertAtIteratorPosition)
{
    CStringList list;
    list.PushBack("A");
    list.PushBack("B");
    list.PushBack("D");

    auto it = list.begin();
    it++; // -> "B"
    it++; // -> "D"

    list.Insert(it, "C");
    
    std::vector<std::string> expected = { "A", "B", "C", "D" };
    size_t i = 0;
    for (auto str : list)
    {
        EXPECT_EQ(str, expected[i++]);
    }

    EXPECT_EQ(list.Size(), 4);
}

