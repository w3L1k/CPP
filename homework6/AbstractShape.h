#ifndef ABSTRACTSHAPES_H
#define ABSTRACTSHAPES_H

#include <memory>
#include "Vector.h"

class Point;
class Segment;
class Ray;
class Line;
class Polygon;
class Circle;

class AbstractShape {
public:
  virtual AbstractShape& Move(const Vector& vect) = 0;
  virtual bool ContainsPoint(const Point& dot) const noexcept = 0;
  virtual bool CrossSegment(Segment& line) const noexcept = 0;
  virtual std::unique_ptr<AbstractShape> Clone() const noexcept = 0;
  virtual void Print() const = 0;

  ~AbstractShape() = default;
};

#endif //ABSTRACTSHAPES_H
