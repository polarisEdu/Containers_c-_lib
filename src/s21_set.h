#ifndef S21_SET_H_
#define S21_SET_H_

#include <initializer_list>
#include <utility>

#include "s21_map.h"

namespace s21 {

template <typename Key>
class Set {
 public:
  // Типы
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename Map<Key, Key>::iterator;
  using const_iterator = typename Map<Key, Key>::const_iterator;
  using size_type = std::size_t;

  // Конструкторы
  Set();
  Set(std::initializer_list<value_type> const& items);
  Set(const Set& other);
  Set(Set&& other) noexcept;
  ~Set();

  // Операторы
  Set& operator=(
      const Set& other);  // Определение оператора присваивания копированием
  Set& operator=(Set&& other) noexcept;

  // Итераторы
  iterator begin() noexcept;
  iterator end() noexcept;

  // Вместимость
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Модификаторы
  void clear() noexcept;
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(Set& other) noexcept;
  void merge(Set& other);

  // Поиск
  iterator find(const key_type& key);
  bool contains(const key_type& key);

 private:
  Map<key_type, value_type> map_;
};

}  // namespace s21

#endif  // S21_SET_H_
