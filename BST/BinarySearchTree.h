#include <iostream>
#include <cstdlib>

template <typename T>
class BinaryTree
{
private:
  class Node
  {
  public:
    T data;
    Node* lc;
    Node* rc;
    Node* parent;
    Node(T _data);
  };
  Node* root;
  void inorder_walk(Node* _x) const; //start from x.
  void release(Node* _x); //for deconstructor.
  void transplant(Node* u, Node* v);
public:
  BinaryTree() {root = NULL;};
  BinaryTree(T _data);
  ~BinaryTree();
  Node* min(Node* _x) const;
  Node* max(Node* _x) const;
  Node* tree_search(Node* _x, T _data);
  void tree_delete(Node* _x);
  void insert(T _data);
  Node* successor(Node* _x) const;
  Node* predecessor(Node* _x) const;
  void inorder_walk() const; //start from root.
  void RandArray(T* A, int n);
  void test();
};

template <typename T>
void BinaryTree<T>::release(Node* _x)
{
  if (_x != NULL)
    {
      release(_x->lc);
      release(_x->rc);
      delete _x;
    }	
};

template <typename T>
BinaryTree<T>::~BinaryTree()
{
  release(root);
};

template <typename T>
BinaryTree<T>::Node::Node(T _data)
{
  data = _data;
  parent = lc = rc = NULL;
};

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::successor(Node* _x) const
{
  if(_x == NULL)
    {
      std::cout << "Can't find the successor of a NULL pointer!" << std::endl;
      return NULL;
    }
  Node* x = _x;
  if (x->rc != NULL)
    return min(x->rc);
  Node* y = x->parent;
  while (y != NULL && x == y->rc)
    {
      x = y;
      y = y->parent;
    }
  return y;
};

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::min(Node* _x) const
{
  while (_x->lc != NULL)
    _x = _x->lc;
  return _x;
};

template  <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::predecessor(Node* _x) const
{
  if(_x == NULL)
    {
      std::cout << "Can't find the predecessor of a NULL pointer!" << std::endl;
      return NULL;
    }
  Node* x = _x;
  if (x->lc != NULL)
    return max(x->lc);
  Node* y = x->parent;
  while (y != NULL && x == y->lc)
    {
      x = y;
      y = y->parent;
    }
  return y;
};

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::max(Node* _x) const
{
  while (_x->rc != NULL)
    _x = _x->rc;
  return _x;
};

template <typename T>
void BinaryTree<T>::inorder_walk() const
{
  inorder_walk(root);
  std::cout << std::endl;
};

template <typename T>
void BinaryTree<T>::inorder_walk(Node* _x) const
{
  if (_x != NULL)
    {
      inorder_walk(_x->lc);
      std::cout << _x->data << "\t";
      inorder_walk(_x->rc);
    }
};

template <typename T>
void BinaryTree<T>::insert(T _data)
{
  Node* y = NULL;
  Node* x = root;
  Node* p = new Node(_data);
  while (x != NULL)
    {
      y = x;
      if (p->data  < x->data)
	x = x->lc;
      else
	x = x->rc;
    }
  p->parent = y;
  if (y == NULL)
    root = p;
  else if (p->data < y->data)
    y->lc = p;
  else
    y->rc = p;
};

template <typename T>
BinaryTree<T>::BinaryTree(T _data)
{
  Node* p = new Node(_data);
  if (root == NULL)
    root = p;
};

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::tree_search(Node* _x, T _data)
{
  while(_x != NULL && _data != _x->data)
    {
      if( _data < _x->data)
	_x = _x->lc;
      else
	_x = _x->rc;
    }
  return _x;
};

template <typename T>
void BinaryTree<T>::tree_delete(Node* _x)
{
  if(_x == NULL)
    {
      std::cout << "Can't delete a NULL pointer!" << std::endl;
      return;
    }
  if(_x->lc == NULL)
    transplant(_x, _x->rc);
  else if(_x->rc == NULL)
    transplant(_x, _x->lc);
  else
    {
      Node* y = min(_x->rc);
      if(y->parent != _x)
	{
	  transplant(y, y->rc);
	  y->rc = _x->rc;
	  y->rc->parent = y;
	}
      transplant(_x, y);
      y->lc = _x->lc;
      y->lc->parent = y;
    }
};

template <typename T>
void BinaryTree<T>::transplant(Node* u, Node* v)
{
  if(u->parent == NULL)
    root = v;
  else if(u == u->parent->lc)
    u->parent->lc = v;
  else
    u->parent->rc = v;
  if(v != NULL)
    v->parent = u->parent;
};

template <typename T>
void BinaryTree<T>::RandArray(T* A, int n)
{
  T a;
  int x;
  //srand(time(NULL));
  for(int i = 0; i < n; i++)
    {
      x=rand() % n;
      a = A[i];
      A[i] = A[x];
      A[x] = a;
    }
};

template <typename T>
void BinaryTree<T>::test()
{
  std::cout << "min(root) = " << min(root)->data << std::endl;
  std::cout << "max(root) = " << max(root)->data << std::endl;
  std::cout << "successor(root): " << successor(root)->data << std::endl;
  std::cout << "predecessor(root): " << predecessor(root)->data << std::endl;
  std::cout << "tree_search(root,12): " << tree_search(root,(T)12) << std::endl;
  tree_delete(root->lc);
  std::cout << "after tree_delete(root->lc): " << std::endl;
  inorder_walk();
};
