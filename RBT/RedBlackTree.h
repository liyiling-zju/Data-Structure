#ifndef __REDBLACKTREE__
#define __REDBLACKTREE__

#include <iostream>
#include <cstdlib>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <vector>
#define BLACK false
#define RED true

#define RESET "\033[0m"
#define RC "\033[31m" /* Red */
#define WC "\033[37m" /* White */



template <typename T>
class RedBlackTree
{
public:
  class Node
  {
  public:
    T data;
    Node* left;    /*Left child.*/
    Node* right;   /*Right child.*/
    Node* parent;  /*Parent.*/
    int depth;     /*Depth of the node.*/
    int pos;       /**/
    bool color = RED;
    Node();
    Node(T _val);
  };
protected:
  Node* root;
  Node* nil;
  inline int __make_space(int _x) const;
  inline void __make_both_branch(int _x) const;
  inline void __make_left_branch(int _x) const;
  inline void __make_right_branch(int _x) const;
  int height(const Node *_x) const;
  int height() const;
public:
  RedBlackTree();
  RedBlackTree(T _val);
  ~RedBlackTree(){ };
  int release();
  int release(Node* _x);
  int TreeInsert(Node* _new);
  void RightRotate(Node* _x);
  void LeftRotate(Node* _x);
  int insert(Node* _new);
  int insert(T _d);
  int transplant(Node* _u, Node* _v);
  int del(Node* _x);
  int updateDepthandPos(Node* _x, int _d, int _p);
  int updateDepthandPos();
  inline int __pow2(int _x) const;
  int display();
  Node* getRoot();
  Node* min(Node* _x) const;
  Node* max(Node* _x) const;
};

#else
//DO NOTHING.
#endif
