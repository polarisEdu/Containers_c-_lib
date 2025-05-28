#ifndef S21_MAP_H_
#define S21_MAP_H_
#include <cstddef>
#include <iterator>
#include <limits>
#include <utility>
// #include <stdexcept>
namespace s21 {

template <typename Key, typename T>
class Map {
 public:
  // Типы, определенные внутри класса
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  // Внутренний класс итератора
  class MapIterator;
  using iterator = MapIterator;
  class MapConstIterator;
  using const_iterator = MapConstIterator;

  // Конструкторы и деструктор+
  Map();
  Map(std::initializer_list<value_type> const& items);
  Map(const Map& m);
  Map(Map&& m);
  ~Map();

  Map& operator=(Map&& m);  //+

  // Доступ к элементам+
  T& at(const Key& key);
  T& operator[](const Key& key);

  // Итераторы
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  // Вместимость+
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  // Модификаторы+
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  void erase(iterator pos);
  void swap(Map& other);
  void merge(Map& other);

  // Поиск+
  bool contains(const Key& key) const;

 private:
  // Внутреннее представление бинарного дерева
  struct Node {
    value_type data;
    Node* left;
    Node* right;
    Node* parent;

    Node(const value_type& value)
        : data(value), left(nullptr), right(nullptr), parent(nullptr) {}
  };

  Node* root_;
  size_type size_;

  // Вспомогательные функции+
  void clear(Node* node);
  Node* find_node(const Key& key) const;
  Node* insert_node(Node* node, const value_type& value);
  Node* erase_node(Node* node, const Key& key);
  Node* min_value_node(Node* node) const;
  void transplant(Node* u, Node* v);
};

// Реализация итераторов
template <typename Key, typename T>
class Map<Key, T>::MapIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename Map::value_type;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type*;
  using reference = value_type&;

  MapIterator(Node* node = nullptr) : node_(node) {}

  reference operator*() const { return node_->data; }
  pointer operator->() const { return &(node_->data); }

  MapIterator& operator++();
  MapIterator operator++(int);
  MapIterator& operator--();
  MapIterator operator--(int);

  bool operator==(const MapIterator& other) const {
    return node_ == other.node_;
  }
  bool operator!=(const MapIterator& other) const {
    return node_ != other.node_;
  }

 private:
  Node* node_;
};

template <typename Key, typename T>
class Map<Key, T>::MapConstIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename Map::value_type;
  using difference_type = std::ptrdiff_t;
  using pointer = const value_type*;
  using reference = const value_type&;

  MapConstIterator(Node* node = nullptr) : node_(node) {}

  reference operator*() const { return node_->data; }
  pointer operator->() const { return &(node_->data); }

  MapConstIterator& operator++();
  MapConstIterator operator++(int);
  MapConstIterator& operator--();
  MapConstIterator operator--(int);

  bool operator==(const MapConstIterator& other) const {
    return node_ == other.node_;
  }
  bool operator!=(const MapConstIterator& other) const {
    return node_ != other.node_;
  }

 private:
  Node* node_;
};

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::begin() {
  return iterator(min_value_node(root_));
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::end() {
  return iterator(nullptr);
}

template <typename Key, typename T>
typename Map<Key, T>::const_iterator Map<Key, T>::begin() const {
  return const_iterator(min_value_node(root_));
}

template <typename Key, typename T>
typename Map<Key, T>::const_iterator Map<Key, T>::end() const {
  return const_iterator(nullptr);
}
// Конструкторы и деструктор

template <typename Key, typename T>
Map<Key, T>::Map() : root_(nullptr), size_(0) {}

template <typename Key, typename T>
Map<Key, T>::Map(std::initializer_list<value_type> const& items) : Map() {
  for (auto& item : items) {
    insert(item);
  }
}

template <typename Key, typename T>
Map<Key, T>::Map(const Map& m) : Map() {
  for (auto it = m.begin(); it != m.end(); ++it) {
    insert(*it);
  }
}

template <typename Key, typename T>
Map<Key, T>::Map(Map&& m) : root_(m.root_), size_(m.size_) {
  m.root_ = nullptr;
  m.size_ = 0;
}

template <typename Key, typename T>
Map<Key, T>::~Map() {
  clear();
}

template <typename Key, typename T>
Map<Key, T>& Map<Key, T>::operator=(Map&& m) {
  if (this != &m) {
    clear();
    root_ = m.root_;
    size_ = m.size_;
    m.root_ = nullptr;
    m.size_ = 0;
  }
  return *this;
}

// Доступ к элементам

template <typename Key, typename T>
T& Map<Key, T>::at(const Key& key) {
  Node* node = find_node(key);
  if (!node) {
    throw std::out_of_range("Key not found");
  }
  return node->data.second;
}

template <typename Key, typename T>
T& Map<Key, T>::operator[](const Key& key) {
  auto result = insert(std::make_pair(key, T()));
  return result.first->second;
}

// Вместимость

template <typename Key, typename T>
bool Map<Key, T>::empty() const {
  return size_ == 0;
}

template <typename Key, typename T>
typename Map<Key, T>::size_type Map<Key, T>::size() const {
  return size_;
}

template <typename Key, typename T>
typename Map<Key, T>::size_type Map<Key, T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(Node);
}

