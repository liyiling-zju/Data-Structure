#include "RedBlackTree.h"

template <typename T>
RedBlackTree<T>::Node::Node()
{
  parent = left = right = NULL;
};

template <typename T>
RedBlackTree<T>::Node::Node(T _val)
{
  data = _val;
  parent = left = right = NULL;
};

template <typename T>
RedBlackTree<T>::RedBlackTree()
{
  nil = new Node;
  nil->color = BLACK;
  root = nil;
};

template <typename T>
RedBlackTree<T>::RedBlackTree(T _val)
{
  nil = new Node;
  nil->color = BLACK;
  Node* r = new Node;
  r->data = _val;
  r->left = nil;
  r->right = nil;
  r->parent = nil;
  root = r;
  this->root->color = BLACK;
};

template <typename T>
int RedBlackTree<T>::release()
{
  release(root);
  root = nil;
  return 0;
};

template <typename T>
int RedBlackTree<T>::release(Node* _x)
{
  if (_x != nil)
    {
      release(_x->left);
      release(_x->right);
      delete _x;
    }
  return 0;
};

template <typename T>
int RedBlackTree<T>::TreeInsert(Node* _new)
{
  Node* y = this->nil;
  Node* x = this->root;
  // Make sure that _new is a single node binary tree.
  _new->left = _new->right = this->nil;
  while (x != this->nil)
    {
      y = x;
      // The nodes less than to the left, then these greater than or
      // equal to to the right.
      if (_new->data < x->data)
	x = x->left;
      else
	x = x->right;
    }
  _new->parent = y;
  if (y == this->nil)
    this->root = _new;
  // Here the decision rule has to same as above.
  else if (_new->data < y->data)
    y->left = _new;
  else
    y->right = _new;
  return 0;
};

template <typename T>
void RedBlackTree<T>::RightRotate(Node* _x)
{
    Node* y = _x->left;
    _x->left = y->right;
    if (y->right != nil)
	y->right->parent = _x;
    y->parent = _x->parent;
    if (_x->parent == nil)
	root = y;
    // if _x is _x's parent's left child,
    else if (_x == _x->parent->left)
	// set y as _x's parent's left child.
	_x->parent->left = y;
    else
	_x->parent->right = y;
    y->right = _x;
    _x->parent = y;
};

template <typename T>
void RedBlackTree<T>::LeftRotate(Node* _x)
{
    Node* y = _x->right;
    _x->right = y->left;
    if (y->left != nil)
	y->left->parent = _x;
    y->parent = _x->parent;
    if (_x->parent == nil)
	root = y;
    // if _x is _x's parent's left child,
    else if (_x == _x->parent->left)
	// set y as _x's parent's left child.
	_x->parent->left = y;
    else
	_x->parent->right = y;
    y->left = _x;
    _x->parent = y;
};


template <typename T>
int RedBlackTree<T>::insert(Node* _new)
{
  Node* x = _new;
  TreeInsert(x);
  x->color = RED; 
  if (x->parent->color == BLACK)
    {
      this->root->color = BLACK;
      return 0;
    } 
  while (x->parent != this->nil && x->color == RED)
    if (x->parent == x->parent->parent->left)
      {
	// y is the uncle or aunt of x.
	Node* y = x->parent->parent->right;
	// case I:
	if (y->color == RED)
	  {
	    x->parent->color = y->color = BLACK;
	    x->parent->parent->color = RED;
	    x = x->parent->parent;
	    if (x->parent->color == BLACK)
	      break;
	  }
	// y->color == BLACK.
	else
	  {
	    // tortuous...
	    if (x == x->parent->right)
	      {
		// case II:
		this->LeftRotate(x->parent);
		x = x->left;
	      }
	    // case III:
	    this->RightRotate(x->parent->parent);
	    x->parent->color = BLACK;
	    x->parent->right->color = RED;
	    x = x->parent;
	  }
      }
    else if (x->parent == x->parent->parent->right)
      {
	Node* y = x->parent->parent->left;
	// case I:
	if (y->color == RED)
	  {
	    x->parent->color = y->color = BLACK;
	    x->parent->parent->color = RED;
	    x = x->parent->parent;
	    if (x->parent->color == BLACK)
	      break;
	  }
	else
	  {
	    if (x == x->parent->left)
	      {
		// case II:
		this->RightRotate(x->parent);
		x = x->right;
	      }
	    // case III:
	    this->LeftRotate(x->parent->parent);
	    x->parent->color = BLACK;
	    x->parent->left->color = RED;
	    x = x->parent;
	    break;
	  }
      }
  this->root->color = BLACK;
  return 0;
};

template <typename T>
int RedBlackTree<T>::insert(T _d)
{
  Node* t = new Node(_d);
  insert(t);
  return 0;
};


template <typename T>
int RedBlackTree<T>::transplant(Node* _u, Node* _v)
{
  if (_u == nil)
    {
      std::cerr << "Error! Can not transplant to a NULL."
		<< std::endl;
      std::exit(-1);
    }
  if (_u->parent == nil)
    root = _v;   /// Here can not use _u = _v;
  else if (_u == _u->parent->left)
    _u->parent->left = _v;
  else
    _u->parent->right = _v;
  //    if (_v != nil)
  _v->parent = _u->parent;
  return 0;
};


