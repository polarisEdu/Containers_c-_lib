#include "../s21_map.h"

#include <gtest/gtest.h>

// Тесты для s21::Map
TEST(MapTest, Constructor) {
  s21::Map<int, std::string> map;
  EXPECT_TRUE(map.empty());
  EXPECT_EQ(map.size(), 0);
}

TEST(MapTest, Insert) {
  s21::Map<int, std::string> map;
  auto result = map.insert({1, "one"});
  EXPECT_TRUE(result.second);
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(map.at(1), "one");
}

TEST(MapTest, At) {
  s21::Map<int, std::string> map;
  map.insert({1, "one"});
  EXPECT_EQ(map.at(1), "one");
  EXPECT_THROW(map.at(2), std::out_of_range);
}

TEST(MapTest, Erase) {
  s21::Map<int, std::string> map;
  map.insert({1, "one"});
  auto it = map.begin();
  map.erase(it);
  EXPECT_TRUE(map.empty());
}

TEST(MapTest, Contains) {
  s21::Map<int, std::string> map;
  map.insert({1, "one"});
  EXPECT_TRUE(map.contains(1));
  EXPECT_FALSE(map.contains(2));
}

// Тестирование begin и end
TEST(MapTest, BeginEnd) {
  s21::Map<int, std::string> map;
  EXPECT_EQ(map.begin(), map.end());
  map.insert({1, "one"});
  EXPECT_NE(map.begin(), map.end());
  EXPECT_EQ(map.begin()->first, 1);
  EXPECT_EQ(map.begin()->second, "one");
}

TEST(MapTest, Iterators) {
  s21::Map<int, std::string> map;
  map.insert({1, "one"});
  map.insert({2, "two"});
  map.insert({3, "three"});

  auto it = map.begin();
  EXPECT_EQ(it->first, 1);
  ++it;
  EXPECT_EQ(it->first, 2);
  ++it;
  EXPECT_EQ(it->first, 3);
  ++it;
  EXPECT_EQ(it, map.end());
}

// Тестирование конструктора копирования
TEST(MapTest, CopyConstructor) {
  s21::Map<int, std::string> map1;
  map1.insert({1, "one"});
  map1.insert({2, "two"});

  s21::Map<int, std::string> map2(map1);
  EXPECT_EQ(map2.size(), 2);
  EXPECT_EQ(map2.at(1), "one");
  EXPECT_EQ(map2.at(2), "two");
}

// Тестирование конструктора перемещения
TEST(MapTest, MoveConstructor) {
  s21::Map<int, std::string> map1;
  map1.insert({1, "one"});
  map1.insert({2, "two"});

  s21::Map<int, std::string> map2(std::move(map1));
  EXPECT_EQ(map2.size(), 2);
  EXPECT_EQ(map2.at(1), "one");
  EXPECT_EQ(map2.at(2), "two");
  EXPECT_TRUE(map1.empty());
}

// Тестирование метода swap
TEST(MapTest, Swap) {
  s21::Map<int, std::string> map1;
  map1.insert({1, "one"});

  s21::Map<int, std::string> map2;
  map2.insert({2, "two"});

  map1.swap(map2);
  EXPECT_EQ(map1.size(), 1);
  EXPECT_EQ(map1.at(2), "two");
  EXPECT_EQ(map2.size(), 1);
  EXPECT_EQ(map2.at(1), "one");
}

// Тестирование метода merge
TEST(MapTest, Merge) {
  s21::Map<int, std::string> map1;
  map1.insert({1, "one"});

  s21::Map<int, std::string> map2;
  map2.insert({2, "two"});

  map1.merge(map2);
  EXPECT_EQ(map1.size(), 2);
  EXPECT_EQ(map1.at(1), "one");
  EXPECT_EQ(map1.at(2), "two");
  EXPECT_TRUE(map2.empty());
}
// Добавьте остальные тесты для s21::Map