// Модификаторы

template <typename Key, typename T>
void Map<Key, T>::clear() {
  clear(root_);
  root_ = nullptr;
  size_ = 0;
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const value_type& value) {
  if (root_ == nullptr) {
    root_ = new Node(value);
    ++size_;
    return std::make_pair(iterator(root_), true);
  } else {
    Node* node = insert_node(root_, value);
    if (node) {
      ++size_;
      return std::make_pair(iterator(node), true);
    } else {
      return std::make_pair(iterator(find_node(value.first)), false);
    }
  }
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const Key& key, const T& obj) {
  return insert(std::make_pair(key, obj));
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert_or_assign(
    const Key& key, const T& obj) {
  auto result = insert(std::make_pair(key, obj));
  if (!result.second) {
    result.first->second = obj;
  }
  return result;
}

template <typename Key, typename T>
void Map<Key, T>::erase(iterator pos) {
  if (pos == end()) return;
  root_ = erase_node(root_, pos->first);
  --size_;
}

template <typename Key, typename T>
void Map<Key, T>::swap(Map& other) {
  std::swap(root_, other.root_);
  std::swap(size_, other.size_);
}

template <typename Key, typename T>
void Map<Key, T>::merge(Map& other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }
  other.clear();
}

// Поиск

template <typename Key, typename T>
bool Map<Key, T>::contains(const Key& key) const {
  return find_node(key) != nullptr;
}

// Вспомогательные функции

