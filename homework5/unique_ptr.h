#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <utility>

template <typename T>
class UniquePtr {
 public:
  UniquePtr() = default;

  explicit UniquePtr(T* ptr) : ptr_(ptr) {}

  UniquePtr(const UniquePtr&) = delete;
  UniquePtr& operator=(const UniquePtr&) = delete;

  UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }

  UniquePtr& operator=(UniquePtr&& other) noexcept {
    if (this != &other) {
      delete ptr_;
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  }

  ~UniquePtr() {
    delete ptr_;
  }

  T* Release() {
    T* old = ptr_;
    ptr_ = nullptr;
    return old;
  }

  void Reset(T* ptr = nullptr) {
    if (ptr_ != ptr) {
      delete ptr_;
      ptr_ = ptr;
    }
  }

  void Swap(UniquePtr& other) noexcept {
    std::swap(ptr_, other.ptr_);
  }

  T* Get() const {
    return ptr_;
  }

  T& operator*() const {
    return *ptr_;
  }

  T* operator->() const {
    return ptr_;
  }

  explicit operator bool() const {
    return ptr_ != nullptr;
  }

 private:
  T* ptr_ = nullptr;
};

#endif  // UNIQUE_PTR_H
