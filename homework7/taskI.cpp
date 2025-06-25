#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

struct WordCount {
  std::string word;
  int count = 0;
};

bool Compare(const WordCount& a, const WordCount& b) {
  if (a.count != b.count) {
    return a.count > b.count;
  }
  return a.word < b.word;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::unordered_map<std::string, int> word_counter;
  std::string line;

  while (std::getline(std::cin, line)) {
    std::stringstream ss(line);
    std::string word;
    while (ss >> word) {
      ++word_counter[word];
    }
  }

  std::vector<WordCount> words;
  for (const auto& entry : word_counter) {
    words.push_back({entry.first, entry.second});
  }

  std::sort(words.begin(), words.end(), Compare);

  for (const auto& wc : words) {
    std::cout << wc.word << "\n";
  }

  return 0;
}
