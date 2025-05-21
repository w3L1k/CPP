#ifndef SHARED_PTR_H_
#define SHARED_PTR_H_

#include <cstddef>

template <typename T>
class SharedPtr {
 public:
  SharedPtr() noexcept : ptr_(nullptr), counter_(nullptr) {}

  explicit SharedPtr(T* ptr) : ptr_(ptr) {
    if (ptr_) {
      counter_ = new std::size_t(1);
    } else {
      counter_ = nullptr;
    }
  }

  SharedPtr(const SharedPtr& other) noexcept : ptr_(other.ptr_), counter_(other.counter_) {
    if (counter_) {
      ++(*counter_);
    }
  }

  SharedPtr(SharedPtr&& other) noexcept : ptr_(other.ptr_), counter_(other.counter_) {
    other.ptr_ = nullptr;
    other.counter_ = nullptr;
  }

  ~SharedPtr() {
    Decrease();
  }

  SharedPtr& operator=(const SharedPtr& other) noexcept {
    if (this != &other) {
      Decrease();
      ptr_ = other.ptr_;
      counter_ = other.counter_;
      if (counter_) {
        ++(*counter_);
      }
    }
    return *this;
  }

  SharedPtr& operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
      Decrease();
      ptr_ = other.ptr_;
      counter_ = other.counter_;
      other.ptr_ = nullptr;
      other.counter_ = nullptr;
    }
    return *this;
  }

  void Reset(T* ptr = nullptr) {
    Decrease();
    if (ptr) {
      ptr_ = ptr;
      counter_ = new std::size_t(1);
    } else {
      ptr_ = nullptr;
      counter_ = nullptr;
    }
  }

  void Swap(SharedPtr& other) noexcept {
    T* tmp_ptr = ptr_;
    ptr_ = other.ptr_;
    other.ptr_ = tmp_ptr;

    std::size_t* tmp_counter = counter_;
    counter_ = other.counter_;
    other.counter_ = tmp_counter;
  }

  T* Get() const noexcept {
    return ptr_;
  }

  std::size_t UseCount() const noexcept {
    return counter_ ? *counter_ : 0;
  }

  T& operator*() const {
    return *ptr_;
  }

  T* operator->() const {
    return ptr_;
  }

  explicit operator bool() const noexcept {
    return ptr_ != nullptr;
  }

 private:
  void Decrease() {
    if (counter_) {
      if (--(*counter_) == 0) {
        delete ptr_;
        delete counter_;
      }
    }
  }

  T* ptr_;
  std::size_t* counter_;
};

#endif  // SHARED_PTR_H_
