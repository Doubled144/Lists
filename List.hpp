/*
  Filename   : List.hpp
  Author     : Gary M. Zoppetti, Editedby: Dominic DuRant
  Course     : CSCI 362-01
  Assignment : N/A
  Description: List class, our implementation of a list ADT 
                 using a circular, doubly-linked list.
*/   
/************************************************************/
// Macro guard

#ifndef LIST_HPP
#define LIST_HPP

/************************************************************/
// System includes

#include <iostream>
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <initializer_list>

/************************************************************/
// Local includes

/************************************************************/
// Using declarations

using std::ostream;
using std::ostream_iterator;
using std::initializer_list;
using std::distance;
 

/************************************************************/

template <typename T>
struct ListNode 
{
  ListNode ()
    : data ()
  {
    // Do NOT modify the member initializer list above
    // Make a circular node, with next and prev
    //   pointing to this node
    // TODO
    next = this;
    prev = this; 
  }

  // TODO
  ListNode (const T& d,
	    ListNode* n = nullptr,
	    ListNode* p = nullptr)
    : data (d), next (n), prev (p)
  // Initialize the three data members appropriately
  //   using a member initializer list 
  {
  }

  T          data;
  ListNode*  next;
  ListNode*  prev;
};

/************************************************************/

template <typename T>
struct ListIterator
{
  using Self = ListIterator<T>;
  using Node = ListNode<T>;

  using difference_type = ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;

  using value_type = T;
  using pointer = T*;
  using reference = T&;

  ListIterator ()
    : m_nodePtr ()
  { }

  explicit
  ListIterator (Node* n)
    : m_nodePtr (n) 
  { }

  reference
  operator* () const
  { 
    return m_nodePtr->data;
  }
  
  // Return address of node's data member
  pointer
  operator-> () const
  { 
    return &m_nodePtr->data;
  }
  
  // Pre-increment: TODO
  Self&
  operator++ ()
  {
    // Make the iterator point to the next node
    //   and return the updated iterator
    m_nodePtr = m_nodePtr->next;
    return *this;
  }
  
  // Post-increment
  Self
  operator++ (int)
  {
    Self temp (*this);
    m_nodePtr = m_nodePtr->next;
    return temp;
  }

  // Pre-decrement: TODO
  Self&
  operator-- ()
  {
    // Make the iterator point to the previous node
    //   and return the updated iterator
    m_nodePtr = m_nodePtr->prev;
    return *this;
  }
  
  // Post-decrement
  Self
  operator-- (int)
  {
    Self temp (*this);
    m_nodePtr = m_nodePtr->prev;
    return temp;
  }
  
  bool
  operator== (const Self& i) const
  {
    return m_nodePtr == i.m_nodePtr;
  }
  
  bool
  operator!= (const Self& i) const
  {
    return m_nodePtr != i.m_nodePtr;
  }
  
  /************************************************************/

  Node* m_nodePtr;

};

/************************************************************/

template <typename T>
struct ListConstIterator
{
  using Self = ListConstIterator<T>;
  using Node = const ListNode<T>;
  using iterator = ListIterator<T>;
  
  using difference_type = ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;

  using value_type = T;
  using pointer = const T*;
  using reference = const T&;
  
  ListConstIterator ()
    : m_nodePtr ()
  { }
  
  explicit
  ListConstIterator (Node* n)
    : m_nodePtr (n)
  { }
  
  ListConstIterator (const iterator& i)
    : m_nodePtr (i.m_nodePtr)
  { 
  }
  
  reference
  operator* () const
  { 
    return m_nodePtr->data;
  }
  
  pointer
  operator-> () const
  { 
    return &m_nodePtr->data;
  }

  Self&
  operator++ ()
  {
    m_nodePtr = m_nodePtr->next;
    return *this;
  }
  
  // Post-increment: TODO
  Self
  operator++ (int)
  {
    // Copy the iterator, make it point to the next node,
    //   and return the copied iterator
    Self temp (*this);
    m_nodePtr = m_nodePtr->next;
    return temp;
  }
  
  Self&
  operator-- ()
  {
    m_nodePtr = m_nodePtr->prev;
    return *this;
  }
  
  // Post-decrement: TODO
  Self
  operator-- (int)
  {
    // Analagous to post-increment
    Self temp (*this);
    m_nodePtr = m_nodePtr->prev;
    return temp;
  }
  
  bool
  operator== (const Self& i) const
  { 
    return m_nodePtr == i.m_nodePtr;
  }
  
  bool
  operator!= (const Self& i) const
  { 
    return m_nodePtr != i.m_nodePtr;
  }
  
  /************************************************************/

  Node* m_nodePtr;

};

template <typename T>
bool
operator== (const ListIterator<T>& i1,
	    const ListConstIterator<T>& i2)
{ 
  // Return whether the two iterators refer to the same node
  // TODO
  return i1 == i2;
}

template <typename T>
bool
operator!= (const ListIterator<T>& i1,
	    const ListConstIterator<T>& i2)
{ 
  // Return whether the two iterators refer to different nodes
  // TODO
  return i1 == i2;
}

