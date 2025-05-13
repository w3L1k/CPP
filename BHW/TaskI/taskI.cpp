#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>

int main() {
  std::unordered_map<std::string, int> word_count;
  std::string line, word;

  while (std::cin >> word) {
    std::cout << word_count[word] << " ";
    word_count[word]++;
  }


  std::cout << std::endl;
  return 0;
}
