#ifndef SEGMENT_H
#define SEGMENT_H

#include <memory>
#include "AbstractShape.h"
#include "Point.h"

class Segment : public AbstractShape {
  Point start_;
  Point end_;

public:
  Segment() = default;
  Segment(const Segment& segm) = default;
  Segment(const Point& start, const Point& end) : start_(start), end_(end) {}
  ~Segment() = default;

  Segment& Move(const Vector& vect) final {return *this;}
  bool ContainsPoint(const Point& dot) const noexcept final {return true;}
  bool CrossSegment(Segment& line) const noexcept final{return true;}
  std::unique_ptr<AbstractShape> Clone() const noexcept override {
    return std::make_unique<Segment>(*this);
  }
  void Print() const {}
};

#endif //SEGMENT_H
