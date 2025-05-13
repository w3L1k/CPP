#include <iostream>
#include <string>

std::string Add(const std::string& a, const std::string& b) {
  std::string reversed_result;
  int carry = 0;
  std::size_t n = std::max(a.size(), b.size());

  for (std::size_t i = 0; i < n; ++i) {
    int digit_a = (i < a.size()) ? a[a.size() - 1 - i] - '0' : 0;
    int digit_b = (i < b.size()) ? b[b.size() - 1 - i] - '0' : 0;
    int sum = digit_a + digit_b + carry;
    reversed_result += static_cast<char>(sum % 10 + '0');
    carry = sum / 10;
  }

  if (carry > 0) {
    reversed_result += static_cast<char>(carry + '0');
  }

  std::string result;
  result.reserve(reversed_result.size());
  for (std::size_t i = reversed_result.size(); i-- > 0;) {
    result += reversed_result[i];
  }

  return result;
}

int main() {
  std::string a;
  std::string b;
  std::cin >> a;
  std::cin >> b;

  std::string sum = Add(a, b);
  std::cout << sum << std::endl;

  return 0;
}
