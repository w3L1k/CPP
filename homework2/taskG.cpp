#include <iostream>

void Reverse(int n) {
  if (n == 0) {
    return;
  }
  int currentnumber = 0;
  std::cin >> currentnumber;
  Reverse(n - 1);
  std::cout << currentnumber << " ";
}
int main() {
  int n = 0;
  std::cin >> n;
  Reverse(n);
  return 0;
}
