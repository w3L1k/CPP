#include <iostream>

int main() {
  const int a = 10000;
  int nums[a];
  int n = 0;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> nums[i];
  }
  int pos = 0;
  for (int i = 0; i < n; ++i) {
    if (nums[i] != 0) {
      nums[pos] = nums[i];
      ++pos;
    }
  }
  while (pos < n) {
    nums[pos] = 0;
    pos++;
  }
  for (int i = 0; i < n; ++i) {
    std::cout << nums[i] << " ";
  }
  return 0;
}