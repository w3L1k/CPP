#include <iostream>
#include <queue>
#include <vector>
#include <cstdint>

int main() {
  uint64_t n = 0;
  std::cin >> n;
  std::priority_queue<uint64_t, std::vector<uint64_t>, std::greater<>> pq;

  for (uint64_t i = 0; i < n; ++i) {
    uint64_t population = 0;
    std::cin >> population;
    pq.push(population);
  }

  uint64_t total = 0;
  while (pq.size() > 1) {
    uint64_t first = pq.top();
    pq.pop();
    uint64_t second = pq.top();
    pq.pop();
    total += first + second;
    pq.push(first + second);
  }
  std::cout << total << std::endl;
  return 0;
}