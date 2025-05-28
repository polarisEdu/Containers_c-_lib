#include "../s21_vector.h"

#include <gtest/gtest.h>

// Constructor tests
TEST(VectorTest, DefaultConstructor) {
  s21::Vector<int> vec;
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 0);
  EXPECT_TRUE(vec.empty());
}

TEST(VectorTest, SizeConstructor) {
  s21::Vector<int> vec(5);
  EXPECT_EQ(vec.size(), 5);
  EXPECT_GE(vec.capacity(), 5);
}

TEST(VectorTest, InitializerListConstructor) {
  s21::Vector<int> vec = {1, 2, 3};
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
}

TEST(VectorTest, CopyConstructor) {
  s21::Vector<int> vec1 = {1, 2, 3};
  s21::Vector<int> vec2(vec1);
  EXPECT_EQ(vec2.size(), 3);
  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 2);
  EXPECT_EQ(vec2[2], 3);
}

TEST(VectorTest, MoveConstructor) {
  s21::Vector<int> vec1 = {1, 2, 3};
  s21::Vector<int> vec2(std::move(vec1));
  EXPECT_EQ(vec2.size(), 3);
  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 2);
  EXPECT_EQ(vec2[2], 3);
  EXPECT_EQ(vec1.size(), 0);
}

// Assignment operator tests
TEST(VectorTest, CopyAssignment) {
  s21::Vector<int> vec1 = {1, 2, 3};
  s21::Vector<int> vec2;
  vec2 = vec1;
  EXPECT_EQ(vec2.size(), 3);
  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 2);
  EXPECT_EQ(vec2[2], 3);
}

TEST(VectorTest, MoveAssignment) {
  s21::Vector<int> vec1 = {1, 2, 3};
  s21::Vector<int> vec2;
  vec2 = std::move(vec1);
  EXPECT_EQ(vec2.size(), 3);
  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 2);
  EXPECT_EQ(vec2[2], 3);
  EXPECT_EQ(vec1.size(), 0);
}

// Element access tests
TEST(VectorTest, At) {
  s21::Vector<int> vec = {1, 2, 3};
  EXPECT_EQ(vec.at(1), 2);
  EXPECT_THROW(vec.at(3), std::out_of_range);
}

TEST(VectorTest, OperatorBrackets) {
  s21::Vector<int> vec = {1, 2, 3};
  EXPECT_EQ(vec[1], 2);
}

TEST(VectorTest, Front) {
  s21::Vector<int> vec = {1, 2, 3};
  EXPECT_EQ(vec.front(), 1);
}

TEST(VectorTest, Back) {
  s21::Vector<int> vec = {1, 2, 3};
  EXPECT_EQ(vec.back(), 3);
}

TEST(VectorTest, Data) {
  s21::Vector<int> vec = {1, 2, 3};
  int* data = vec.data();
  EXPECT_EQ(data[0], 1);
  EXPECT_EQ(data[1], 2);
  EXPECT_EQ(data[2], 3);
}

// Iterator tests
TEST(VectorTest, Begin) {
  s21::Vector<int> vec = {1, 2, 3};
  EXPECT_EQ(*vec.begin(), 1);
}

TEST(VectorTest, End) {
  s21::Vector<int> vec = {1, 2, 3};
  EXPECT_EQ(*(vec.end() - 1), 3);
}

// Capacity tests
TEST(VectorTest, Empty) {
  s21::Vector<int> vec;
  EXPECT_TRUE(vec.empty());
}

TEST(VectorTest, Size) {
  s21::Vector<int> vec = {1, 2, 3};
  EXPECT_EQ(vec.size(), 3);
}

TEST(VectorTest, MaxSize) {
  s21::Vector<int> vec;
  EXPECT_GT(vec.max_size(), 0);
}

TEST(VectorTest, Reserve) {
  s21::Vector<int> vec;
  vec.reserve(10);
  EXPECT_GE(vec.capacity(), 10);
}

TEST(VectorTest, Capacity) {
  s21::Vector<int> vec;
  vec.reserve(10);
  EXPECT_EQ(vec.capacity(), 10);
}

TEST(VectorTest, ShrinkToFit) {
  s21::Vector<int> vec = {1, 2, 3};
  vec.reserve(10);
  vec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), 3);
}

// Modifiers tests
TEST(VectorTest, Clear) {
  s21::Vector<int> vec = {1, 2, 3};
  vec.clear();
  EXPECT_EQ(vec.size(), 0);
}

TEST(VectorTest, Insert) {
  s21::Vector<int> vec = {1, 3};
  vec.insert(vec.begin() + 1, 2);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[1], 2);
}

TEST(VectorTest, Erase) {
  s21::Vector<int> vec = {1, 2, 3};
  vec.erase(vec.begin() + 1);
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[1], 3);
}

TEST(VectorTest, PushBack) {
  s21::Vector<int> vec;
  vec.push_back(1);
  EXPECT_EQ(vec.size(), 1);
  EXPECT_EQ(vec[0], 1);
}

TEST(VectorTest, PopBack) {
  s21::Vector<int> vec = {1, 2, 3};
  vec.pop_back();
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec.back(), 2);
}

TEST(VectorTest, Swap) {
  s21::Vector<int> vec1 = {1, 2};
  s21::Vector<int> vec2 = {3, 4};
  vec1.swap(vec2);
  EXPECT_EQ(vec1[0], 3);
  EXPECT_EQ(vec1[1], 4);
  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 2);
}
