#include <iostream>
#include <string>
#include <vector>

int main() {
  int n = 0;
  std::cin >> n;

  std::vector<std::string> passwords(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> passwords[i];
  }

  int64_t count = 0;

  for (int i = 0; i < n; ++i) {
    const std::string& a = passwords[i];
    for (int j = 0; j < n; ++j) {
      if (i == j) {
        continue;
      }
      const std::string& b = passwords[j];
      if (b.find(a) != std::string::npos) {
        ++count;
      }
    }
  }

  std::cout << count << std::endl;
  return 0;
}
