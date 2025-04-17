#include <iostream>
#include <cmath>

int MinDifference(int i, int sum1, int sum2, int n, int a[]) {
  if (i == n) {
    return std::abs(sum1 - sum2);
  }
  int value1 = MinDifference(i + 1, sum1 + a[i], sum2, n, a);
  int value2 = MinDifference(i + 1, sum1, sum2 + a[i], n, a);
  return std::min(value1, value2);
}
int main() {
  int a[20] = {0};
  int n = 0;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  int result = MinDifference(0, 0, 0, n, a);
  std::cout << result << std::endl;
  return 0;
}