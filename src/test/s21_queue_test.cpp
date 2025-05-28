#include "../s21_queue.h"

#include <gtest/gtest.h>

TEST(QueueTest, Constructors) {
  size_t count = 0;
  s21::Queue<int> q1, q2{0, 1, 2, 3, 4, 5}, q3(q2);
  ASSERT_EQ(q1.size(), 0);
  ASSERT_EQ(q2.size(), 6);
  ASSERT_EQ(q3.size(), 6);
  while (q2.size() > 0) {
    ASSERT_EQ(q2.front(), count);
    q2.pop();
    count++;
  }
  q2.push(1);
  q2.push(2);
  q2.push(3);
  count = 1;
  while (q2.size() > 0) {
    ASSERT_EQ(q2.front(), count);
    q2.pop();
    count++;
  }
  s21::Queue<int> q4(std::move(q3)), q5;
  ASSERT_EQ(q3.size(), 0);
  ASSERT_EQ(q4.size(), 6);
  q5 = std::move(q4);
  ASSERT_EQ(q5.size(), 6);
  count = 0;
  while (q5.size() > 0) {
    ASSERT_EQ(q5.front(), count);
    q5.pop();
    count++;
  }
}

TEST(QueueTest, ElementAccess) {
  s21::Queue<int> q{1, 2, 3, 4};
  ASSERT_EQ(q.front(), 1);
  ASSERT_EQ(q.back(), 4);
}

TEST(QueueTest, QueueCapacity) {
  s21::Queue<int> q1, q2{1, 2, 3, 4};
  ASSERT_EQ(q1.empty(), 1);
  ASSERT_EQ(q2.empty(), 0);
  ASSERT_EQ(q1.size(), 0);
  ASSERT_EQ(q2.size(), 4);
}

TEST(QueueTest, QueueModifiers) {
  s21::Queue<int> q1, q2{1, 2, 3, 4};
  q1.push(1);
  q1.push(2);
  q1.push(3);
  ASSERT_EQ(q1.size(), 3);
  q1.pop();
  ASSERT_EQ(q1.size(), 2);
  q1.swap(q2);
  ASSERT_EQ(q1.size(), 4);
  ASSERT_EQ(q2.size(), 2);
  size_t count = 2;
  while (q2.size() > 0) {
    ASSERT_EQ(q2.front(), count);
    q2.pop();
    count++;
  }
  count = 1;
  while (q1.size() > 0) {
    ASSERT_EQ(q1.front(), count);
    q1.pop();
    count++;
  }
}
