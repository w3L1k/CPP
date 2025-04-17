#include <iostream>
#include <string>

bool Annagram(const std::string& s1, const std::string& s2) {
  if (s1.length() != s2.length()) {
    return false;
  }
  int alphabet[26] = {0};
  for (std::size_t i = 0; i < s1.length(); ++i) {
    alphabet[s1[i] - 'a']++;
    alphabet[s2[i] - 'a']--;
  }
  for (int i = 0; i < 26; ++i) {
    if (alphabet[i] != 0) {
      return false;
    }
  }
  return true;
}

int main() {
  std::string s1;
  std::string s2;
  std::cin >> s1 >> s2;
  if (Annagram(s1, s2)) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
  return 0;
}