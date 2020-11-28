#include "LinkedList.h"
#include <iostream>


int main()
{
  LinkedList<int> link;
  Node<int> a;
  for(int i = 0; i < 10; i++){
    a.set_data(i);
    link.append(a);
  }
  std::cout << "initial link: ";
  link.list();
  Node<int>* p1 = link.find(3);
  std::cout << "link.find(3): " << p1 << ", the data = " << p1->get_data() << std::endl;
  link.del(p1);
  std::cout << "after delete find(3): ";
  link.list();
  link.insert(6);
  std::cout << "after insert 6: ";
  link.list();
};
