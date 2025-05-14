#include <gtest/gtest.h>
#include "../FindMaxEx/FindMaxEx.h"

class FindMaxExTest : public testing::Test {};

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

struct Athlete
{
    std::string name;
    double height;
    double weight;
};

bool HeightCompare(const Athlete& a, const Athlete& b)
{
    return a.height < b.height;
}

bool WeightCompare(const Athlete& a, const Athlete& b)
{
    return a.weight < b.weight;
}

// Tests
TEST(FindMaxExTest, FindTallestAthlete)
{
    std::vector<Athlete> athletes = {
        {"Athlete1", 123.4, 75.0},
        {"Athlete2", 175.2, 72.0},
        {"Athlete3", 168.7, 78.0}
    };

    Athlete tallest;
    bool result = FindMax(athletes, tallest, HeightCompare);

    ASSERT_TRUE(result);
    EXPECT_EQ(tallest.name, "Athlete2");
    EXPECT_DOUBLE_EQ(tallest.height, 175.2);
    EXPECT_DOUBLE_EQ(tallest.weight, 72.0);
}

TEST(FindMaxExTest, FindHeaviestAthlete)
{
    std::vector<Athlete> athletes = {
        {"Athlete1", 123.4, 75.0},
        {"Athlete2", 175.2, 72.0},
        {"Athlete3", 168.7, 78.0}
    };

    Athlete heaviest;
    bool result = FindMax(athletes, heaviest, WeightCompare);

    ASSERT_TRUE(result);
    EXPECT_EQ(heaviest.name, "Athlete3");
    EXPECT_DOUBLE_EQ(heaviest.height, 168.7);
    EXPECT_DOUBLE_EQ(heaviest.weight, 78.0);
}

TEST(FindMaxExTest, EmptyVectorReturnsFalse)
{
    std::vector<Athlete> emptyAthletes;
    Athlete dummy;

    bool result = FindMax(emptyAthletes, dummy, HeightCompare);
    EXPECT_FALSE(result);
}
