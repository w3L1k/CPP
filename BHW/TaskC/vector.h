#pragma once

#include <algorithm>
#include <exception>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <utility>

#define VECTOR_MEMORY_IMPLEMENTED

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("Index out of range") {
  }
};

template <typename T>
class Vector {
 public:
  using ValueType = T;
  using Pointer = T*;
  using ConstPointer = const T*;
  using Reference = T&;
  using ConstReference = const T&;
  using SizeType = size_t;

  using Iterator = T*;
  using ConstIterator = const T*;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

  Vector() : data_(nullptr), size_(0), capacity_(0) {
  }

  explicit Vector(SizeType size) : data_(nullptr), size_(0), capacity_(size) {
    if (size > 0) {
      data_ = static_cast<T*>(::operator new(size * sizeof(T)));
      try {
        std::uninitialized_value_construct_n(data_, size);
        size_ = size;
      } catch (...) {
        Dealloc(data_);
        data_ = nullptr;
        capacity_ = 0;
        throw;
      }
    }
  }

  Vector(SizeType size, const T& value) : data_(nullptr), size_(0), capacity_(size) {
    if (size > 0) {
      data_ = static_cast<T*>(operator new(size * sizeof(T)));
      try {
        std::uninitialized_fill_n(data_, size, value);
        size_ = size;
      } catch (...) {
        Dealloc(data_);
        data_ = nullptr;
        capacity_ = 0;
        throw;
      }
    }
  }

  template <class InputIterator,
            class = std::enable_if_t<std::is_base_of_v<
                std::input_iterator_tag, typename std::iterator_traits<InputIterator>::iterator_category>>>
  Vector(InputIterator first, InputIterator last) : data_(nullptr), size_(0), capacity_(std::distance(first, last)) {
    if (capacity_ > 0) {
      data_ = static_cast<T*>(operator new(capacity_ * sizeof(T)));
      try {
        std::uninitialized_copy(first, last, data_);
        size_ = capacity_;
      } catch (...) {
        Dealloc(data_);
        data_ = nullptr;
        capacity_ = 0;
        throw;
      }
    }
  }

  Vector(std::initializer_list<T> init) : Vector(init.begin(), init.end()) {
  }

  Vector(const Vector& other) : data_(nullptr), size_(0), capacity_(0) {
    if (other.size_ > 0) {
      data_ = static_cast<T*>(operator new(other.capacity_ * sizeof(T)));
      try {
        std::uninitialized_copy(other.data_, other.data_ + other.size_, data_);
        size_ = other.size_;
        capacity_ = other.capacity_;
      } catch (...) {
        Dealloc(data_);
        data_ = nullptr;
        capacity_ = 0;
        throw;
      }
    }
  }

