#include <iostream>
#include <vector>

void PrintPrime(int a, int b) {
  std::vector<bool> isprime(b + 1, true);
  isprime[0] = isprime[1] = false;

  for (int i = 2; i * i <= b; ++i) {
    if (isprime[i]) {
      for (int j = i * i; j <= b; j += i) {
        isprime[j] = false;
      }
    }
  }

  for (int i = a; i <= b; ++i) {
    if (isprime[i]) {
      std::cout << i << std::endl;
    }
  }
}

int main() {
  int a = 0;
  int b = 0;
  std::cin >> a >> b;
  PrintPrime(a, b);
  return 0;
}
