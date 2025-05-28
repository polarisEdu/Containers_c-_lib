#ifndef Containers_List_H
#define Containers_List_H
#include <initializer_list>
#include <stdexcept>

namespace s21 {

template <class MyList>
class ListIterator {
 public:
  using value_type = typename MyList::value_type;

  template <class T>
  friend class List;
  inline ListIterator<MyList>& operator++();
  inline ListIterator<MyList> operator++(int);
  inline ListIterator<MyList>& operator--();
  inline ListIterator<MyList> operator--(int);
  inline typename MyList::value_type& operator*();
  inline bool operator==(const ListIterator<MyList>& rhs);
  inline bool operator!=(const ListIterator<MyList>& rhs);

 protected:
  struct ListEntry {
    ListEntry* fLink;
    ListEntry* bLink;
    typename MyList::value_type entity;
  };
  ListEntry* nodePtr_ = nullptr;
  ListEntry* headPtr_ = nullptr;
  bool isReversed_ = 0;

  ListIterator() {}
  ListIterator(ListEntry* node, ListEntry* head);
};

template <class MyList>
inline ListIterator<MyList>& ListIterator<MyList>::operator++() {
  if (!isReversed_) {
    if (nodePtr_ == headPtr_)
      throw std::runtime_error("cannot increment end list iterator");
  } else if (headPtr_->bLink == nodePtr_)
    throw std::runtime_error("cannot decrement begin list iterator");
  nodePtr_ = nodePtr_->fLink;
  return *this;
}

template <class MyList>
inline ListIterator<MyList> ListIterator<MyList>::operator++(int) {
  ListIterator<MyList> old = *this;
  operator++();
  return old;
}

template <class MyList>
inline ListIterator<MyList>& ListIterator<MyList>::operator--() {
  if (!isReversed_) {
    if (nodePtr_->bLink == headPtr_)
      throw std::runtime_error("cannot decrement begin list iterator");
  } else if (nodePtr_ == headPtr_)
    throw std::runtime_error("cannot increment end list iterator");
  nodePtr_ = nodePtr_->bLink;
  return *this;
}

template <class MyList>
inline ListIterator<MyList> ListIterator<MyList>::operator--(int) {
  ListIterator<MyList> old = *this;
  operator--();
  return old;
}

template <class MyList>
inline typename MyList::value_type& ListIterator<MyList>::operator*() {
  return nodePtr_->entity;
}

template <class MyList>
inline bool ListIterator<MyList>::operator==(const ListIterator<MyList>& rhs) {
  return nodePtr_ == rhs.nodePtr_;
}

template <class MyList>
inline bool ListIterator<MyList>::operator!=(const ListIterator<MyList>& rhs) {
  return nodePtr_ != rhs.nodePtr_;
}

template <class MyList>
ListIterator<MyList>::ListIterator(ListEntry* node, ListEntry* head) {
  nodePtr_ = node;
  headPtr_ = head;
}

template <class MyList>
class ConstListIterator : public ListIterator<MyList> {
 public:
  template <class T>
  friend class List;

  inline const typename MyList::value_type& operator*() const;
  inline ConstListIterator<MyList>& operator++();
  inline ConstListIterator<MyList> operator++(int);
  inline ConstListIterator<MyList>& operator--();
  inline ConstListIterator<MyList> operator--(int);

 private:
  ConstListIterator(typename ListIterator<MyList>::ListEntry* node,
                    typename ListIterator<MyList>::ListEntry* head)
      : ListIterator<MyList>(node, head) {}
};

template <class MyList>
inline const typename MyList::value_type& ConstListIterator<MyList>::operator*()
    const {
  return this->nodePtr_->entity;
}

template <class MyList>
inline ConstListIterator<MyList>& ConstListIterator<MyList>::operator++() {
  this->ListIterator<MyList>::operator++();
  return *this;
}

template <class MyList>
inline ConstListIterator<MyList> ConstListIterator<MyList>::operator++(int) {
  ConstListIterator<MyList> old = *this;
  operator++();
  return old;
}

template <class MyList>
inline ConstListIterator<MyList>& ConstListIterator<MyList>::operator--() {
  this->ListIterator<MyList>::operator--();
  return *this;
}

template <class MyList>
inline ConstListIterator<MyList> ConstListIterator<MyList>::operator--(int) {
  ConstListIterator<MyList> old = *this;
  operator--();
  return old;
}

template <class MyList>
class ReverseListIterator : public ListIterator<MyList> {
 public:
  inline ReverseListIterator<MyList>& operator++();
  inline ReverseListIterator<MyList> operator++(int);
  inline ReverseListIterator<MyList>& operator--();
  inline ReverseListIterator<MyList> operator--(int);

