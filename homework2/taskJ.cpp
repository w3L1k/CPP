#include <iostream>
#include <string>
#include <cctype>

std::string Zip(const std::string& s) {
  std::string result;
  std::size_t n = s.length();

  for (std::size_t i = 0; i < n;) {
    char current = s[i];
    std::size_t count = 0;

    while (i < n && s[i] == current) {
      count++;
      i++;
    }

    result += current;
    result += std::to_string(count);
  }

  return result;
}

std::string Unzip(const std::string& s) {
  std::string result;
  std::size_t n = s.length();

  for (std::size_t i = 0; i < n;) {
    char current = s[i++];
    std::string count_str;

    while (i < n && std::isdigit(static_cast<unsigned char>(s[i]))) {
      count_str += s[i++];
    }

    int count = std::stoi(count_str);
    for (int j = 0; j < count; ++j) {
      result += current;
    }
  }

  return result;
}

int main() {
  std::string input;
  std::cin >> input;

  std::string a = Zip(input);
  std::string b = Unzip(a);

  std::cout << a << std::endl;
  std::cout << b << std::endl;

  return 0;
}
