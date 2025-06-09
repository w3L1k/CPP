#include <iostream>

int main(void) {
int x = 0;
int a = x++;
int b = ++x;
std::cout << "x: " << x << ", a: " << a << ", b: " << b << std::endl;
    return 0;
}