#include "../s21_set.h"

#include <gtest/gtest.h>

#include <utility>

// Тесты для s21::Set
TEST(SetTest, DefaultConstructor) {
  s21::Set<int> set;
  EXPECT_TRUE(set.empty());
  EXPECT_EQ(set.size(), 0);
}

// Оператор сравнения для сравнения пары <const int, int> с int
bool operator==(const std::pair<const int, int>& lhs, int rhs) {
  return lhs.second == rhs;
}

// Функция для сравнения значения в std::pair<const int, int> с int
bool pairSecondEquals(const std::pair<const int, int>& pair, int value) {
  return pair.second == value;
}

// Тест для вставки элементов в множество
TEST(SetTest, Insert) {
  s21::Set<int> set;

  // Вставляем элемент 1
  auto [it, inserted] = set.insert(1);

  // Проверяем, что элемент успешно вставлен
  EXPECT_TRUE(inserted);
  EXPECT_EQ(set.size(), 1);

  // Проверяем, что множество содержит вставленный элемент
  EXPECT_TRUE(pairSecondEquals(*it, 1));

  // Повторная вставка элемента 1 должна вернуть false
  auto [it2, inserted2] = set.insert(1);

  // Проверяем, что элемент не был вставлен повторно
  EXPECT_FALSE(inserted2);
  EXPECT_EQ(set.size(), 1);

  // Проверяем итераторы (если они поддерживаются)
  auto it_begin = set.begin();
  EXPECT_TRUE(pairSecondEquals(*it_begin, 1));
  ++it_begin;
  EXPECT_EQ(it_begin, set.end());
}

TEST(SetTest, Erase) {
  s21::Set<int> set = {1, 2, 3};
  auto it = set.find(2);
  ASSERT_NE(it, set.end());
  set.erase(it);
  EXPECT_EQ(set.size(), 2);
  EXPECT_FALSE(set.contains(2));
}

TEST(SetTest, Clear) {
  s21::Set<int> set = {1, 2, 3};
  set.clear();
  EXPECT_TRUE(set.empty());
  EXPECT_EQ(set.size(), 0);
}

TEST(SetTest, CopyConstructor) {
  s21::Set<int> set1 = {1, 2, 3};
  s21::Set<int> set2 = set1;
  EXPECT_EQ(set1.size(), set2.size());
  EXPECT_TRUE(std::equal(set1.begin(), set1.end(), set2.begin()));
}

TEST(SetTest, MoveConstructor) {
  s21::Set<int> set1 = {1, 2, 3};
  s21::Set<int> set2 = std::move(set1);
  EXPECT_TRUE(set1.empty());  // set1 должно быть пустым после перемещения
  EXPECT_EQ(set2.size(), 3);
  EXPECT_TRUE(set2.contains(1));
  EXPECT_TRUE(set2.contains(2));
  EXPECT_TRUE(set2.contains(3));
}

TEST(SetTest, CopyAssignmentOperator) {
  s21::Set<int> set1 = {1, 2, 3};
  s21::Set<int> set2;
  set2 = set1;
  EXPECT_EQ(set1.size(), set2.size());
  EXPECT_TRUE(std::equal(set1.begin(), set1.end(), set2.begin()));
}

TEST(SetTest, MoveAssignmentOperator) {
  s21::Set<int> set1 = {1, 2, 3};
  s21::Set<int> set2;
  set2 = std::move(set1);
  EXPECT_TRUE(set1.empty());  // set1 должно быть пустым после перемещения
  EXPECT_EQ(set2.size(), 3);
  EXPECT_TRUE(set2.contains(1));
  EXPECT_TRUE(set2.contains(2));
  EXPECT_TRUE(set2.contains(3));
}

TEST(SetTest, Swap) {
  s21::Set<int> set1 = {1, 2};
  s21::Set<int> set2 = {2, 3};
  set1.swap(set2);

  // Проверяем set1 после обмена
  EXPECT_EQ(set1.size(), 2);
  EXPECT_TRUE(set1.contains(2));
  EXPECT_TRUE(set1.contains(3));

  // Проверяем set2 после обмена
  EXPECT_EQ(set2.size(), 2);
  EXPECT_TRUE(set2.contains(1));
  EXPECT_TRUE(set2.contains(2));

  // Проверяем итераторы (если они поддерживаются)
  auto it1 = set1.begin();
  EXPECT_TRUE(pairSecondEquals(*it1, 2) || pairSecondEquals(*it1, 3));
  ++it1;
  EXPECT_TRUE(pairSecondEquals(*it1, 2) || pairSecondEquals(*it1, 3));
  ++it1;
  EXPECT_EQ(it1, set1.end());

  auto it2 = set2.begin();
  EXPECT_TRUE(pairSecondEquals(*it2, 1) || pairSecondEquals(*it2, 2));
  ++it2;
  EXPECT_TRUE(pairSecondEquals(*it2, 1) || pairSecondEquals(*it2, 2));
  ++it2;
  EXPECT_EQ(it2, set2.end());
}

TEST(SetTest, Merge) {
  s21::Set<int> set1 = {1, 2};
  s21::Set<int> set2 = {2, 3};
  set1.merge(set2);
  EXPECT_EQ(set1.size(), 3);
  EXPECT_TRUE(set1.contains(1));
  EXPECT_TRUE(set1.contains(2));
  EXPECT_TRUE(set1.contains(3));
  EXPECT_TRUE(set2.empty());
}

template <typename Key, typename T>
bool operator==(const std::pair<const Key, T>& lhs, const Key& rhs) {
  return lhs.first == rhs;
}

template <typename Key, typename T>
bool operator==(const Key& lhs, const std::pair<const Key, T>& rhs) {
  return lhs == rhs.first;
}
TEST(SetTest, Find) {
  s21::Set<int> set = {1, 2, 3};
  auto it = set.find(2);
  ASSERT_NE(it, set.end());
  EXPECT_EQ(it->first, 2);  // Сравниваем ключ
}

TEST(SetTest, Contains) {
  s21::Set<int> set = {1, 2, 3};
  EXPECT_TRUE(set.contains(2));
  EXPECT_FALSE(set.contains(4));
}
