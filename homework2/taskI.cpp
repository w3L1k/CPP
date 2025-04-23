#include <iostream>

double Power(double a, int b) {
  if (b == 0) {
    return 1;
  }
  if (b < 0) {
    return 0;
  }
  double half = Power(a, b / 2);
  if (b % 2 == 0) {
    return half * half;
  }
  return half * half * a;
}
int main() {
  double a = 0;
  int b = 0;
  std::cin >> a >> b;
  std::cout << Power(a, b) << std::endl;
  return 0;
}