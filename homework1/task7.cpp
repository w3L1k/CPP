#include <iostream>
#include <cstdint>

int main() {
  uint64_t x = 0;
  std::cin >> x;
  uint64_t i = 2;
  while (i * i <= x) {
    while (x % i == 0) {
      std::cout << i << " ";
      x /= i;
    }
    i++;
  }
  if (x > 1) {
    std::cout << x;
  }
  std::cout << std::endl;
  return 0;
}