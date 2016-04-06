#include <iostream>

#include <forward_list.h>

template <typename T>
void printList(ptl::ForwardList<T>& list)
{
  for (auto itr=list.begin(); itr!=list.end(); ++itr) {
    std::cout << *itr << std::endl;
  }
}

int main()
{
  ptl::ForwardList<int> list;
  list.push_front(0);
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);

  printList(list);
}
