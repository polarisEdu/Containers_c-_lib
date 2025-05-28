#include "s21_set.h"

namespace s21 {

// Конструктор по умолчанию
template <typename Key>
Set<Key>::Set() : map_() {}

// Конструктор с инициализатором списка
template <typename Key>
Set<Key>::Set(std::initializer_list<value_type> const& items) {
  for (const auto& item : items) {
    insert(item);
  }
}

// Копирующий конструктор
template <typename Key>
Set<Key>::Set(const Set& other) : map_(other.map_) {}

// Перемещающий конструктор
template <typename Key>
Set<Key>::Set(Set&& other) noexcept : map_(std::move(other.map_)) {}

// Деструктор
template <typename Key>
Set<Key>::~Set() {}

// Оператор присваивания перемещением
template <typename Key>
Set<Key>& Set<Key>::operator=(Set&& other) noexcept {
  if (this != &other) {
    map_ = std::move(other.map_);
  }
  return *this;
}

template <typename Key>
Set<Key>& Set<Key>::operator=(const Set<Key>& other) {
  if (this != &other) {
    map_.clear();  // Clear current map content
    for (const auto& pair : other.map_) {
      map_.insert(pair);  // Insert elements from other's map
    }
  }
  return *this;
}

// Проверка на пустоту
template <typename Key>
bool Set<Key>::empty() const noexcept {
  return map_.empty();
}

// Возвращает количество элементов
template <typename Key>
typename Set<Key>::size_type Set<Key>::size() const noexcept {
  return map_.size();
}

// Возвращает максимальное количество элементов
template <typename Key>
typename Set<Key>::size_type Set<Key>::max_size() const noexcept {
  return map_.max_size();
}

// Очистка множества
template <typename Key>
void Set<Key>::clear() noexcept {
  map_.clear();
}

// Вставка элемента
template <typename Key>
std::pair<typename Set<Key>::iterator, bool> Set<Key>::insert(
    const value_type& value) {
  auto result = map_.insert(std::make_pair(value, value));
  return {result.first, result.second};
}

// Удаление элемента по итератору
template <typename Key>
void Set<Key>::erase(iterator pos) {
  map_.erase(pos);
}

// Обмен содержимым
template <typename Key>
void Set<Key>::swap(Set& other) noexcept {
  map_.swap(other.map_);
}

// Слияние множеств
// Слияние множеств
template <typename Key>
void Set<Key>::merge(Set<Key>& other) {
  map_.merge(other.map_);
  other.map_.clear();  // Optionally clear `other` after merging if desired
}

// Поиск элемента
// Поиск элемента (константная версия)
// Поиск элемента по ключу
template <typename Key>
typename Set<Key>::iterator Set<Key>::find(const Key& key) {
  auto it = map_.begin();
  while (it != map_.end()) {
    if (it->first == key) {  // Сравниваем ключи
      return iterator(it);
    }
    ++it;
  }
  return end();  // Возвращаем итератор на конец, если элемент не найден
}

// // Проверка на наличие элемента
// Проверка на наличие элемента по ключу
template <typename Key>
bool Set<Key>::contains(const Key& key) {
  return find(key) != end();
}

// Итератор на начало множества
template <typename Key>
typename Set<Key>::iterator Set<Key>::begin() noexcept {
  return map_.begin();
}

// Итератор на конец множества
template <typename Key>
typename Set<Key>::iterator Set<Key>::end() noexcept {
  return map_.end();
}

// Явные инстанцирования шаблонов, чтобы избежать ошибок компоновщика
template class Set<int>;
template class Set<double>;
template class Set<std::string>;

}  // namespace s21
