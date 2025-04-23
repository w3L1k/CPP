#include <iostream>

int main() {
  int64_t a = 0;
  int64_t b = 0;
  std::cin >> a >> b;
  int64_t difference = 0;
  int64_t abs_difference = 0;
  int64_t maximum = 0;
  difference = a - b;
  abs_difference = (difference * ((difference >> 63) | 1)) - (difference >> 63);
  maximum = (a + b + abs_difference) / 2;
  std::cout << maximum << std::endl;
  return 0;
}