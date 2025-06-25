#include <iostream>
#include <map>
#include <string>
#include <cstdint>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::map<std::string, std::map<std::string, int64_t>> database;

  std::string buyer;
  std::string product;
  int64_t quantity = 0;

  while (std::cin >> buyer >> product >> quantity) {
    database[buyer][product] += quantity;
  }

  for (const auto& buyer_entry : database) {
    std::cout << buyer_entry.first << ":\n";
    for (const auto& product_entry : buyer_entry.second) {
      std::cout << product_entry.first << " " << product_entry.second << "\n";
    }
  }

  return 0;
}
