#include <cmath>
#include <iostream>

int main() {
  int йцу = 0;
  int y = 0;
  double z = 0.0;

  std::cin >> йцу >> y;

  z = std::sqrt(йцу * йцу + y * y);

  std::cout << z << std::endl;
  return 0;
}
