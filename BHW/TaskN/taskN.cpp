#include <iostream>
#include <string>

std::string Subtract(const std::string& a, const std::string& b) {
  std::string reversed_result;
  int carry = 0;
  std::size_t n = a.size();

  for (std::size_t i = 0; i < n; ++i) {
    int digit_a = a[a.size() - 1 - i] - '0';
    int digit_b = (i < b.size()) ? b[b.size() - 1 - i] - '0' : 0;
    int diff = digit_a - digit_b - carry;

    if (diff < 0) {
      diff += 10;
      carry = 1;
    } else {
      carry = 0;
    }

    reversed_result += static_cast<char>(diff + '0');
  }

  while (reversed_result.size() > 1 && reversed_result.back() == '0') {
    reversed_result.pop_back();
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
  std::cin >> a >> b;

  std::string diff = Subtract(a, b);
  std::cout << diff << std::endl;

  return 0;
}
