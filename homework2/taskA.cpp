#include <iostream>

int BitAddition(int num) {
  if (num == 0) {
    return 1;
  }

  int mask = 0;
  int temp = num;

  while (temp > 0) {
    mask = (mask << 1) | 1;
    temp >>= 1;
  }

  return ~num & mask;
}

int main() {
  int num = 0;
  std::cin >> num;
  std::cout << BitAddition(num) << std::endl;
  return 0;
}
