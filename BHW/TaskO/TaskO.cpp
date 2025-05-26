#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string Multiply(const std::string &a, const std::string &b) {
  if (a == "0" || b == "0") {
    return "0";
  }

  std::size_t n = a.size();
  std::size_t m = b.size();
  std::vector<int> result(n + m, 0);

  for (std::size_t i = n; i-- > 0;) {
    int digit_a = a[i] - '0';
    for (std::size_t j = m; j-- > 0;) {
      int digit_b = b[j] - '0';
      int sum = digit_a * digit_b + result[i + j + 1];
      result[i + j + 1] = sum % 10;
      result[i + j] += sum / 10;
    }
  }

  std::string product;
  product.reserve(n + m);
  bool leading = true;
  for (int digit : result) {
    if (leading && digit == 0) {
      continue;
    }
    leading = false;
    product.push_back(static_cast<char>('0' + digit));
  }

  return product.empty() ? "0" : product;
}

int main() {
  std::string a;
  std::string b;
  std::cin >> a;
  std::cin >> b;

  std::string product = Multiply(a, b);
  std::cout << product << std::endl;
  return 0;
}
