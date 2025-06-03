#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>

struct Vector {
  int x_ = 0;
  int y_ = 0;
  Vector() = default;
  Vector(const Vector&) = default;
  Vector(const int &x, const int &y) : x_(x), y_(y) {}
  ~Vector() = default;

  int Length() const {
    return static_cast<int>(std::sqrt(x_ * x_ + y_ * y_));
  }
  void Normalize() {
    *this /= Length();
  }
  Vector Normalized() const {
    return *this / Length();
  }

  Vector operator+(const Vector &rhs) const {
    return {x_ + rhs.x_, y_ + rhs.y_};
  }
  Vector operator-(const Vector &rhs) const {
    return {x_ - rhs.x_, y_ - rhs.y_};
  }
  Vector& operator+=(const Vector &rhs) {
    x_ += rhs.x_;
    y_ += rhs.y_;
    return *this;
  }
  Vector& operator-=(const Vector &rhs) {
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    return *this;
  }

  Vector operator+() const { return *this; }
  Vector operator-() const { return {-x_, -y_}; }

  Vector operator*(const int &num) const {
    return {x_ * num, y_ * num};
  }
  Vector operator/(const int &num) const {
    return {x_ / num, y_ / num};
  }
  Vector& operator*=(const int &num) {
    x_ *= num;
    y_ *= num;
    return *this;
  }
  Vector& operator/=(const int &num) {
    x_ /= num;
    y_ /= num;
    return *this;
  }

  bool operator==(const Vector &rhs) const {
    return x_ == rhs.x_ && y_ == rhs.y_;
  }
  bool operator!=(const Vector &rhs) const {
    return !(*this == rhs);
  }
};

inline Vector operator*(const int &num, const Vector &vect) {
  return {vect.x_ * num, vect.y_ * num};
}
inline Vector operator/(const int &num, const Vector &vect) {
  return {vect.x_ / num, vect.y_ / num};
}
inline std::ostream &operator<<(std::ostream &os, const Vector &vect) {
  os << "(0, 0)--->(" << vect.x_ << ", " << vect.y_ << ')';
  return os;
}

inline int DotProduct(const Vector &lhs, const Vector &rhs) noexcept {
  return lhs.x_ * rhs.x_ + lhs.y_ * rhs.y_;
}

inline int CrossProduct(const Vector &lhs, const Vector &rhs) noexcept {
  return lhs.x_ * rhs.y_ - lhs.y_ * rhs.x_;
}

inline bool Collinear(const Vector &lhs, const Vector &rhs) noexcept {
  return CrossProduct(lhs, rhs) == 0;
}

inline bool CoDirectional(const Vector &lhs, const Vector &rhs) noexcept {
  return CrossProduct(lhs, rhs) == 0 && DotProduct(lhs, rhs) >= 0;
}

inline bool AntiDirectional(const Vector& lhs, const Vector& rhs) noexcept {
  return CrossProduct(lhs, rhs) == 0 && DotProduct(lhs, rhs) <= 0;
}

#endif //VECTOR_H