/************************************************************/

template <typename T>
class List 
{
  using Node = ListNode<T>;

public:

  using iterator       = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;

  using value_type      = T;
  using pointer         = T*;
  using reference       = T&;
  using const_reference = const T&;

  // TODO
  // Initialize an empty list
  List ()
    : m_header (),
      m_size (0)

  // Initialize data members using member initializer list
  {
    // Body should remain EMPTY
  }

  // Initialize a list with the elements in "values",
  //   in the same order
  // Called in cases like this:
  //    List<int> A { 1, 3, 7 };
  List (initializer_list<T> values)
    : m_header (),
      m_size (0)
  {
    // TODO
    // Add all values to this list (preserving order)
    
    for( const auto& elem : values)
      push_back( elem );
  }  


  // Initialize a list of size "n", with each value set to "defValue"
  explicit List (size_t n, const T& defValue = T ())
    : m_header (),
      m_size (n)
  {
    for(size_t i = 0; i <= m_size; ++i)
    {
      this->push_back (defValue);
     // push_back (defValue);
      --i;
    }
   
  }

  // Copy constructor
  //   Initialize this list to be a copy of "otherList"
  List (const List& otherList);

  // Destructor
  ~List ()
  {
    // TODO
    // Remove all dynamically allocated nodes
    while (!empty ())
    {
      pop_front ();
    }
  }

  // Assign "rhs" to this object
  //   Check for self-assignment using standard operator= pattern!
  List&
  operator= (const List& rhs)
  {
    if (this != &rhs)
    {
      // TODO
      for( auto & x : rhs )
      {
        push_back( x );
      }
    }
    return *this;
  }

  // TODO
  // Return whether the list is empty
  bool    
  empty () const
  {
    return m_size == 0;
  }
  
  // TODO
  // Return the size
  size_t
  size ()  const
  {
    return m_size;
  }

  // TODO
  // Return the first element
  reference
  front ()
  {
    return *begin ();
  }

  // TODO
  const_reference
  front () const
  {
    return *begin ();
  }

  // TODO
  // Return the last element
  reference
  back ()
  {
    return *end ();
  }

  // TODO
  const_reference
  back () const
  {
    return *end ();
  }

  // TODO
  // Add "item" to the front of the list
  // MUST be implemented with a one line call to "insert"
  void 
  push_front (const T& item)
  {
    insert (begin (),item);
  }

  // TODO
  // Remove the first element
  // MUST be implemented with a one line call to "erase"
  void
  pop_front  ()
  {
    erase(begin ());
  }

  // TODO
  // Add "item" to the back of the list
  // MUST be implemented with a one line call to "insert"
  void 
  push_back  (const T& item)
  {
    insert(end (), item);
  }

  // TODO
  // Remove the last element
  // MUST be implemented with a one line call to "erase"
  void 
  pop_back   ()
  {
    erase (end ());
  }

  // TODO
  // Return an iterator referencing the first element
  iterator       
  begin ()
  {
    iterator i (m_header.next);
    return i;
  }

  // TODO
  const_iterator 
  begin () const
  {
    iterator i (m_header.next);
    return i;
  }

  // TODO
  // Return an iterator referencing one past the last element,
  //   which will be the header node. 
  iterator       
  end   ()
  {
    iterator j (m_header.prev->next);
    return j;
  }

  // TODO
  const_iterator 
  end   () const
  {
    iterator j (m_header.prev->next);
    return j;
  }  

  // TODO
  // Insert "item" at position "i"
  // Return an iterator referencing the inserted element
  iterator 
  insert (iterator i, const T& item)
  {
    Node *j = i.m_nodePtr;
    Node *newNode = new Node (item, j->prev, j);
    ++m_size;

    j->prev = newNode;
    j->prev->next = newNode ;
    return i--; 
  }

  // TODO
  // Erase element at position "i"
  // Return an iterator referencing the element beyond the one erased
  iterator 
  erase  (iterator i)
  {
    Node *a = i.m_nodePtr;
    iterator value (a->next) ;
    a->prev->next = a->next;
    a->next->prev = a->prev;

    delete a;
    --m_size;

    return value;
  } 

  // TODO
  // Erase elements in the range [i1, i2)
  // Return iterator "i2"
  iterator 
  erase  (iterator i1, iterator i2)
  {
    for ( iterator start = i1; i1 != i2; )
       start = erase (start);

     return i2;
  }
  
private:
  // Dummy header
  Node   m_header;
  size_t m_size;
};

/************************************************************/

// Output operator
// Output "aList" in the format [ e1 e2 e3 ... en ]
//   E.g.: [ 3 8 21 ] for an integer list of size 3
// NOTE CAREFULLY the spacing and LACK of commas
// If you implement this incorrectly MOST of my tests will FAIL!
template <typename T>
ostream&
operator<< (ostream& out, const List<T>& aList)
{
  out << "[ ";
  // Print the elements ...
  // TODO
  for (const auto& elem : aList)
    out << elem << " ";
  out << "]";

  return out;
}

/************************************************************/

#endif

/************************************************************/
