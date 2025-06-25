#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> numbers(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> numbers[i];
  }

  int x;
  std::cin >> x;

  int count = std::count(numbers.begin(), numbers.end(), x);
  std::cout << count << "\n";

  return 0;
}