  ReverseListIterator(typename ListIterator<MyList>::ListEntry* node,
                      typename ListIterator<MyList>::ListEntry* head)
      : ListIterator<MyList>(node, head) {
    this->isReversed_ = 1;
  }
};

template <class MyList>
inline ReverseListIterator<MyList>& ReverseListIterator<MyList>::operator++() {
  this->ListIterator<MyList>::operator--();
  return *this;
}

template <class MyList>
inline ReverseListIterator<MyList> ReverseListIterator<MyList>::operator++(
    int) {
  ListIterator<MyList> old = *this;
  operator++();
  return old;
}

template <class MyList>
inline ReverseListIterator<MyList>& ReverseListIterator<MyList>::operator--() {
  this->ListIterator<MyList>::operator++();
  return *this;
}

template <class MyList>
inline ReverseListIterator<MyList> ReverseListIterator<MyList>::operator--(
    int) {
  ListIterator<MyList> old = *this;
  operator--();
  return old;
}

template <class MyList>
class ConstReverseListIterator : public ReverseListIterator<MyList> {
 public:
  template <class T>
  friend class List;

  inline const typename MyList::value_type& operator*() const;
  inline ConstReverseListIterator<MyList>& operator++();
  inline ConstReverseListIterator<MyList> operator++(int);
  inline ConstReverseListIterator<MyList>& operator--();
  inline ConstReverseListIterator<MyList> operator--(int);

 private:
  ConstReverseListIterator(typename ListIterator<MyList>::ListEntry* node,
                           typename ListIterator<MyList>::ListEntry* head)
      : ReverseListIterator<MyList>(node, head) {}
};

template <class MyList>
inline const typename MyList::value_type&
ConstReverseListIterator<MyList>::operator*() const {
  return this->nodePtr_->entity;
}

template <class MyList>
inline ConstReverseListIterator<MyList>&
ConstReverseListIterator<MyList>::operator++() {
  this->ReverseListIterator<MyList>::operator++();
  return *this;
}

template <class MyList>
inline ConstReverseListIterator<MyList>
ConstReverseListIterator<MyList>::operator++(int) {
  ConstReverseListIterator<MyList> old = *this;
  operator++();
  return old;
}

template <class MyList>
inline ConstReverseListIterator<MyList>&
ConstReverseListIterator<MyList>::operator--() {
  this->ReverseListIterator<MyList>::operator--();
  return *this;
}

template <class MyList>
inline ConstReverseListIterator<MyList>
ConstReverseListIterator<MyList>::operator--(int) {
  ConstReverseListIterator<MyList> old = *this;
  operator--();
  return old;
}

template <class T>
class List {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = ListIterator<List<T>>;
  using const_iterator = ConstListIterator<List<T>>;
  using reverse_iterator = ReverseListIterator<List<T>>;
  using const_reverse_iterator = ConstReverseListIterator<List<T>>;
  using size_type = size_t;

  List();
  explicit List(size_type n);
  List(std::initializer_list<T> const& list);
  List(const List& l);
  List(List&& l);
  ~List();
  List& operator=(List&& l);

  inline const_reference front() const;
  inline const_reference back() const;

  inline iterator begin() noexcept;
  inline const_iterator cbegin() const noexcept;
  inline reverse_iterator rbegin() noexcept;
  inline const_reverse_iterator crbegin() const noexcept;
  inline iterator end() noexcept;
  inline const_iterator cend() const noexcept;
  inline reverse_iterator rend() noexcept;
  inline const_reverse_iterator crend() const noexcept;

  inline bool empty() const noexcept;
  inline size_type size() const noexcept { return size_; }
  inline size_type max_size() const noexcept;

  inline void clear() noexcept;
  inline iterator insert(iterator pos, const_reference value) noexcept;
  inline void erase(iterator pos) noexcept;
  inline void push_back(const T& val) noexcept;
  inline void pop_back();
  inline void push_front(const T& val) noexcept;
  inline void pop_front();
  inline void swap(List& other) noexcept;
  void merge(List& other) noexcept;
  inline void splice(const_iterator pos, List& other) noexcept;
  inline void reverse() noexcept;
  void unique() noexcept;
  void sort() noexcept;

