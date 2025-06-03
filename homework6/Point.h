#ifndef POINT_H
#define POINT_H

#include "AbstractShape.h"
#include "memory"

class Point: public AbstractShape {
  int x_ = 0;
  int y_ = 0;
public:
  Point() = default;
  Point(const int& x, const int& y) : x_(x), y_(y) {}
  Point(const Point& dot) = default;

  Point operator-(const Point& dot) const {
    return {x_ - dot.x_, y_ - dot.y_};
  }

  Point& Move(const Vector& vect) override {
    x_ += vect.x_;
    y_ += vect.y_;
    return *this;
  }
  [[nodiscard]] bool ContainsPoint(const Point& dot) const noexcept override {
    return x_ == dot.x_ && y_ == dot.y_;
  }
  bool CrossSegment(Segment& segm) const noexcept override {
    return true;
  }
  [[nodiscard]] std::unique_ptr<AbstractShape> Clone() const noexcept override {
    return std::make_unique<Point>(*this);
  }
  void Print() const override {
    std::cout << x_ << ' ' << y_;
  }

  friend bool CollinearVectors(const Point& dot1, const Point& dot2, const Point& dot3);
};

#endif //POINT_H
