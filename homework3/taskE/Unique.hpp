#ifndef UNIQUE_HPP
#define UNIQUE_HPP

#include <iostream>
template <typename Iterator>
Iterator Unique(Iterator begin, Iterator end) {
  if (begin == end) {
    return end;
  }

  Iterator write = begin;
  Iterator read = begin;

  ++read;

  while (read != end) {
    if (*read != *write) {
      ++write;
      *write = *read;
    }
  ++read;
  }

  return ++write;
}

#endif