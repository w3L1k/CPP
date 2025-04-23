#include <iostream>
#include <cmath>
#include <cstdint>

int main() {
  int64_t x = 0;
  std::cin >> x;
  int64_t count = 0;
  int64_t limit = 1;
  while (limit * limit <= x) {
    ++limit;
  }
  --limit;
  for (int64_t i = 1; i <= limit; ++i) {
    if (x % i == 0) {
      count += 2;
      if (i == x / i) {
        --count;
      }
    }
  }
  std::cout << count << std::endl;
  return 0;
}