template <typename T>
int RedBlackTree<T>::del(Node* _x)
{
  Node* y = _x;
  bool original_color_y = y->color;
  Node* x;
  if (_x->left == this->nil)
    {
      x = _x->right;
      this->transplant(_x, _x->right);
    }
  else if (_x->right == this->nil)
    {
      x = _x->left;
      this->transplant(_x, _x->left);
    }
  else
    {
      y = this->min(_x->right);
      original_color_y = y->color;
      x = y->right;
      //    	if (y->parent == _x)
      //    	    x->parent = y;
      //    	else
      if (y->parent != _x)
    	{
	  this->transplant(y, y->right);
	  y->right = _x->right;
	  y->right->parent = y;
    	}
      this->transplant(_x, y);
      y->left = _x->left;
      y->left->parent = y;
      y->color = _x->color;
    }
  if (original_color_y == BLACK)
    while (x != this->root && x->color == BLACK)
      if (x == x->parent->left)
	{
	  Node* w = x->parent->right;
	  if (w->color == RED)
	    {
	      w->color = BLACK;
	      x->parent->color = RED;
	      this->LeftRotate(x->parent);
	      w = x->parent->right;
	    }
	  if (w->left->color == BLACK && w->right->color == BLACK)
	    {
	      w->color = RED;
	      x = x->parent;
	    }
	  else
	    {
	      if (w->right->color == BLACK)
		{
		  w->left->color = BLACK;
		  w->color = RED;
		  this->RightRotate(w);
		  w = x->parent->right;
		}
	      w->color = x->parent->color;
	      x->parent->color = BLACK;
	      w->right->color = BLACK;
	      this->LeftRotate(x->parent);
	      // If job finished, but x is not root, set to root
	      // for quitting.
	      x = this->root;
	    }
	}
      else
	{
	  Node* w = x->parent->left;
	  if (w->color == RED)
	    {
	      w->color = BLACK;
	      x->parent->color = RED;
	      this->RightRotate(x->parent);
	      w = x->parent->left;
	    }
	  if (w->right->color == BLACK && w->left->color == BLACK)
	    {
	      w->color = RED;
	      x = x->parent;
	    }
	  else
	    {
	      if (w->left->color == BLACK)
		{
		  w->right->color = BLACK;
		  w->color = RED;
		  this->LeftRotate(w);
		  w = x->parent->left;
		}
	      w->color = x->parent->color;
	      x->parent->color = BLACK;
	      w->left->color = BLACK;
	      this->RightRotate(x->parent);
	      // If job finished, but x is not root, set to root
	      // for quitting.
	      x = this->root;
	    }
	}
  x->color = BLACK;
  delete _x;
  return 0;    
};

template <typename T>
int RedBlackTree<T>::updateDepthandPos(Node* _x, int _d, int _p)
{
  if (_x != nil)
    {
      _x->depth = _d;
      _x->pos = _p;
      updateDepthandPos(_x->left, _d + 1, _p * 2);
      updateDepthandPos(_x->right, _d + 1, _p *2 + 1);
    }
  return 0;
};

template <typename T>
int RedBlackTree<T>::updateDepthandPos()
{
  updateDepthandPos(root, 0, 0);
  return 0;
};



template <typename T>
inline int RedBlackTree<T>::__make_space(int _x) const
{
  for (int i = 0; i < _x; i++)
    std::cout << " ";
  return 0;
};

template <typename T>
inline void RedBlackTree<T>::__make_both_branch(int _x) const
{
  std::cout << "┌";
  for (int i = 0; i < (_x - 3) / 2; i++)
    std::cout << "─";
  std::cout << "┴";
  for (int i = 0; i < (_x - 3) / 2; i++)
    std::cout << "─";
  std::cout << "┐"; 
};

template <typename T>
inline void RedBlackTree<T>::__make_left_branch(int _x) const
{
  std::cout << "┌";
  for (int i = 0; i < (_x - 3) / 2; i++)
    std::cout << "─";
  std::cout << "┘";
  for (int i = 0; i < (_x - 3) / 2; i++)
    std::cout << " ";
  std::cout << " "; 
};

template <typename T>
inline void RedBlackTree<T>::__make_right_branch(int _x) const
{
  std::cout << " ";
  for (int i = 0; i < (_x - 3) / 2; i++)
    std::cout << " ";
  std::cout << "└";
  for (int i = 0; i < (_x - 3) / 2; i++)
    std::cout << "─";
  std::cout << "┐"; 
};

template <typename T>
inline int RedBlackTree<T>::__pow2(int _x) const
{
  return (1 << _x);
};

