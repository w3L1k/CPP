#include <iostream>
#include <cmath>

int main() {
  const int n = 10000;
  int nums[n];
  int result[n];

  for (int i = 0; i < n; ++i) {
    std::cin >> nums[i];
  }

  int left = 0;
  int right = n - 1;

  for (int i = n - 1; i >= 0; --i) {
    if (std::abs(nums[left]) > std::abs(nums[right])) {
      result[i] = nums[left] * nums[left];
      ++left;
    } else {
      result[i] = nums[right] * nums[right];
      --right;
    }
  }

  for (int i = 0; i < n; ++i) {
    std::cout << result[i] << " ";
  }

  return 0;
}
