#include <iostream>
#include <string>

std::string ToBinary(int n) {
  std::string result;
  while (n > 0) {
    result = std::to_string(n % 2) + result;
    n /= 2;
  }
  return result;
}
std::string InvertBinary(std::string binary) {
  std::string inverted;
  for (char bit : binary) {
    inverted += (bit == '0') ? '1' : '0';
  }
  return inverted;
}
int main() {
  int n = 0;
  std::cin >> n;
  std::string binary = ToBinary(n);
  std::string inverted = InvertBinary(binary);
  int inverted_decimal = 0;
  for (size_t i = 0; i < inverted.length(); ++i) {
    inverted_decimal += (inverted[i] - '0') * (1 << (inverted.length() - 1 - i));
  }
  std::cout << inverted_decimal << std::endl;
  return 0;
}