#include <iostream>
#include <unordered_map>
#include <string>

int main() {
  int query_count = 0;
  std::cin >> query_count;

  std::unordered_map<std::string, int> accounts;

  for (int i = 0; i < query_count; ++i) {
    int command = 0;
    std::cin >> command;

    if (command == 1) {
      std::string name;
      int amount = 0;
      std::cin >> name >> amount;
      accounts[name] += amount;
    } else if (command == 2) {
      std::string name;
      std::cin >> name;
      if (accounts.count(name) > 0) {
        std::cout << accounts[name] << "\n";
      } else {
        std::cout << "ERROR\n";
      }
    }
  }

  return 0;
}
