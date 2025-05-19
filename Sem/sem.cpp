#include <iostream>

int f(int x){
  if (x<3) {
    return 1;
  }
    if (x>2 && x%2==0) {
    return f(x-1)+x-1;
  }
    if (x>2 && x%2 != 0) {
    return f(x-2)+2*x-2;
  }
}

int main() {
  int x= f(3048) - f(3045);
  std::cout << x << std::endl;
  return 0;
}