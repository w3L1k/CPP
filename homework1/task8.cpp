#include <iostream>
#include <cstdint>

int main() {
  uint64_t n = 0;
  std::cin >> n;
  int differnet = 0;
  int total = 0;
  uint64_t i = 2;

  while (i * i <= n) {
    int power = 0;
    while (n % i == 0) {
      n /= i;
      power++;
    }
    if (power > 0) {
      differnet++;
      total += power;
      if (power > 1) {
        std::cout << "NO" << std::endl;
        return 0;
      }
    }
    i++;
  }

  if (n > 1) {
    differnet++;
    total++;
  }

  if (differnet == 2 && total == 2) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }

  return 0;
}
