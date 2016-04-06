#pragma once

namespace ptl {

template <typename T>
struct ForwardListNode
{
  using NodePtr = ForwardListNode*;
  NodePtr next;
  T       value;

  void init();
};

template <typename T>
void ForwardListNode<T>::init()
{
  next = nullptr;
}

template <typename T>
class ForwardListIterator
{
  // FRIENDS
    template <typename T1>
    friend bool operator==(ForwardListIterator<T1>,
                           ForwardListIterator<T1>);

public:
  // TYPES
  using NodePtr  = typename ForwardListNode<T>::NodePtr;

  // CREATORS
  ForwardListIterator(NodePtr);

  // METHODS
  ForwardListIterator& operator++();
  T& operator*() const;
  T* operator->() const;
  

private:
  // DATA
  NodePtr d_nodePtr;
};

template <typename T>
bool operator==(ForwardListIterator<T> lhs,
                ForwardListIterator<T> rhs);

template <typename T>
bool operator!=(ForwardListIterator<T> lhs,
                ForwardListIterator<T> rhs);

template <typename T>
class ForwardList
{
public:  
  // TYPES
  using iterator       = ForwardListIterator<T>;
  using const_iterator = ForwardListIterator<const T>;
  using value_type     = T;

  // CREATORS
  ForwardList();

  // MUTATORS
  iterator begin();
  iterator end();

  void push_front(const value_type& t);
  
  // ACCESSORS
  const_iterator begin() const;
  const_iterator end() const;

private:
  // TYPES
  using Node    = ForwardListNode<T>;
  using NodePtr = Node*;

private:
  // DATA
  NodePtr d_nodePtr; // head of list
  NodePtr d_sentinel;
  size_t  d_size;

private:
  // PRIVATE ACCESSORS
  NodePtr head() const;

  // PRIVATE MUTATORS
  size_t& sizeRef();
  void createSentinel();
  void linkNodes(NodePtr prev, NodePtr next);
  NodePtr allocateNode();
  void freeNode(NodePtr ptr);
};

// ITERATOR IMPL

template <typename T>
ForwardListIterator<T>::ForwardListIterator(NodePtr ptr)
  : d_nodePtr(ptr)
{
}

template <typename T>
ForwardListIterator<T>& ForwardListIterator<T>::operator++()
{
    this->d_nodePtr = this->d_nodePtr->next;
    return *this;
}

template <typename T>
T* ForwardListIterator<T>::operator->() const
{
  return &(this->d_nodePtr->value);
}

template <typename T>
T& ForwardListIterator<T>::operator*() const
{
  return this->d_nodePtr->value;
}

template <typename T>
bool operator==(ForwardListIterator<T> lhs,
                ForwardListIterator<T> rhs)
{
  return lhs.d_nodePtr == rhs.d_nodePtr;
}

template <typename T>
bool operator!=(ForwardListIterator<T> lhs,
                ForwardListIterator<T> rhs)
{
  return !(lhs == rhs);
}

// LIST IMPL

template <typename T>
ForwardList<T>::ForwardList()
{
  createSentinel();
  d_nodePtr = d_sentinel;
}

template <typename T>
typename ForwardList<T>::iterator ForwardList<T>::begin()
{
  return iterator(head());
}

template <typename T>
typename ForwardList<T>::const_iterator ForwardList<T>::begin() const
{
  return const_iterator(head());
}

template <typename T>
typename ForwardList<T>::iterator ForwardList<T>::end()
{
  return iterator(d_sentinel);
}

template <typename T>
typename ForwardList<T>::const_iterator ForwardList<T>::end() const
{
  return const_iterator(d_sentinel);
}

template <typename T>
void ForwardList<T>::push_front(const value_type& t)
{
  iterator position(begin());
  NodePtr ptr = allocateNode();
  linkNodes(ptr, d_nodePtr);
  ptr->value = t;
  d_nodePtr  = ptr;
  ++sizeRef();  
}

template <typename T>
size_t& ForwardList<T>::sizeRef()
{
  return d_size;
}

template <typename T>
void ForwardList<T>::linkNodes(NodePtr prev, NodePtr next)
{
  prev->next = next;  
}

template <typename T>
typename ForwardList<T>::NodePtr ForwardList<T>::allocateNode()
{
  NodePtr ptr = new Node;
  ptr->init();
  return ptr;
}

template <typename T>
void ForwardList<T>::freeNode(NodePtr ptr)
{
  delete ptr;
}

template <typename T>
void ForwardList<T>::createSentinel()
{
  d_sentinel = allocateNode();
  linkNodes(d_sentinel, d_sentinel);  // initially circular
  sizeRef() = 0;
}

template <typename T>
typename ForwardList<T>::NodePtr ForwardList<T>::head() const
{
  return d_nodePtr;
}


} // close namespace ptl