  inline void assign(const std::initializer_list<T>& el) noexcept;

 private:
  iterator head_;
  size_type size_ = 0;
};

template <class T>
List<T>::List() {
  head_.nodePtr_ = new typename ListIterator<List<T>>::ListEntry();
  head_.nodePtr_->fLink = head_.nodePtr_;
  head_.nodePtr_->bLink = head_.nodePtr_;
  head_.headPtr_ = head_.nodePtr_;
}

template <class T>
List<T>::List(size_type n) : List<T>::List() {
  for (size_type i = 0; i < n; ++i) push_back(0);
}

template <class T>
List<T>::List(std::initializer_list<T> const& el) : List<T>::List() {
  assign(el);
}

template <class T>
List<T>::List(const List& l) : List<T>::List() {
  for (auto it = l.cbegin(); it != l.cend(); ++it) push_back(*it);
}

template <class T>
List<T>::List(List&& l) : List<T>::List() {
  swap(l);
}

template <class T>
List<T>::~List() {
  clear();
  delete head_.nodePtr_;
}

template <class T>
List<T>& List<T>::operator=(List&& l) {
  if (&l != this) {
    clear();
    swap(l);
  }
  return *this;
}

template <class T>
inline typename List<T>::const_reference List<T>::front() const {
  if (empty()) throw(std::runtime_error("front called on empty list"));
  return *cbegin();
}

template <class T>
inline typename List<T>::const_reference List<T>::back() const {
  if (empty()) throw(std::runtime_error("front called on empty list"));
  return *(--cend());
}

template <class T>
inline typename List<T>::iterator List<T>::begin() noexcept {
  return iterator(head_.nodePtr_->fLink, head_.nodePtr_);
}

template <class T>
inline typename List<T>::const_iterator List<T>::cbegin() const noexcept {
  return const_iterator(head_.nodePtr_->fLink, head_.nodePtr_);
}

template <class T>
inline typename List<T>::reverse_iterator List<T>::rbegin() noexcept {
  return reverse_iterator(head_.nodePtr_->bLink, head_.nodePtr_);
}

template <class T>
inline typename List<T>::const_reverse_iterator List<T>::crbegin()
    const noexcept {
  return const_reverse_iterator(head_.nodePtr_->bLink, head_.nodePtr_);
}

template <class T>
inline typename List<T>::iterator List<T>::end() noexcept {
  return head_;
}

template <class T>
inline typename List<T>::const_iterator List<T>::cend() const noexcept {
  return const_iterator(head_.nodePtr_, head_.nodePtr_);
}

template <class T>
inline typename List<T>::reverse_iterator List<T>::rend() noexcept {
  return reverse_iterator(head_.nodePtr_, head_.nodePtr_);
}

template <class T>
inline typename List<T>::const_reverse_iterator List<T>::crend()
    const noexcept {
  return const_reverse_iterator(head_.nodePtr_, head_.nodePtr_);
}

template <class T>
inline bool List<T>::empty() const noexcept {
  return size_ == 0;
}

template <class T>
inline typename List<T>::size_type List<T>::max_size() const noexcept {
  return ~0ull / (sizeof(typename ListIterator<List<T>>::ListEntry));
}

template <class T>
inline void List<T>::clear() noexcept {
  iterator next = begin();
  while (next != head_) {
    iterator current = next++;
    delete current.nodePtr_;
  }
  size_ = 0;
  head_.nodePtr_->fLink = head_.nodePtr_;
  head_.nodePtr_->bLink = head_.nodePtr_;
}

template <class T>
inline typename List<T>::iterator List<T>::insert(
    typename List<T>::iterator pos,
    typename List<T>::const_reference value) noexcept {
  auto newNode = new typename iterator::ListEntry();
  newNode->fLink = pos.nodePtr_;
  newNode->bLink = pos.nodePtr_->bLink;
  newNode->entity = value;
  pos.nodePtr_->bLink->fLink = newNode;
  pos.nodePtr_->bLink = newNode;
  ++size_;
  return iterator(newNode, head_.nodePtr_);
}

template <class T>
inline void List<T>::erase(typename List<T>::iterator pos) noexcept {
  pos.nodePtr_->fLink->bLink = pos.nodePtr_->bLink;
  pos.nodePtr_->bLink->fLink = pos.nodePtr_->fLink;
  delete pos.nodePtr_;
  --size_;
}

template <class T>
inline void List<T>::push_back(const T& val) noexcept {
  iterator back = end();
  auto newNode = new typename iterator::ListEntry();
  newNode->fLink = back.nodePtr_;
  newNode->bLink = back.nodePtr_->bLink;
  newNode->entity = val;
  back.nodePtr_->bLink->fLink = newNode;
  back.nodePtr_->bLink = newNode;
  ++size_;
}

template <class T>
inline void List<T>::pop_back() {
  if (empty()) throw(std::runtime_error("pop_back called on empty list"));
  erase(--end());
}

template <class T>
inline void List<T>::push_front(const T& val) noexcept {
  iterator back = end();
  auto newNode = new typename iterator::ListEntry();
  newNode->fLink = back.nodePtr_->fLink;
  newNode->bLink = back.nodePtr_;
  newNode->entity = val;
  back.nodePtr_->fLink->bLink = newNode;
  back.nodePtr_->fLink = newNode;
  ++size_;
}

template <class T>
inline void List<T>::pop_front() {
  if (empty()) throw(std::runtime_error("pop_back called on empty list"));
  erase(begin());
}

template <class T>
inline void List<T>::swap(List& other) noexcept {
  std::swap(size_, other.size_);
  std::swap(head_, other.head_);
}

template <class T>
void List<T>::merge(List& other) noexcept {
  if (&other != this) {
    iterator thisIt = begin(), otherIt = other.begin();
    while (otherIt != other.end()) {
      if (thisIt == end() || *thisIt > *otherIt) {
        iterator otherOldIt = otherIt++;
        otherOldIt.nodePtr_->bLink = thisIt.nodePtr_->bLink;
        otherOldIt.nodePtr_->fLink = thisIt.nodePtr_;
        thisIt.nodePtr_->bLink->fLink = otherOldIt.nodePtr_;
        thisIt.nodePtr_->bLink = otherOldIt.nodePtr_;
      } else
        ++thisIt;
    }
    otherIt.nodePtr_->fLink = otherIt.nodePtr_;
    otherIt.nodePtr_->bLink = otherIt.nodePtr_;
    this->size_ = this->size_ + other.size_;
    other.size_ = 0;
  }
}

template <class T>
inline void List<T>::splice(const_iterator pos, List& other) noexcept {
  if (&other != this) {
    iterator it = other.begin();
    while (it != other.end()) {
      iterator cur = it++;
      cur.nodePtr_->fLink = pos.nodePtr_;
      cur.nodePtr_->bLink = pos.nodePtr_->bLink;
      pos.nodePtr_->bLink->fLink = cur.nodePtr_;
      pos.nodePtr_->bLink = cur.nodePtr_;
    }
    it.nodePtr_->fLink = it.nodePtr_;
    it.nodePtr_->bLink = it.nodePtr_;
    this->size_ = this->size_ + other.size_;
    other.size_ = 0;
  }
}

template <class T>
inline void List<T>::reverse() noexcept {
  iterator it = begin(), beg = begin();
  do {
    std::swap(it.nodePtr_->bLink, it.nodePtr_->fLink);
    it.nodePtr_ = it.nodePtr_->bLink;
  } while (it != beg);
}

template <class T>
void List<T>::unique() noexcept {
  for (iterator i = begin(); i != end(); ++i) {
    for (iterator j = i; j != end(); ++j) {
      if (i == j) continue;
      if (*i == *j) {
        iterator del = j--;
        erase(del);
      }
    }
  }
}

template <class T>
void List<T>::sort() noexcept {
  for (iterator i = begin(); i != end();) {
    iterator min = i;
    for (iterator j = i; j != end(); ++j) {
      if (*j < *min) min = j;
    }
    if (i != min) {
      min.nodePtr_->fLink->bLink = min.nodePtr_->bLink;
      min.nodePtr_->bLink->fLink = min.nodePtr_->fLink;
      min.nodePtr_->fLink = i.nodePtr_;
      min.nodePtr_->bLink = i.nodePtr_->bLink;
      i.nodePtr_->bLink->fLink = min.nodePtr_;
      i.nodePtr_->bLink = min.nodePtr_;
    } else
      ++i;
  }
}

template <class T>
inline void List<T>::assign(const std::initializer_list<T>& el) noexcept {
  clear();
  for (const T& val : el) {
    push_back(val);
  }
}

}  // namespace s21

#endif  // !Containers_List_H