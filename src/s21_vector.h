#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>

namespace s21 {

template <typename T>
class Vector {
 public:
  // Member types
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = std::size_t;

  // Constructors
  Vector();
  explicit Vector(size_type n);
  Vector(std::initializer_list<value_type> const& items);
  Vector(const Vector& v);
  Vector(Vector&& v);
  ~Vector();

  // Operator=
  Vector& operator=(const Vector& v);
  Vector& operator=(Vector&& v);

  // Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  T* data();
  const T* data() const;

  // Iterators
  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  // Capacity
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();

  // Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(Vector& other);

 private:
  T* data_;
  size_type size_;
  size_type capacity_;

  void reallocate(size_type new_capacity);
};

// Implementations

// Constructors
template <typename T>
Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
Vector<T>::Vector(size_type n) : data_(new T[n]()), size_(n), capacity_(n) {}

template <typename T>
Vector<T>::Vector(std::initializer_list<value_type> const& items)
    : data_(new T[items.size()]), size_(items.size()), capacity_(items.size()) {
  std::copy(items.begin(), items.end(), data_);
}

template <typename T>
Vector<T>::Vector(const Vector& v)
    : data_(new T[v.capacity_]), size_(v.size_), capacity_(v.capacity_) {
  std::copy(v.data_, v.data_ + v.size_, data_);
}

template <typename T>
Vector<T>::Vector(Vector&& v)
    : data_(v.data_), size_(v.size_), capacity_(v.capacity_) {
  v.data_ = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;
}

template <typename T>
Vector<T>::~Vector() {
  delete[] data_;
}

// Operator=
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& v) {
  if (this != &v) {
    delete[] data_;
    data_ = new T[v.capacity_];
    size_ = v.size_;
    capacity_ = v.capacity_;
    std::copy(v.data_, v.data_ + v.size_, data_);
  }
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& v) {
  if (this != &v) {
    delete[] data_;
    data_ = v.data_;
    size_ = v.size_;
    capacity_ = v.capacity_;
    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }
  return *this;
}

// Element access
template <typename T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Vector::at: index out of range");
  }
  return data_[pos];
}

template <typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::operator[](size_type pos) const {
  return data_[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::front() const {
  return data_[0];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::back() const {
  return data_[size_ - 1];
}

template <typename T>
T* Vector<T>::data() {
  return data_;
}

template <typename T>
const T* Vector<T>::data() const {
  return data_;
}

// Iterators
template <typename T>
typename Vector<T>::iterator Vector<T>::begin() {
  return data_;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const {
  return data_;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() {
  return data_ + size_;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::end() const {
  return data_ + size_;
}

// Capacity
template <typename T>
bool Vector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::size() const {
  return size_;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::max_size() const {
  return std::numeric_limits<size_type>::max();
}

template <typename T>
void Vector<T>::reserve(size_type new_capacity) {
  if (new_capacity > capacity_) {
    reallocate(new_capacity);
  }
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    reallocate(size_);
  }
}

// Modifiers
template <typename T>
void Vector<T>::clear() {
  for (size_type i = 0; i < size_; ++i) {
    data_[i].~T();
  }
  size_ = 0;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - begin();
  if (size_ >= capacity_) {
    reallocate(capacity_ > 0 ? 2 * capacity_ : 1);
  }
  std::move_backward(begin() + index, end(), end() + 1);
  data_[index] = value;
  ++size_;
  return begin() + index;
}

template <typename T>
void Vector<T>::erase(iterator pos) {
  if (pos >= begin() && pos < end()) {
    pos->~T();
    std::move(pos + 1, end(), pos);
    --size_;
  }
}

template <typename T>
void Vector<T>::push_back(const_reference value) {
  if (size_ >= capacity_) {
    reallocate(capacity_ > 0 ? 2 * capacity_ : 1);
  }
  data_[size_] = value;
  ++size_;
}

template <typename T>
void Vector<T>::pop_back() {
  if (size_ > 0) {
    data_[size_ - 1].~T();
    --size_;
  }
}

template <typename T>
void Vector<T>::swap(Vector& other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

// Private member functions
template <typename T>
void Vector<T>::reallocate(size_type new_capacity) {
  T* new_data = new T[new_capacity];
  std::move(data_, data_ + size_, new_data);
  delete[] data_;
  data_ = new_data;
  capacity_ = new_capacity;
}

}  // namespace s21

#endif  // S21_VECTOR_H
