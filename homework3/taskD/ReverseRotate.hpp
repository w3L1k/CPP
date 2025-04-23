#ifndef ReverseRotate_hpp
#define ReverseRotate_hpp
#include <iostream>
template <typename T>
void Swap(T& a, T& b) {
  T temp = a;
  a = b;
  b = temp;
}

template <typename Iterator>
void Reverse(Iterator begin , Iterator end) {
  if (begin == end) {
    return;
  }
  --end;
  while (begin < end) {
    Swap(*begin, *end);
    ++begin;
    --end;
  }
}
template <typename Iterator>
void Rotate(Iterator begin, Iterator middle, Iterator end) {
  Reverse(begin, middle);
  Reverse(middle, end);
  Reverse(begin, end);
}
#endif