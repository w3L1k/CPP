#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <type_traits>
#include <utility> // for std::as_const

// NOLINT

template <typename T>
class Vector {
 public:
  using ValueType = T;
  using Pointer = T*;
  using ConstPointer = const T*;
  using Reference = T&;
  using ConstReference = const T&;
  using SizeType = std::size_t;
  using Iterator = T*;
  using ConstIterator = const T*;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

  Vector() noexcept = default;

  explicit Vector(SizeType n) : size_(n), capacity_(n) {
    if (n == 0) {
      data_ = nullptr;
    } else {
      data_ = allocator_.allocate(n);
      std::uninitialized_value_construct_n(data_, n);
    }
  }

  Vector(SizeType n, const T& value) : size_(n), capacity_(n) {
    if (n == 0) {
      data_ = nullptr;
    } else {
      data_ = allocator_.allocate(n);
      std::uninitialized_fill_n(data_, n, value);
    }
  }

  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  Vector(Iterator first, Iterator last) {
    SizeType n = std::distance(first, last);
    if (n == 0) {
      data_ = nullptr;
      size_ = capacity_ = 0;
    } else {
      data_ = allocator_.allocate(n);
      std::uninitialized_copy(first, last, data_);
      size_ = capacity_ = n;
    }
  }

  Vector(std::initializer_list<T> init) : Vector(init.begin(), init.end()) {}

  Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_) {
    if (other.size_ == 0) {
      data_ = nullptr;
    } else {
      data_ = allocator_.allocate(capacity_);
      std::uninitialized_copy(other.data_, other.data_ + size_, data_);
    }
  }

  Vector(Vector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = other.capacity_ = 0;
  }

  Vector& operator=(const Vector& other) {
    if (this != &other) {
      Vector tmp(other);
      Swap(tmp);
    }
    return *this;
  }

  Vector& operator=(Vector&& other) noexcept {
    if (this != &other) {
      Clear();
      allocator_.deallocate(data_, capacity_);
      data_ = other.data_;
      size_ = other.size_;
      capacity_ = other.capacity_;
      other.data_ = nullptr;
      other.size_ = other.capacity_ = 0;
    }
    return *this;
  }

  ~Vector() {
    Clear();
    if (data_) allocator_.deallocate(data_, capacity_);
  }

  SizeType Size() const noexcept { return size_; }
  SizeType Capacity() const noexcept { return capacity_; }
  bool Empty() const noexcept { return size_ == 0; }

  Reference operator[](SizeType i) { return data_[i]; }
  ConstReference operator[](SizeType i) const { return data_[i]; }

  Reference At(SizeType i) {
    if (i >= size_) throw std::out_of_range("Vector::At: index out of range");
    return data_[i];
  }
  ConstReference At(SizeType i) const {
    if (i >= size_) throw std::out_of_range("Vector::At: index out of range");
    return data_[i];
  }

  Reference Front() { return data_[0]; }
  ConstReference Front() const { return data_[0]; }
  Reference Back() { return data_[size_ - 1]; }
  ConstReference Back() const { return data_[size_ - 1]; }

  Pointer Data() noexcept { return data_; }
  ConstPointer Data() const noexcept { return data_; }

  void Swap(Vector& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  void Resize(SizeType new_size) {
    if (new_size < size_) {
      std::destroy_n(data_ + new_size, size_ - new_size);
      size_ = new_size;
    } else if (new_size > size_) {
      Reserve(new_size);
      std::uninitialized_default_construct_n(data_ + size_, new_size - size_);
      size_ = new_size;
    }
    if (size_ == 0 && capacity_ != 0) {
      allocator_.deallocate(data_, capacity_);
      data_ = nullptr;
      capacity_ = 0;
    }
  }

  void Resize(SizeType new_size, const T& value) {
    if (new_size < size_) {
      std::destroy_n(data_ + new_size, size_ - new_size);
      size_ = new_size;
    } else if (new_size > size_) {
      Reserve(new_size);
      std::uninitialized_fill_n(data_ + size_, new_size - size_, value);
      size_ = new_size;
    }
    if (size_ == 0 && capacity_ != 0) {
      allocator_.deallocate(data_, capacity_);
      data_ = nullptr;
      capacity_ = 0;
    }
  }

  void PushBack(const T& value) {
    SizeType old_capacity = capacity_;
    if (size_ == capacity_) {
      try {
        Reserve(capacity_ ? capacity_ * 2 : 1);
      } catch (...) {
        capacity_ = old_capacity;
        throw;
      }
    }
    new (data_ + size_) T(value);
    ++size_;
  }

  void PushBack(T&& value) {
    SizeType old_capacity = capacity_;
    if (size_ == capacity_) {
      try {
        Reserve(capacity_ ? capacity_ * 2 : 1);
      } catch (...) {
        capacity_ = old_capacity;
        throw;
      }
    }
    new (data_ + size_) T(std::move(value));
    ++size_;
  }

  void Reserve(SizeType new_cap) {
    if (new_cap <= capacity_) return;
    T* new_data = nullptr;
    try {
      new_data = allocator_.allocate(new_cap);
      std::uninitialized_move(data_, data_ + size_, new_data);
    } catch (...) {
      if (new_data) allocator_.deallocate(new_data, new_cap);
      throw;
    }
    T* old_data = data_;
    SizeType old_capacity = capacity_;
    data_ = new_data;
    capacity_ = new_cap;
    if (old_data) {
      std::destroy_n(old_data, size_);
      allocator_.deallocate(old_data, old_capacity);
    }
  }

  void ShrinkToFit() {
    if (capacity_ == size_) return;
    if (size_ == 0) {
      if (data_) allocator_.deallocate(data_, capacity_);
      data_ = nullptr;
      capacity_ = 0;
      return;
    }
    T* new_data = allocator_.allocate(size_);
    std::uninitialized_move(data_, data_ + size_, new_data);
    std::destroy_n(data_, size_);
    allocator_.deallocate(data_, capacity_);
    data_ = new_data;
    capacity_ = size_;
  }

  void Clear() noexcept {
    std::destroy_n(data_, size_);
    size_ = 0;
  }

  void PopBack() {
    if (size_) {
      --size_;
      std::destroy_at(data_ + size_);
    }
  }

  Iterator begin() noexcept { return data_; } // NOLINT
  ConstIterator begin() const noexcept { return data_; } // NOLINT
  ConstIterator cbegin() const noexcept { return data_; } // NOLINT
  Iterator end() noexcept { return data_ + size_; } // NOLINT
  ConstIterator end() const noexcept { return data_ + size_; } // NOLINT
  ConstIterator cend() const noexcept { return data_ + size_; } // NOLINT
  ReverseIterator rbegin() noexcept { return ReverseIterator(end()); } // NOLINT
  ReverseIterator rend() noexcept { return ReverseIterator(begin()); } // NOLINT
  ConstReverseIterator rbegin() const noexcept { return ConstReverseIterator(end()); } // NOLINT
  ConstReverseIterator rend() const noexcept { return ConstReverseIterator(begin()); } // NOLINT
  ConstReverseIterator crbegin() const noexcept { return ConstReverseIterator(cend()); } // NOLINT
  ConstReverseIterator crend() const noexcept { return ConstReverseIterator(cbegin()); } // NOLINT

  friend bool operator==(const Vector& lhs, const Vector& rhs) {
    return lhs.size_ == rhs.size_ && std::equal(lhs.begin(), lhs.end(), rhs.begin());
  }

  friend bool operator!=(const Vector& lhs, const Vector& rhs) {
    return !(lhs == rhs);
  }

  friend bool operator<(const Vector& lhs, const Vector& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
  }

  friend bool operator<=(const Vector& lhs, const Vector& rhs) {
    return !(rhs < lhs);
  }

  friend bool operator>(const Vector& lhs, const Vector& rhs) {
    return rhs < lhs;
  }

  friend bool operator>=(const Vector& lhs, const Vector& rhs) {
    return !(lhs < rhs);
  }

 private:
  T* data_ = nullptr;
  SizeType size_ = 0;
  SizeType capacity_ = 0;
  std::allocator<T> allocator_;
};

#endif // VECTOR_H
