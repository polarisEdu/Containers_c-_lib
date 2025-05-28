#include "../s21_stack.h"

#include <gtest/gtest.h>

TEST(StackTest, Constructors) {
  size_t count = 5;
  s21::Stack<int> s1, s2{0, 1, 2, 3, 4, 5}, s3(s2);
  ASSERT_EQ(s1.size(), 0);
  ASSERT_EQ(s2.size(), 6);
  ASSERT_EQ(s3.size(), 6);
  while (s2.size() > 0) {
    ASSERT_EQ(s2.top(), count);
    s2.pop();
    count--;
  }
  s2.push(1);
  s2.push(2);
  s2.push(3);
  count = 3;
  while (s2.size() > 0) {
    ASSERT_EQ(s2.top(), count);
    s2.pop();
    count--;
  }
  s21::Stack<int> s4(std::move(s3)), s5;
  ASSERT_EQ(s3.size(), 0);
  ASSERT_EQ(s4.size(), 6);
  s5 = std::move(s4);
  ASSERT_EQ(s5.size(), 6);
  count = 5;
  while (s5.size() > 0) {
    ASSERT_EQ(s5.top(), count);
    s5.pop();
    count--;
  }
}

TEST(StackTest, ElementAccess) {
  s21::Stack<int> s{1, 2, 3, 4};
  ASSERT_EQ(s.top(), 4);
}

TEST(StackTest, StackCapacity) {
  s21::Stack<int> s1, s2{1, 2, 3, 4};
  ASSERT_EQ(s1.empty(), 1);
  ASSERT_EQ(s2.empty(), 0);
  ASSERT_EQ(s1.size(), 0);
  ASSERT_EQ(s2.size(), 4);
}

TEST(StackTest, StackModifiers) {
  s21::Stack<int> s1, s2{1, 2, 3, 4};
  s1.push(1);
  s1.push(2);
  s1.push(3);
  ASSERT_EQ(s1.size(), 3);
  s1.pop();
  ASSERT_EQ(s1.size(), 2);
  s1.swap(s2);
  ASSERT_EQ(s1.size(), 4);
  ASSERT_EQ(s2.size(), 2);
  size_t count = 2;
  while (s2.size() > 0) {
    ASSERT_EQ(s2.top(), count);
    s2.pop();
    count--;
  }
  count = 4;
  while (s1.size() > 0) {
    ASSERT_EQ(s1.top(), count);
    s1.pop();
    count--;
  }
}
