#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>

int main() {
  int n = 0;
  std::cin >> n;

  std::priority_queue<int, std::vector<int>, std::greater<int>> heap;

  for (int i = 0; i < n; ++i) {
    int num = 0;
    std::cin >> num;
    heap.push(num);
  }

  double total_cost = 0.0;

  while (heap.size() > 1) {
    int a = heap.top();
    heap.pop();
    int b = heap.top();
    heap.pop();

    int merged = a + b;
    total_cost += merged * 0.05;
    heap.push(merged);
  }

  std::cout << std::fixed << std::setprecision(6) << total_cost << "\n";
  return 0;
}
