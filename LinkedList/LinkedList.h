#include <cstdlib>
#include "Node.h"
#include <iostream>

template <typename T>
class LinkedList
{
private:
  Node<T>* head;
public:
  LinkedList();
  ~LinkedList();
  void append(const Node<T>& _node);
  void append(T _val);
  void list() const;
  T pop_front();
  Node<T>* find(T _val) const;
  void del(Node<T>* _add);
  void insert(T _val);
};

template <typename T>
LinkedList<T>::LinkedList()
{
  head = NULL;
};

template <typename T>
LinkedList<T>::~LinkedList()
{
  if (head != NULL)
    {
      Node<T>* p = head;
      while (p->get_next() != NULL)
	{
	  Node<T>* t = p;
	  p = p->get_next();
	  delete t;
	}
      delete p;
    }
};

template <typename T>
void LinkedList<T>::append(const Node<T>& _node)
{
  Node<T>* tail = head;
  Node<T>* p = new Node<T>;
  p->set_data(_node.get_data());
  p->set_next(NULL);
  if (tail != NULL)
    {
      while (tail->get_next() != NULL)
	tail = tail->get_next();
      tail->set_next(p);
    }
  else
    head = p;
};

template <typename T>
void LinkedList<T>::append(T _val)
{
  Node<T>* tail = head;
  Node<T>* p = new Node<T>;
  p->set_data(_val);
  p->set_next(NULL);
  if (tail != NULL)
    {
      while (tail->get_next() != NULL)
	tail = tail->get_next();
      tail->set_next(p);
    }
  else
    head = p;
};

template <typename T>
void LinkedList<T>::list() const
{
  Node<T>* tail = head;
  if (tail != NULL)
    {
      while (tail->get_next() != NULL)
	{
	  std::cout << tail->get_data() << ", ";
	  tail = tail->get_next();
	}
      std::cout << tail->get_data() << std::endl;
    }
};

template <typename T>
T LinkedList<T>::pop_front()
{
  if (head == NULL)
    {
      std::cerr << "Error! Can not pop a data from an empty list." << std::endl;
      return -1;
    }
  Node<T>* p = head;
  T data = p->get_data();
  head = p->get_next();
  delete p;
  return data;
};


template <typename T>
Node<T>* LinkedList<T>::find(T _val) const
{
  Node<T>* p = head;
  Node<T>* t = p;
  if (p == NULL)
    return NULL;
  else if (p->get_data() == _val)
    return NULL;// wait for correcting
  else
    p = p->get_next();
  while (p != NULL){
    if (p->get_data() == _val){
      return t;
      break;
    }
    t = p;
    p = p->get_next();
  }
  return NULL;
};

template <typename T>
void LinkedList<T>::del(Node<T>* _add)
{
  Node<T>* p = head;
  if (p == NULL)
    return;
  while (p->get_next() != NULL){
    if (p == _add){
      p = p->get_next();
      if (p->get_next() != NULL)
	_add->set_next(p->get_next());
      delete p;
      break;
    }
    p = p->get_next();
  }
};

template <typename T>
void LinkedList<T>::insert(T _val)
{
  Node<T>* p = new Node<T>;
  p->set_data(_val);
  p->set_next(NULL);
  if (head == NULL){
    head = p;
    return;
  }
  Node<T>* tail = head;
  Node<T>* t = tail;
  while(p->get_data() >= tail->get_data()){
    if (tail->get_next() != NULL){
      t = tail;
      tail = tail->get_next();
    }
    else{
      tail->set_next(p);
      return;
    }
  }
  t->set_next(p);
  p->set_next(tail);
};
