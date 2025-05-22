#include <gtest/gtest.h>
#include "../CMyArray/CMyArray.h"

template <typename T>
class CMyArrayTest : public ::testing::Test 
{
};

using TestTypes = ::testing::Types<std::string, float>;
TYPED_TEST_SUITE(CMyArrayTest, TestTypes);

// создавать переменные типа TypeParam и оперировать ими
TYPED_TEST(CMyArrayTest, PushAndSize) {
    CMyArray<TypeParam> arr;
    EXPECT_EQ(arr.Size(), 0);

    arr.Push(TypeParam());
    EXPECT_EQ(arr.Size(), 1);

    arr.Push(TypeParam());
    EXPECT_EQ(arr.Size(), 2);

    arr.Push(TypeParam());
    EXPECT_EQ(arr.Size(), 3);
    EXPECT_EQ(arr.Capacity(), 4);
}

TYPED_TEST(CMyArrayTest, Resize) {
    CMyArray<TypeParam> arr;
    arr.Resize(10);
    EXPECT_EQ(arr.Capacity(), 10);
}

TYPED_TEST(CMyArrayTest, Clear) {
    CMyArray<TypeParam> arr;
    arr.Push(TypeParam());
    arr.Push(TypeParam());
    EXPECT_EQ(arr.Size(), 2);

    arr.Clear();
    EXPECT_EQ(arr.Size(), 0);
}

TYPED_TEST(CMyArrayTest, AccessOperator) {
    CMyArray<TypeParam> arr;
    TypeParam value = TypeParam();
    arr.Push(value);

    EXPECT_EQ(arr[0], value);

    EXPECT_THROW(arr[1], std::out_of_range);
}

TYPED_TEST(CMyArrayTest, CopyConstructor) {
    CMyArray<TypeParam> arr1;
    arr1.Push(TypeParam());
    arr1.Push(TypeParam());

    CMyArray<TypeParam> arr2(arr1);
    EXPECT_EQ(arr2.Size(), arr1.Size());
}

TYPED_TEST(CMyArrayTest, MoveConstructor) {
    CMyArray<TypeParam> arr1;
    arr1.Push(TypeParam());
    arr1.Push(TypeParam());

    CMyArray<TypeParam> arr2(std::move(arr1));
    EXPECT_EQ(arr2.Size(), 2);
    EXPECT_EQ(arr1.Size(), 0);
}

// добавить тесты на копирование/перемещние самого себя
TYPED_TEST(CMyArrayTest, CopyAssignment) {
    CMyArray<TypeParam> arr1;
    arr1.Push(TypeParam());
    arr1.Push(TypeParam());

    CMyArray<TypeParam> arr2;
    arr2 = arr1;
    EXPECT_EQ(arr2.Size(), arr1.Size());
}

TYPED_TEST(CMyArrayTest, MoveAssignment) {
    CMyArray<TypeParam> arr1;
    arr1.Push(TypeParam());
    arr1.Push(TypeParam());

    CMyArray<TypeParam> arr2;
    arr2 = std::move(arr1);
    EXPECT_EQ(arr2.Size(), 2);
    EXPECT_EQ(arr1.Size(), 0);
}

TYPED_TEST(CMyArrayTest, Iterators) {
    CMyArray<TypeParam> arr;
    arr.Push(TypeParam());
    arr.Push(TypeParam());

    auto it = arr.begin();
    EXPECT_NE(it, arr.end());

    auto rit = arr.rbegin();
    EXPECT_NE(rit, arr.rend());

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
