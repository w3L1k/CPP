#include <iostream>

void Reverse(int n) {
  if (n == 0) {
    return;
  }
  int x = 0;
  std::cin >> x;
  Reverse(n - 1);
  std::cout << x << " ";
}
int main() {
  int n = 0;
  std::cin >> n;
  Reverse(n);
  return 0;
}
