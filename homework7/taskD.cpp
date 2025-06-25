#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  int n = 0;
  std::cin >> n;

  std::vector<int> colors(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> colors[i];
  }

  int m = 0;
  std::cin >> m;

  std::vector<int> queries(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> queries[i];
  }

  for (const int query : queries) {
    auto lower = std::lower_bound(colors.begin(), colors.end(), query);
    auto upper = std::upper_bound(colors.begin(), colors.end(), query);
    std::cout << upper - lower << "\n";
  }

  return 0;
}
