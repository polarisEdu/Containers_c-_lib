#ifndef Containers_Stack_H
#define Containers_Stack_H
#include "s21_list.h"

namespace s21 {

template <class T>
class Stack {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  Stack();
  Stack(std::initializer_list<value_type> const& items);
  Stack(const Stack& s);
  Stack(Stack&& s);
  ~Stack();
  Stack& operator=(Stack&& s);

  inline const_reference top() const;

  inline bool empty() const noexcept;
  inline size_type size() const noexcept;

  inline void push(const_reference value) noexcept;
  inline void pop() noexcept;
  inline void swap(Stack& other) noexcept;

 private:
  s21::List<T> container_;
};

template <class T>
Stack<T>::Stack() {}

template <class T>
Stack<T>::~Stack() {}

template <class T>
Stack<T>::Stack(std::initializer_list<value_type> const& items) {
  container_.assign(items);
}

template <class T>
Stack<T>::Stack(const Stack& s) {
  s21::List<T> buf(s.container_);
  container_.swap(buf);
}

template <class T>
Stack<T>::Stack(Stack&& s) {
  container_.swap(s.container_);
}

template <class T>
Stack<T>& Stack<T>::operator=(Stack&& s) {
  if (&s != this) {
    container_.clear();
    container_.swap(s.container_);
  }
  return *this;
}

template <class T>
inline typename Stack<T>::const_reference Stack<T>::top() const {
  return container_.back();
}
template <class T>
inline bool Stack<T>::empty() const noexcept {
  return container_.empty();
}

template <class T>
inline typename Stack<T>::size_type Stack<T>::size() const noexcept {
  return container_.size();
}

template <class T>
inline void Stack<T>::push(const_reference value) noexcept {
  container_.push_back(value);
}

template <class T>
inline void Stack<T>::pop() noexcept {
  container_.pop_back();
}

template <class T>
inline void Stack<T>::swap(Stack& other) noexcept {
  container_.swap(other.container_);
}
}  // namespace s21

#endif  // !Containers_Stack_H