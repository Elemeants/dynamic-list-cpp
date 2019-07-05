#include <iostream>
#include "./../../list.hpp"

int main(void)
{
  std::cout << "Creating a list instance" << std::endl;
  List<int> int_list = List<int>();
  int_list.push(10);
  int_list.push(20);
  int_list.push_front(0);
  int val = int_list.pop();
  if (val == 0) { std::cout << "POP: OK" << std::endl; }
  val = int_list.pop_back();
  if (val == 20) { std::cout << "POP_BACK: OK" << std::endl; }
  for (int i = 0; i < int_list.length(); i++)
  {
    std::cout << " Value at position " << i << ": " <<  int_list[i] << std::endl;
  }
  return 0;
}
