#include <iostream>
#include <cmath>

int main() {
  int n = 0;
  std::cin >> n;

  if (n <= 1) {
    std::cout << "NO" << std::endl;
    return 0;
  }
  int64_t limit = 1;
  while (limit * limit <= n) {
    ++limit;
  }
  --limit;

  bool isprime = true;
  for (int i = 2; i <= limit; ++i) {
    if (n % i == 0) {
      isprime = false;
      break;
    }
  }

  if (isprime) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }

  return 0;
}