template <typename T>
int RedBlackTree<T>::display() 
{
  updateDepthandPos();
  // For breadth-first tree walk. 
  std::queue<Node *> val;
  // For print tree.  
  std::queue<Node *> output;	
  // Children status for a node.
  enum ChildCases {LEFT, RIGHT, BOTH, NONE};
  // The children stauts of nodes outputing.
  std::queue<ChildCases> output_cc;
  // Cache the branches between node and its children. 
  std::queue<ChildCases> branch_cache;
  // Cache the nodes for outputing. 
  std::queue<Node *> node_cache; 
  if (root != nil)
    val.push(root);
  else
    {
      std::cout << "The tree is empty." << std::endl;
      return 0;
    }
  // Height of the whole tree. 
  int h = height();
  // Record the nodes number for each tree layer. 
  std::vector<int> counter(h , 0);
  // Count the number of outputed nodes.  
  int count = 0;		
  // In this loop, we use a queue val to apply a breadth-first tree
  // walking and to record the order of nodes ouputing by another
  // queue output. In the same time, we also record the children
  // status of each outputing node by queue output_cc, and the
  // number of nodes to output in each layer of the tree by vector
  // counter.
  while (!val.empty())
    {
      bool left_exist = false;
      bool right_exist = false;
      Node *next = val.front();
      val.pop();
      if (next->left != nil)
	{
	  val.push(next->left);
	  left_exist = true;
	}
      if (next->right != nil)
	{
	  val.push(next->right);
	  right_exist = true;
	}
      if (left_exist && right_exist)
	output_cc.push(BOTH);
      else if (left_exist)
	output_cc.push(LEFT);
      else if (right_exist)
	output_cc.push(RIGHT);
      else
	output_cc.push(NONE);
      output.push(next);
      counter[next->depth]++;
    }
  // Because some of the nodes are missing in an imcomplete tree, so
  // we use the variable off to compute the offset of the display
  // positon for every outputing node. That means we actually print
  // out a complete tree! In some cases, such as each node only has
  // right child, the complexity of this function is 2 to the power
  // of n, which is terrible. However, this function obviously is
  // only for small scale debuging usages.
    
  // Offset of the position to display a node. 
  int off = 0;	
  // In this loop, we actually print the tree by using
  // std::cout. With the branches between nodes and their chidren.
  while (!output.empty())
    {
      Node *next = output.front();
      output.pop();
      // Fill the missing nodes.
      while (off < next->pos)
	{
	  __make_space(__pow2(h - next->depth + 1));
	  off++;
	}
      // Offset for centrally print every node.
      __make_space(__pow2(h - next->depth) - 2);
      if (next->color == RED)
	{
	  std::cout << RC;
	  std::cout << std::setw(3) << std::left << next->data;
	  std::cout << RESET;
	}
      else
	{
	  std::cout << WC;
	  std::cout << std::setw(3) << std::left << next->data;
	  std::cout << RESET;
	}
      __make_space(__pow2(h - next->depth) - 1);
      count++;
      off++;
      // Record the printed node, the children status of these to
      // build the branches between nodes and their childern.
      node_cache.push(next);
      branch_cache.push(output_cc.front());
      output_cc.pop();
      // The first condition means all nodes in this layer have been
      // printed, in the next we should print out a enter to start a
      // newline for branches. And the second condition says if we
      // are in the last layer, we don't do it.
      if (count == counter[next->depth] && next->depth != h - 1)
	{
	  count = 0;
	  off = 0;
	  std::cout << std::endl;
	  while (!branch_cache.empty())
	    {
	      ChildCases cc = branch_cache.front();
	      branch_cache.pop();
	      Node *next = node_cache.front();
	      node_cache.pop();
	      // Again, we need comput the offset for the branches
	      // of those missing node.
	      while (off < next->pos)
		{
		  __make_space(__pow2(h - next->depth + 1));
		  off++;
		}
	      // The offset for centrally print.
	      __make_space(__pow2(h - next->depth - 1) - 2);
	      // Pick the different type of the branches.
	      if (cc == BOTH)
		__make_both_branch(__pow2(h - next->depth) + 1);
	      else if (cc == LEFT)
		__make_left_branch(__pow2(h - next->depth) + 1);
	      else if (cc == RIGHT)
		__make_right_branch(__pow2(h - next->depth) + 1);
	      else if (cc == NONE)
		__make_space(__pow2(h - next->depth) + 1);
	      __make_space(__pow2(h - next->depth - 1) - 2);
	      std::cout << "   ";
	      off++;
	    }
	  off = 0;
	  std::cout << std::endl;
	}
    }
  std::cout << std::endl;
  return 0;
};

template <typename T>
int RedBlackTree<T>::height(const Node *_x) const
{
    if (_x == nil)
	return 0;
    else
	return std::max(height(_x->left), height(_x->right)) + 1;
};

template <typename T>
int RedBlackTree<T>::height() const
{
    return height(root);
};

template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::getRoot()
{
    if (root != nil)
	return root;
    else
	return NULL;
};

template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::min(Node* _x) const
{
  while (_x->left != this->nil)
    _x = _x->left;
  return _x;
};

template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::max(Node* _x) const
{
  while (_x->right != this->nil)
    _x = _x->right;
  return _x;
};
