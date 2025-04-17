#include <iostream>

int main() {
  int n = 0;
  std::cin >> n;
  int sum = n / 100 + (n / 10) % 10 + n % 10;
  std::cout << sum;
  return 0;
}