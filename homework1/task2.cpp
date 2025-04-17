#include <cmath>
#include <iostream>

int main() {
  int x = 0;
  int y = 0;
  double z = 0.0;

  std::cin >> x >> y;

  z = std::sqrt(x * x + y * y);

  std::cout << z << std::endl;
  return 0;
}
