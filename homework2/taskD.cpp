#include <iostream>

int main() {
  int a[3][3];
  int b[3][3];
  int c[3][3] = {};

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      std::cin >> a[i][j];
    }
  }

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      std::cin >> b[i][j];
    }
  }

  // Умножение A * B → C
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      c[row][col] = 0;
      for (int inner = 0; inner < 3; ++inner) {
        c[row][col] += a[row][inner] * b[inner][col];
      }
      std::cout << c[row][col] << " ";
    }
    std::cout << "\n";
  }

  return 0;
}
