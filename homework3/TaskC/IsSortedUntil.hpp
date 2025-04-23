#pragma once

template <typename Iterator>
Iterator IsSortedUntil(Iterator first, Iterator last) {
  if (first == last) {
    return last;
  }

  Iterator next = first;
  ++next;

  while (next != last) {
    if (*next < *first) {
      return next;
    }
    ++first;
    ++next;
  }

  return last;
}