#include "BinarySearchTree.h"

int main(int argc, char* argv[])
{
  int B[10] = {11,12,13,14,15,16,17,18,19,20};
  std::cout << "To sort :B = [ ";
  for(int i = 0;i < 10; i++)
    {
      std::cout << B[i] << ' ';
    }
  std::cout << "]" << std::endl;
  //
  BinaryTree<int> A;
  //
  A.RandArray(B,10);
  std::cout << "random B = [ ";
  for(int i = 0;i <10; i++)
    {
      std::cout << B[i] << ' ';
    }
  std::cout << "]" << std::endl;
  //
  for(int i = 0; i < 10; i++) A.insert(B[i]);
  //
  std::cout << "result of BST_Sort:" << std::endl;
  A.inorder_walk();
  A.test();
  return 0;
};