  Vector(Vector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  Vector& operator=(const Vector& other) {
    if (this != &other) {
      if (other.size_ == 0) {
        Clear();
        Dealloc(data_);
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
      } else {
        Vector tmp(other);
        Swap(tmp);
      }
    }
    return *this;
  }

  Vector& operator=(Vector&& other) noexcept {
    if (this != &other) {
      Clear();
      Dealloc(data_);
      data_ = other.data_;
      size_ = other.size_;
      capacity_ = other.capacity_;
      other.data_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }
    return *this;
  }

  ~Vector() {
    Clear();
    Dealloc(data_);
  }

  SizeType Size() const {
    return size_;
  }

  SizeType Capacity() const {
    return capacity_;
  }

  bool Empty() const {
    return size_ == 0;
  }

  Reference operator[](SizeType index) {
    return data_[index];
  }

  ConstReference operator[](SizeType index) const {
    return data_[index];
  }

  Reference At(SizeType index) {
    if (index >= size_) {
      throw ArrayOutOfRange();
    }
    return data_[index];
  }

  ConstReference At(SizeType index) const {
    if (index >= size_) {
      throw ArrayOutOfRange();
    }
    return data_[index];
  }

  Reference Front() {
    return data_[0];
  }

  ConstReference Front() const {
    return data_[0];
  }

  Reference Back() {
    return data_[size_ - 1];
  }

  ConstReference Back() const {
    return data_[size_ - 1];
  }

  Pointer Data() {
    return data_;
  }

  ConstPointer Data() const {
    return data_;
  }

  void Swap(Vector& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  void Resize(SizeType new_size) {
    if (new_size > size_) {
      if (new_size > capacity_) {
        SizeType new_capacity = new_size;
        T* new_data = static_cast<T*>(operator new(new_capacity * sizeof(T)));
        try {
          std::uninitialized_move(data_, data_ + size_, new_data);
          std::uninitialized_value_construct_n(new_data + size_, new_size - size_);
        } catch (...) {
          std::destroy(new_data, new_data + size_);
          operator delete(new_data);
          throw;
        }
        std::destroy(data_, data_ + size_);
        operator delete(data_);
        data_ = new_data;
        capacity_ = new_capacity;
      } else {
        try {
          std::uninitialized_value_construct_n(data_ + size_, new_size - size_);
        } catch (...) {
          std::destroy(data_ + size_, data_ + new_size);
          throw;
        }
      }
    } else {
      std::destroy(data_ + new_size, data_ + size_);
    }
    size_ = new_size;
  }

  void Resize(SizeType new_size, const T& value) {
    if (new_size > size_) {
      if (new_size > capacity_) {
        T* new_data = nullptr;
        SizeType old_capacity = capacity_;
        try {
          new_data = static_cast<T*>(operator new(new_size * sizeof(T)));
          std::uninitialized_move(data_, data_ + size_, new_data);
          std::uninitialized_fill_n(new_data + size_, new_size - size_, value);
          std::destroy(data_, data_ + size_);
          Dealloc(data_);
          data_ = new_data;
          capacity_ = new_size;
        } catch (...) {
          if (new_data) {
            std::destroy(new_data, new_data + size_);
            Dealloc(new_data);
          }
          capacity_ = old_capacity;
          throw;
        }
      } else {
        try {
          std::uninitialized_fill_n(data_ + size_, new_size - size_, value);
        } catch (...) {
          std::destroy(data_ + size_, data_ + new_size);
          throw;
        }
      }
    } else {
      std::destroy(data_ + new_size, data_ + size_);
    }
    size_ = new_size;
  }

  void Reserve(SizeType new_cap) {
    if (new_cap > capacity_) {
      T* new_data = static_cast<T*>(operator new(new_cap * sizeof(T)));
      try {
        std::uninitialized_move(data_, data_ + size_, new_data);
      } catch (...) {
        Dealloc(new_data);
        throw;
      }
      std::destroy(data_, data_ + size_);
      Dealloc(data_);
      data_ = new_data;
      capacity_ = new_cap;
    }
  }

  void ShrinkToFit() {
    if (size_ == 0) {
      Dealloc(data_);
      data_ = nullptr;
      capacity_ = 0;
    } else if (capacity_ > size_) {
      T* new_data = static_cast<T*>(operator new(size_ * sizeof(T)));
      try {
        std::uninitialized_move(data_, data_ + size_, new_data);
      } catch (...) {
        Dealloc(new_data);
        throw;
      }
      std::destroy(data_, data_ + size_);
      Dealloc(data_);
      data_ = new_data;
      capacity_ = size_;
    }
  }

  void Clear() noexcept {
    std::destroy(data_, data_ + size_);
    size_ = 0;
  }

  void PushBack(const T& value) {
    if (size_ == capacity_) {
      SizeType new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
      T* new_data = static_cast<T*>(operator new(new_capacity * sizeof(T)));
      try {
        std::uninitialized_move(data_, data_ + size_, new_data);
        new (new_data + size_) T(value);
      } catch (...) {
        std::destroy(new_data, new_data + size_);
        operator delete(new_data);
        throw;
      }
      std::destroy(data_, data_ + size_);
      operator delete(data_);
      data_ = new_data;
      capacity_ = new_capacity;
    } else {
      try {
        new (data_ + size_) T(value);
      } catch (...) {
        throw;
      }
    }
    ++size_;
  }

  void PushBack(T&& value) {
    if (size_ == capacity_) {
      SizeType new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
      T* new_data = static_cast<T*>(operator new(new_capacity * sizeof(T)));
      try {
        std::uninitialized_move(data_, data_ + size_, new_data);
        new (new_data + size_) T(std::move(value));
      } catch (...) {
        std::destroy(new_data, new_data + size_);
        operator delete(new_data);
        throw;
      }
      std::destroy(data_, data_ + size_);
      operator delete(data_);
      data_ = new_data;
      capacity_ = new_capacity;
    } else {
      try {
        new (data_ + size_) T(std::move(value));
      } catch (...) {
        throw;
      }
    }
    ++size_;
  }

  template <typename... Args>
  void EmplaceBack(Args&&... args) {
    if (size_ == capacity_) {
      Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    try {
      new (data_ + size_) T(std::forward<Args>(args)...);
      ++size_;
    } catch (...) {
      std::destroy_at(data_ + size_);
      throw;
    }
  }

  void PopBack() {
    if (size_ > 0) {
      std::destroy_at(data_ + size_ - 1);
      --size_;
    }
  }

  friend bool operator==(const Vector& l_value, const Vector& r_value) {
    return l_value.size_ == r_value.size_ && std::equal(l_value.data_, l_value.data_ + l_value.size_, r_value.data_);
  }
  
  friend bool operator!=(const Vector& l_value, const Vector& r_value) {
    return !(l_value == r_value);
  }

  friend bool operator<(const Vector& l_value, const Vector& r_value) {
    return std::lexicographical_compare(l_value.data_, l_value.data_ + l_value.size_, r_value.data_, r_value.data_ + r_value.size_);
  }

  friend bool operator>(const Vector& l_value, const Vector& r_value) {
    return r_value < l_value;
  }

  friend bool operator<=(const Vector& l_value, const Vector& r_value) {
    return !(r_value < l_value);
  }

  friend bool operator>=(const Vector& l_value, const Vector& r_value) {
    return !(l_value < r_value);
  }
  
  Iterator begin() {  // NOLINT
    return data_;
  }

  ConstIterator begin() const {  // NOLINT
    return data_;
  }

  Iterator end() {  // NOLINT
    return data_ + size_;
  }

  ConstIterator end() const {  // NOLINT
    return data_ + size_;
  }

  ConstIterator cbegin() const {  // NOLINT
    return data_;
  }

  ConstIterator cend() const {  // NOLINT
    return data_ + size_;
  }

  ReverseIterator rbegin() {  // NOLINT
    return ReverseIterator(end());
  }

  ConstReverseIterator rbegin() const {  // NOLINT
    return ConstReverseIterator(end());
  }

  ReverseIterator rend() {  // NOLINT
    return ReverseIterator(begin());
  }

  ConstReverseIterator rend() const {  // NOLINT
    return ConstReverseIterator(begin());
  }

  ConstReverseIterator crbegin() const {  // NOLINT
    return ConstReverseIterator(cend());
  }

  ConstReverseIterator crend() const {  // NOLINT
    return ConstReverseIterator(cbegin());
  }

 private:
  Pointer data_;
  SizeType size_;
  SizeType capacity_;

  static void Dealloc(Pointer p) {
    if (p != nullptr) {
      operator delete(p);
    }
  }
};
