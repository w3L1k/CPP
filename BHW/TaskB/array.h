#ifndef ARRAY_H_
#define ARRAY_H_

#include <cstddef>
#include <stdexcept>

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <typename T, std::size_t N>
class Array {
  public:
    T data [N];

    constexpr std::size_t Size() const noexcept {
      return N;
    }
    constexpr bool Empty() const noexcept {
      return N == 0;
    }
    T& operator[](std::size_t idx) {
      return data[idx];
    }
    const T& operator[](std::size_t idx) const {
      return data[idx];
    }
    T& At(std::size_t idx) {
      if (idx >= N) {
        throw ArrayOutOfRange{};
      }
      return data[idx];
      }

    const T& At(std::size_t idx) const {
      if (idx >= N) {
        throw ArrayOutOfRange{};
      }
      return data[idx];
    }
    T& Front() {
      return data[0];
    }
    const T& Front() const {
      return data[0];
    }
    T& Back() {
      return data[N - 1];
    }
    const T& Back() const {
      return data[N - 1];
    }
    T* Data() {
      return data;
    }
    const T* Data() const {
      return data;
    }
    void Fill(const T& value) {
      for (std::size_t i = 0; i < N; ++i) {
        data[i] = value;
      }
    }
    void Swap(Array<T, N>& other) {
      for (std::size_t i = 0; i < N; ++i) {
        T tmp = data[i];
        data[i] = other.data[i];
        other.data[i] = tmp;
      }
  }
};

#endif  // ARRAY_H_