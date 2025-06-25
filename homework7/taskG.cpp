#include <iostream>
#include <unordered_map>
#include <string>

int main() {
  int n = 0;
  std::cin >> n;

  std::unordered_map<std::string, std::string> synonyms;

  for (int i = 0; i < n; ++i) {
    std::string word1;
    std::string word2;
    std::cin >> word1 >> word2;
    synonyms[word1] = word2;
    synonyms[word2] = word1;
  }

  int q = 0;
  std::cin >> q;

  for (int i = 0; i < q; ++i) {
    std::string query_word;
    std::cin >> query_word;
    std::cout << synonyms[query_word] << "\n";
  }

  return 0;
}
