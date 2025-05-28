#include "../s21_list.h"

#include <gtest/gtest.h>
TEST(ListTest, Constructors) {
  size_t count = 0;
  s21::List<int> l1, l2(5), l3{0, 1, 2, 3, 4, 5};
  ASSERT_EQ(l1.size(), 0);
  ASSERT_EQ(l2.size(), 5);
  ASSERT_EQ(l3.size(), 6);
  for (auto it = l2.cbegin(); it != l2.cend(); ++it) {
    ASSERT_EQ(*it, 0);
    ++count;
  }
  ASSERT_EQ(count, 5);
  count = 0;
  for (auto it = l3.cbegin(); it != l3.cend(); ++it) {
    ASSERT_EQ(*it, count);
    ++count;
  }
  ASSERT_EQ(count, 6);
  s21::List<int> l4(l3), l5(std::move(l2)), l6;
  l6 = std::move(l3);
  ASSERT_EQ(l4.size(), 6);
  ASSERT_EQ(l5.size(), 5);
  ASSERT_EQ(l2.size(), 0);
  ASSERT_TRUE(l2.cbegin() == l2.cend());
  ASSERT_TRUE(l3.cbegin() == l3.cend());
  count = 0;
  for (auto it = l4.cbegin(); it != l4.cend(); ++it) {
    ASSERT_EQ(*it, count);
    ++count;
  }
  ASSERT_EQ(count, 6);
  count = 0;
  for (auto it = l5.cbegin(); it != l5.cend(); ++it) {
    ASSERT_EQ(*it, 0);
    ++count;
  }
  ASSERT_EQ(count, 5);
  count = 0;
  for (auto it = l6.cbegin(); it != l6.cend(); ++it) {
    ASSERT_EQ(*it, count);
    ++count;
  }
  ASSERT_EQ(count, 6);
}

TEST(ListTest, ListElementAccess) {
  s21::List<int> list{1, 2, 3, 4};
  ASSERT_EQ(list.front(), 1);
  ASSERT_EQ(list.back(), 4);
}

TEST(ListTest, ListIterators) {
  s21::List<int> list{0, 1, 2, 3, 4};
  size_t count = 0;
  for (auto it = list.begin(); it != list.end(); ++it) {
    ASSERT_EQ(*it, count);
    *it += 1;
    ++count;
  }
  for (auto it = --list.end(); it != list.begin(); --it) {
    ASSERT_EQ(*it, count);
    --count;
  }
  for (auto it = list.cbegin(); it != list.cend(); ++it) {
    ASSERT_EQ(*it, count);
    ++count;
  }
  count -= 1;
  for (auto it = list.rbegin(); it != list.rend(); ++it) {
    ASSERT_EQ(*it, count);
    --count;
  }
  count += 1;
  for (auto it = --list.rend(); it != list.rbegin(); --it) {
    ASSERT_EQ(*it, count);
    ++count;
  }
  for (auto it = list.crbegin(); it != list.crend(); ++it) {
    ASSERT_EQ(*it, count);
    --count;
  }
}

TEST(ListTest, ListCapacity) {
  s21::List<int> l1, l2{1, 2, 3, 4};
  ASSERT_EQ(l1.empty(), 1);
  ASSERT_EQ(l2.empty(), 0);
  ASSERT_EQ(l1.size(), 0);
  ASSERT_EQ(l2.size(), 4);
  ASSERT_EQ(l1.max_size(), ~0ull / 24);
}

TEST(ListTest, Clear) {
  s21::List<int> list{1, 2, 3, 4};
  list.clear();
  ASSERT_EQ(list.size(), 0);
  ASSERT_TRUE(list.cbegin() == list.cend());
}

TEST(ListTest, Insert) {
  s21::List<int> list{1, 3, 4, 5};
  auto it = ++list.begin();
  auto newPos = list.insert(it, 2);
  ASSERT_EQ(*newPos, 2);
  ASSERT_EQ(list.size(), 5);
  size_t count = 1;
  for (const int& val : list) {
    ASSERT_EQ(val, count);
    count++;
  }
}

