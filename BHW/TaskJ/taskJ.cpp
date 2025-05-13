#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

int main() {
  std::vector<std::pair<std::string, int>> word_count;
  std::string line;
  std::string word;

  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      break;
    }

    std::istringstream iss(line);
    while (iss >> word) {
      bool found = false;
      for (auto& entry : word_count) {
        if (entry.first == word) {
          ++entry.second;
          found = true;
          break;
        }
      }

      if (!found) {
        word_count.emplace_back(word, 1);
      }
    }
  }

  std::sort(word_count.begin(), word_count.end(),
            [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
              if (a.second != b.second) {
                return a.second > b.second;
              }
              return a.first < b.first;
            });

  for (const auto& entry : word_count) {
    std::cout << entry.first << std::endl;
  }

  return 0;
}
