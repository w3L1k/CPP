#include <iostream>
#include <vector>

int main() {
  int n = 0;
  std::cin >> n;
  int a = 1;
  int b = 1;
  int c = 0;
  if (n == 1 || n == 2) {
    std::cout << 1 << std::endl;
    return 0;
  }
  for (int i = 2; i < n; i++) {
    c = b + a;
    a = b;
    b = c;
  }
  std::cout << c << std::endl;
  return 0;
}