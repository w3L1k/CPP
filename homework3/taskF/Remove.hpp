#ifndef REMOVE_HPP
#define REMOVE_HPP

template <typename Iterator, typename T>
Iterator Remove(Iterator begin, Iterator end, const T& value) {
  Iterator write = begin;
  for (Iterator read = begin; read != end; ++read) {
    if (*read != value) {
      *write = *read;
      ++write;
    }
  }
  return write;
}
#endif