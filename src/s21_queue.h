#ifndef Containers_Queue_H
#define Containers_Queue_H
#include "s21_list.h"

namespace s21 {

template <class T>
class Queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  Queue();
  Queue(std::initializer_list<value_type> const& items);
  Queue(const Queue& q);
  Queue(Queue&& q);
  ~Queue();
  Queue& operator=(Queue&& q);

  inline const_reference front() const;
  inline const_reference back() const;

  inline bool empty() const noexcept;
  inline size_type size() const noexcept;

  inline void push(const_reference value) noexcept;
  inline void pop() noexcept;
  inline void swap(Queue& other) noexcept;

 private:
  s21::List<T> container_;
};

template <class T>
Queue<T>::Queue() {}

template <class T>
Queue<T>::~Queue() {}

template <class T>
Queue<T>::Queue(std::initializer_list<value_type> const& items) {
  container_.assign(items);
}

template <class T>
Queue<T>::Queue(const Queue& q) {
  s21::List<T> buf(q.container_);
  container_.swap(buf);
}

template <class T>
Queue<T>::Queue(Queue&& q) {
  container_.swap(q.container_);
}

template <class T>
Queue<T>& Queue<T>::operator=(Queue&& q) {
  if (&q != this) {
    container_.clear();
    container_.swap(q.container_);
  }
  return *this;
}

template <class T>
inline typename Queue<T>::const_reference Queue<T>::front() const {
  return container_.front();
}

template <class T>
inline typename Queue<T>::const_reference Queue<T>::back() const {
  return container_.back();
}
template <class T>
inline bool Queue<T>::empty() const noexcept {
  return container_.empty();
}

template <class T>
inline typename Queue<T>::size_type Queue<T>::size() const noexcept {
  return container_.size();
}

template <class T>
inline void Queue<T>::push(const_reference value) noexcept {
  container_.push_back(value);
}

template <class T>
inline void Queue<T>::pop() noexcept {
  container_.pop_front();
}

template <class T>
inline void Queue<T>::swap(Queue& other) noexcept {
  container_.swap(other.container_);
}
}  // namespace s21

#endif  // !Containers_Queue_H