TEST(ListTest, Erase) {
  s21::List<int> list{0, 1, 2, 3, 1337};
  list.erase(--list.end());
  ASSERT_EQ(list.size(), 4);
  size_t count = 0;
  for (const int& val : list) {
    ASSERT_EQ(val, count);
    count++;
  }
}

TEST(ListTest, Push_back) {
  s21::List<int> list{0, 1, 2, 3};
  list.push_back(4);
  ASSERT_EQ(list.size(), 5);
  size_t count = 0;
  for (const int& val : list) {
    ASSERT_EQ(val, count);
    count++;
  }
}

TEST(ListTest, Pop_back) {
  s21::List<int> list{0, 1, 2, 3};
  list.pop_back();
  ASSERT_EQ(list.size(), 3);
  size_t count = 0;
  for (const int& val : list) {
    ASSERT_EQ(val, count);
    count++;
  }
}

TEST(ListTest, Push_front) {
  s21::List<int> list{2, 3, 4, 5};
  list.push_front(1);
  ASSERT_EQ(list.size(), 5);
  size_t count = 1;
  for (const int& val : list) {
    ASSERT_EQ(val, count);
    count++;
  }
}

TEST(ListTest, Pop_front) {
  s21::List<int> list{0, 1, 2, 3};
  list.pop_front();
  ASSERT_EQ(list.size(), 3);
  size_t count = 1;
  for (const int& val : list) {
    ASSERT_EQ(val, count);
    count++;
  }
}

TEST(ListTest, Swap) {
  s21::List<int> l1{0, 1, 2, 3}, l2{4, 5};
  l1.swap(l2);
  ASSERT_EQ(l1.size(), 2);
  ASSERT_EQ(l2.size(), 4);
  size_t count = 0;
  for (const int& val : l2) {
    ASSERT_EQ(val, count);
    count++;
  }
  for (const int& val : l1) {
    ASSERT_EQ(val, count);
    count++;
  }
}

TEST(ListTest, Merge) {
  s21::List<int> l1{0, 3, 5, 7, 8}, l2{1, 2, 4, 6, 9, 10};
  l1.merge(l2);
  ASSERT_EQ(l1.size(), 11);
  ASSERT_EQ(l2.size(), 0);
  ASSERT_TRUE(l2.cbegin() == l2.cend());
  size_t count = 0;
  for (const int& val : l1) {
    ASSERT_EQ(val, count);
    count++;
  }
}

TEST(ListTest, Splice) {
  s21::List<int> l1{1, 5}, l2{2, 3, 4};
  l1.splice(++l1.cbegin(), l2);
  ASSERT_EQ(l1.size(), 5);
  ASSERT_EQ(l2.size(), 0);
  ASSERT_TRUE(l2.cbegin() == l2.cend());
  size_t count = 1;
  for (const int& val : l1) {
    ASSERT_EQ(val, count);
    count++;
  }
}

TEST(ListTest, Reverse) {
  s21::List<int> list{1, 2, 3, 4};
  list.reverse();
  size_t count = 4;
  for (const int& val : list) {
    ASSERT_EQ(val, count);
    count--;
  }
}

TEST(ListTest, Unique) {
  s21::List<int> list{1, 1, 1, 2, 3, 4, 5, 6, 5, 2};
  list.unique();
  ASSERT_EQ(list.size(), 6);
  size_t count = 1;
  for (const int& val : list) {
    ASSERT_EQ(val, count);
    count++;
  }
}

TEST(ListTest, Sort) {
  s21::List<int> list{9, 1, 5, 2, 3, 0, 4, 7, 6, 8};
  list.sort();
  size_t count = 0;
  for (const int& val : list) {
    ASSERT_EQ(val, count);
    count++;
  }
}