template <typename Key, typename T>
void Map<Key, T>::clear(Node* node) {
  if (node) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

template <typename Key, typename T>
typename Map<Key, T>::Node* Map<Key, T>::find_node(const Key& key) const {
  Node* current = root_;
  while (current) {
    if (key == current->data.first) {
      return current;
    } else if (key < current->data.first) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return nullptr;
}

template <typename Key, typename T>
typename Map<Key, T>::Node* Map<Key, T>::insert_node(Node* node,
                                                     const value_type& value) {
  if (value.first == node->data.first) {
    return nullptr;
  } else if (value.first < node->data.first) {
    if (node->left) {
      return insert_node(node->left, value);
    } else {
      node->left = new Node(value);
      node->left->parent = node;
      return node->left;
    }
  } else {
    if (node->right) {
      return insert_node(node->right, value);
    } else {
      node->right = new Node(value);
      node->right->parent = node;
      return node->right;
    }
  }
}
template <typename Key, typename T>
typename Map<Key, T>::Node* Map<Key, T>::erase_node(Node* node,
                                                    const Key& key) {
  if (node == nullptr) {
    return node;  // Узел не найден
  }
  if (key < node->data.first) {
    node->left = erase_node(node->left, key);
  } else if (key > node->data.first) {
    node->right = erase_node(node->right, key);
  } else {
    if (node->left == nullptr) {
      Node* right_child = node->right;
      transplant(node, right_child);
      delete node;
      return right_child;
    } else if (node->right == nullptr) {
      Node* left_child = node->left;
      transplant(node, left_child);
      delete node;
      return left_child;
    } else {
      Node* successor = min_value_node(node->right);
      if (successor->parent != node) {
        transplant(successor, successor->right);
        successor->right = node->right;
        successor->right->parent = successor;
      }
      transplant(node, successor);
      successor->left = node->left;
      successor->left->parent = successor;
      delete node;
      return successor;
    }
  }
  return node;
}

template <typename Key, typename T>
typename Map<Key, T>::Node* Map<Key, T>::min_value_node(Node* node) const {
  Node* current = node;
  while (current && current->left) {
    current = current->left;
  }
  return current;
}

template <typename Key, typename T>
void Map<Key, T>::transplant(Node* u, Node* v) {
  if (!u->parent) {
    root_ = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  if (v) {
    v->parent = u->parent;
  }
}

// Реализация итераторов

template <typename Key, typename T>
typename Map<Key, T>::MapIterator& Map<Key, T>::MapIterator::operator++() {
  if (node_->right) {
    node_ = node_->right;
    while (node_->left) {
      node_ = node_->left;
    }
  } else {
    Node* parent = node_->parent;
    while (parent && node_ == parent->right) {
      node_ = parent;
      parent = parent->parent;
    }
    node_ = parent;
  }
  return *this;
}

template <typename Key, typename T>
typename Map<Key, T>::MapIterator Map<Key, T>::MapIterator::operator++(int) {
  MapIterator tmp = *this;
  ++(*this);
  return tmp;
}

template <typename Key, typename T>
typename Map<Key, T>::MapIterator& Map<Key, T>::MapIterator::operator--() {
  if (node_->left) {
    node_ = node_->left;
    while (node_->right) {
      node_ = node_->right;
    }
  } else {
    Node* parent = node_->parent;
    while (parent && node_ == parent->left) {
      node_ = parent;
      parent = parent->parent;
    }
    node_ = parent;
  }
  return *this;
}

template <typename Key, typename T>
typename Map<Key, T>::MapIterator Map<Key, T>::MapIterator::operator--(int) {
  MapIterator tmp = *this;
  --(*this);
  return tmp;
}

template <typename Key, typename T>
typename Map<Key, T>::MapConstIterator&
Map<Key, T>::MapConstIterator::operator++() {
  if (node_->right) {
    node_ = node_->right;
    while (node_->left) {
      node_ = node_->left;
    }
  } else {
    Node* parent = node_->parent;
    while (parent && node_ == parent->right) {
      node_ = parent;
      parent = parent->parent;
    }
    node_ = parent;
  }
  return *this;
}

template <typename Key, typename T>
typename Map<Key, T>::MapConstIterator
Map<Key, T>::MapConstIterator::operator++(int) {
  MapConstIterator tmp = *this;
  ++(*this);
  return tmp;
}

template <typename Key, typename T>
typename Map<Key, T>::MapConstIterator&
Map<Key, T>::MapConstIterator::operator--() {
  if (node_->left) {
    node_ = node_->left;
    while (node_->right) {
      node_ = node_->right;
    }
  } else {
    Node* parent = node_->parent;
    while (parent && node_ == parent->left) {
      node_ = parent;
      parent = parent->parent;
    }
    node_ = parent;
  }
  return *this;
}

template <typename Key, typename T>
typename Map<Key, T>::MapConstIterator
Map<Key, T>::MapConstIterator::operator--(int) {
  MapConstIterator tmp = *this;
  --(*this);
  return tmp;
}

}  // namespace s21

#endif  // S21_MAP_H_
