#include <iostream>

int Midle(int a, int b, int c) {
  if (a > b) {
    if (a < c) {
      return a;
    } else if (b > c) {
      return b;
    } 
    else {
      return c;
    }
  }
  else {
    if (b < c) {
      return b;
    } else if (a > c) {
      return a;
      } 
      else {
        return c;
      }
  }
}