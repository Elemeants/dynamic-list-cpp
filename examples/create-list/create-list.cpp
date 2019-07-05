#include <iostream>
#include "./../../list.hpp"

int main(void)
{
  std::cout << "Creating a list instance" << std::endl;
  List<int> int_list;
  int_list.push(10);
  int_list.push(20);
  for (int i = 0; i < int_list.length(); i++)
  {
      std::cout << " Value at position " << i << ": " <<  int_list[i] << std::endl;
  }
  return 0;
}
