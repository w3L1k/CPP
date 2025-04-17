#include <iostream>

bool IsPrime(int n) {
  if (n <= 1) {
    return false;
  }
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}
int main() {
  int n = 0;
  int t = 0;
  std::cin >> n >> t;
  for (int i = n; i <= t; ++i) {
    if (IsPrime(i)) {
      std::cout << i << "\n";
    }
  }
  return 0;
}