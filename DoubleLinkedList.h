#ifndef DOUBLELINKEDLIST_H_INCLUDED
#define DOUBLELINKEDLIST_H_INCLUDED

#include <iostream>

template <typename T>
struct DoubleLinkedListElement {

  DoubleLinkedListElement(T const& _data,
                          DoubleLinkedListElement* _next = nullptr,
                          DoubleLinkedListElement* _prev = nullptr) :
    data(_data), next(_next), prev(_prev) {}

  T data;
  DoubleLinkedListElement *next, *prev;
};

template <typename T>
class DoubleLinkedListIterator;

template <typename T>
class DoubleLinkedList {
public:

  using I = DoubleLinkedListIterator<T>;

private:

  using LLE = DoubleLinkedListElement<T>;

  LLE *front, *back;


  void copy(DoubleLinkedList const& l) {
    for(I it = l.begin(); it; ++it)
      insertEnd(*it);
  }


  void clean() {
    T tmp;
    while(!empty())
      deleteBegin(tmp);
  }

public:


  DoubleLinkedList() : front(nullptr), back(nullptr) {}


  DoubleLinkedList(DoubleLinkedList const& l) : front(nullptr), back(nullptr) {
    copy(l);
  }


  DoubleLinkedList& operator=(DoubleLinkedList const& l) {
    if (this != &l) {
      clean();
      copy(l);
    }
    return *this;
  }


  ~DoubleLinkedList() {
    clean();
  }


  bool empty() const {
    return front == nullptr;
  }


  T& getAt(I it) const {
    return it.get();
  }


  I begin() const {
    return I(front);
  }


  I end() const {
    return I(back);
  }


  void insertBegin(T const& x) {
    insertBefore(x, begin());
  }


  void insertEnd(T const& x) {
    insertAfter(x, end());
  }


  bool deleteBegin(T& x) {
    return deleteAt(x, begin());
  }


  bool deleteEnd(T& x) {
    return deleteAt(x, end());
  }




  bool insertBefore(T const& x, I it) {
    if (it == begin()) {
      LLE* p = new LLE(x, front);
      if (empty())

        back = p;
      else

        front->prev = p;
      front = p;
      return true;
    }

    if (!it || empty())
      return false;

    LLE* p = new LLE(x, it.ptr, it.ptr->prev);
    it.ptr->prev = it.ptr->prev->next = p;
    return true;
   }


  bool insertAfter(T const& x, I it) {
    if (it == end()) {
      LLE* p = new LLE(x, nullptr, back);
      if (empty())
       front = p;
      else
        back->next = p;
      back = p;
      return true;
    }

    if (!it || empty())
      return false;

    LLE* p = new LLE(x, it.ptr->next, it.ptr);
    it.ptr->next = it.ptr->next->prev = p;
    return true;
  }

  bool deleteAt(T& x, I it) {
    if (!it)
      return false;

    x = *it;

    if (it == begin()) {
      front = front->next;
      delete it.ptr;
      if (front == nullptr)
        back = nullptr;
      else
       front->prev = nullptr;
    } else
      if (it == end()) {
        back = back->prev;
        delete it.ptr;
        if (back == nullptr)
          front = nullptr;
        else
          back->next = nullptr;
      } else {
        it.ptr->prev->next = it.ptr->next;
        it.ptr->next->prev = it.ptr->prev;
        delete it.ptr;
      }
    return true;
  }

  bool deleteBefore(T& x, I it) {
    if (!it)
      return false;
    return deleteAt(x, it.prev());
  }

  bool deleteAfter(T& x, I it) {
    if (!it)
      return false;
    return deleteAt(x, it.next());
  }

  void append(DoubleLinkedList& l) {
    if (back != nullptr)
      back->next = l.front;
    else
      front = l.front;

    if (l.back != nullptr) {
      back = l.back;
      l.front->prev = back;
    }
    l.front = l.back = nullptr;
  }


};

template <typename T>
class DoubleLinkedListIterator {
private:

  using LLE = DoubleLinkedListElement<T>;

  LLE* ptr;


public:

  using I = DoubleLinkedListIterator<T>;
  friend class DoubleLinkedList<T>;

  DoubleLinkedListIterator(LLE* _ptr = nullptr) : ptr(_ptr) {}

  I next() const {
    return I(ptr->next);
  }

  I prev() const {
    return I(ptr->prev);
  }

   T& get() const {
    return ptr->data;
  }

  T const& getConst() const;

  bool valid() const {
    return ptr != nullptr;
  }

  bool operator==(I const& it) const {
    return ptr == it.ptr;
  }

  bool operator!=(I const& it) const {
    return !(*this == it);
  }

  T& operator*() const {
    return get();
  }

  I operator++(int) {
    I prev = *this;
    ++(*this);
    return prev;
  }

  I& operator++() {
    return *this = next();
  }

  I operator--(int) {
    I prev = *this;
    --(*this);
    return prev;
  }

  I& operator--() {
    return *this = prev();
  }

  operator bool() const {
    return valid();
  }
};


#endif // DOUBLELINKEDLIST_H_INCLUDED
