#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

namespace geometry {

class Vector;
class IAbstractShape;
class Point;
class Segment;
class Ray;
class Line;
class Polygon;
class Circle;

class Vector {
 private:
  int x_ = 0;
  int y_ = 0;

 public:
  Vector() = default;

  Vector(const int& x, const int& y) : x_(x), y_(y) {
  }

  Vector(const Point& a, const Point& b);

  ~Vector() = default;

  int X() const {
    return x_;
  }

  int Y() const {
    return y_;
  }
};

inline int DotProduct(const Vector& lhs, const Vector& rhs) noexcept {
  return lhs.X() * rhs.X() + lhs.Y() * rhs.Y();
}

inline int CrossProduct(const Vector& lhs, const Vector& rhs) noexcept {
  return lhs.X() * rhs.Y() - lhs.Y() * rhs.X();
}

inline bool Collinear(const Vector& lhs, const Vector& rhs) noexcept {
  return CrossProduct(lhs, rhs) == 0;
}

inline bool CoDirectional(const Vector& lhs, const Vector& rhs) noexcept {
  return CrossProduct(lhs, rhs) == 0 && DotProduct(lhs, rhs) >= 0;
}

inline bool AntiDirectional(const Vector& lhs, const Vector& rhs) noexcept {
  return CrossProduct(lhs, rhs) == 0 && DotProduct(lhs, rhs) <= 0;
}

class IAbstractShape {
 public:
  virtual ~IAbstractShape() = default;

  virtual IAbstractShape* Move(const Vector& vect) = 0;

  [[nodiscard]] virtual bool ContainsPoint(const Point& point) const = 0;

  [[nodiscard]] virtual bool CrossSegment(const Segment& segment) const = 0;

  [[nodiscard]] virtual IAbstractShape* Clone() const = 0;

  virtual void Print() const = 0;
};

class Point : public IAbstractShape {
 private:
  int x_ = 0;
  int y_ = 0;

 public:
  Point() = default;
  Point(int x, int y) : x_(x), y_(y) {
  }

  int X() const {
    return x_;
  }
  int Y() const {
    return y_;
  }

  IAbstractShape* Move(const Vector& vect) override {
    x_ += vect.X();
    y_ += vect.Y();
    return this;
  }

  bool ContainsPoint(const Point& other) const override {
    return x_ == other.X() && y_ == other.Y();
  }

  bool CrossSegment(const Segment& segment) const override;

  IAbstractShape* Clone() const override {
    return new Point(*this);
  }

  void Print() const override {
    std::cout << x_ << " " << y_;
  }
};
Vector::Vector(const Point& a, const Point& b) : x_(b.X() - a.X()), y_(b.Y() - a.Y()) {
}
class Segment : public IAbstractShape {
 private:
  Point start_;
  Point end_;

 public:
  Segment() = default;

  Segment(const Point& a, const Point& b) : start_(a), end_(b) {
  }

  const Point& Start() const {
    return start_;
  }

  const Point& End() const {
    return end_;
  }

  IAbstractShape* Move(const Vector& vect) override {
    start_.Move(vect);
    end_.Move(vect);
    return this;
  }

  bool ContainsPoint(const Point& point) const override {
    if (start_.X() == end_.X() && start_.Y() == end_.Y()) {
      return (point.X() == start_.X() && point.Y() == start_.Y());
    }
    Vector ab_vector(start_, end_);
    Vector ap_vector(start_, point);
    if (CrossProduct(ab_vector, ap_vector) != 0) {
      return false;
    }
    int dot_ab = DotProduct(ab_vector, ab_vector);
    int dot_ap = DotProduct(ap_vector, ab_vector);
    return (dot_ap >= 0) && (dot_ap <= dot_ab);
  }

  bool CrossSegment(const Segment& other) const override {
    auto on_segment = [](const Point& p, const Point& q, const Point& r) {
      return std::min(p.X(), r.X()) <= q.X() && q.X() <= std::max(p.X(), r.X()) && std::min(p.Y(), r.Y()) <= q.Y() &&
             q.Y() <= std::max(p.Y(), r.Y());
    };

    auto orientation = [](const Point& p, const Point& q, const Point& r) {
      Vector pq(p, q);
      Vector pr(p, r);
      int val = CrossProduct(pq, pr);
      if (val == 0) {
        return 0;
      };
      return (val > 0) ? 1 : 2;
    };

    Point p1 = start_;
    Point q1 = end_;
    Point p2 = other.start_;
    Point q2 = other.end_;
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) {
      return true;
    }

    if (o1 == 0 && on_segment(p1, p2, q1)) {
      return true;
    }
    if (o2 == 0 && on_segment(p1, q2, q1)) {
      return true;
    }
    if (o3 == 0 && on_segment(p2, p1, q2)) {
      return true;
    }
    if (o4 == 0 && on_segment(p2, q1, q2)) {
      return true;
    }
    return false;
  }

  IAbstractShape* Clone() const override {
    return new Segment(*this);
  }

  void Print() const override {
    std::cout << start_.X() << " " << start_.Y() << " " << end_.X() << " " << end_.Y() << std::endl;
  }
};

bool Point::CrossSegment(const Segment& segment) const {
  const Point& a = segment.Start();
  const Point& b = segment.End();

  Vector ab(a, b);
  Vector ap(a, *this);

  int cross = CrossProduct(ab, ap);
  int dot = DotProduct(ap, ab);
  int ab_sq = DotProduct(ab, ab);

  return cross == 0 && dot >= 0 && dot <= ab_sq;
}

class Line : public IAbstractShape {
 private:
  Point p1_;
  Point p2_;

 public:
  Line() = default;
  Line(const Point& a, const Point& b) : p1_(a), p2_(b) {
  }

  const Point& P1() const {
    return p1_;
  }
  const Point& P2() const {
    return p2_;
  }

  IAbstractShape* Move(const Vector& vect) override {
    p1_.Move(vect);
    p2_.Move(vect);
    return this;
  }

  bool ContainsPoint(const Point& point) const override {
    return Collinear(Vector(p1_, p2_), Vector(p1_, point));
  }

  bool CrossSegment(const Segment& segment) const override {
    const Point& a = segment.Start();
    const Point& b = segment.End();

    Vector dir = Vector(p1_, p2_);
    Vector va(p1_, a);
    Vector vb(p1_, b);

    int cp1 = CrossProduct(dir, va);
    int cp2 = CrossProduct(dir, vb);

    return cp1 * cp2 <= 0;
  }

  IAbstractShape* Clone() const override {
    return new Line(*this);
  }

  void Print() const override {
    std::cout << p1_.X() << " " << p1_.Y() << " " << p2_.X() << " " << p2_.Y();
  }
};

class Ray : public IAbstractShape {
 private:
  Point start_;
  Point through_;

 public:
  Ray() = default;

  Ray(const Point& start, const Point& through) : start_(start), through_(through) {
  }

  const Point& Start() const {
    return start_;
  }
  const Point& Through() const {
    return through_;
  }

  IAbstractShape* Move(const Vector& vect) override {
    start_.Move(vect);
    through_.Move(vect);
    return this;
  }

  bool ContainsPoint(const Point& point) const override {
    Vector dir(start_, through_);
    Vector to_point(start_, point);

    return Collinear(dir, to_point) && CoDirectional(dir, to_point);
  }

  bool CrossSegment(const Segment& segment) const override {
    const Point& a = segment.Start();
    const Point& b = segment.End();

    Vector dir(start_, through_);
    Vector sa(start_, a);
    Vector sb(start_, b);

    int cp1 = CrossProduct(dir, sa);
    int cp2 = CrossProduct(dir, sb);

    if (cp1 * cp2 > 0) {
      return false;
    }

    return CoDirectional(dir, sa) || CoDirectional(dir, sb);
  }

  IAbstractShape* Clone() const override {
    return new Ray(*this);
  }

  void Print() const override {
    std::cout << start_.X() << " " << start_.Y() << " " << through_.X() << " " << through_.Y();
  }
};

class Polygon : public IAbstractShape {
 private:
  std::vector<Point> points_;
  size_t size_;

 public:
  Polygon(const std::vector<Point>& points, size_t size) : points_(points), size_(size) {
    if (size < 3) {
      throw std::invalid_argument("Polygon must have at least 3 points");
    }
  }

  Polygon* Move(const Vector& vector) override {
    for (auto& point : points_) {
      point.Move(vector);
    }
    return this;
  }

  [[nodiscard]] bool ContainsPoint(const Point& point) const override {
    for (size_t i = 0; i < points_.size(); ++i) {
      Segment edge(points_[i], points_[(i + 1) % points_.size()]);
      if (edge.ContainsPoint(point)) {
        return true;
      }
    }
    int crossings = 0;
    for (size_t i = 0; i < size_; ++i) {
      const Point& a = points_[i];
      const Point& b = points_[(i + 1) % size_];
      int y_min = std::min(a.Y(), b.Y());
      int y_max = std::max(a.Y(), b.Y());
      if (point.Y() < y_min || point.Y() > y_max) {
        continue;
      }
      if ((a.Y() > point.Y()) != (b.Y() > point.Y())) {
        double x_cross = static_cast<double>(b.X() - a.X()) * (point.Y() - a.Y()) / (b.Y() - a.Y()) + a.X();
        if (x_cross > point.X()) {
          ++crossings;
        }
      }
    }
    return (crossings % 2) == 1;
  }

  [[nodiscard]] bool CrossSegment(const Segment& segment) const override {
    Segment edge;
    for (size_t i = 0; i < size_; ++i) {
      edge = Segment(points_[i], points_[(i + 1) % size_]);
      if (edge.CrossSegment(segment)) {
        return true;
      }
    }
    return false;
  }

  [[nodiscard]] IAbstractShape* Clone() const override {
    return new Polygon(points_, size_);
  }

  void Print() const override {
    std::cout << size_ << '\n';
    for (const auto& point : points_) {
      std::cout << point.X() << ' ' << point.Y() << ' ';
    }
  }
};

class Circle : public IAbstractShape {
 private:
  Point center_;
  int radius_ = 0;

 public:
  Circle() = default;

  Circle(const Point& center, int radius) : center_(center), radius_(radius) {
  }

  const Point& Center() const {
    return center_;
  }
  int Radius() const {
    return radius_;
  }

  IAbstractShape* Move(const Vector& vect) override {
    center_.Move(vect);
    return this;
  }

  bool ContainsPoint(const Point& point) const override {
    Vector dist(center_, point);
    return DotProduct(dist, dist) <= radius_ * radius_;
  }

  bool CrossSegment(const Segment& segment) const override {
    Vector d = Vector(segment.Start(), segment.End());
    Vector f = Vector(center_, segment.Start());

    auto a = DotProduct(d, d);
    auto b = 2 * DotProduct(f, d);
    auto c = DotProduct(f, f) - radius_ * radius_;

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
      return false;
    }

    discriminant = std::sqrt(discriminant);
    auto t1 = (-b - discriminant) / (2 * a);
    auto t2 = (-b + discriminant) / (2 * a);

    return (0 <= t1 && t1 <= 1) || (0 <= t2 && t2 <= 1);
  }

  IAbstractShape* Clone() const override {
    return new Circle(*this);
  }

  void Print() const override {
    std::cout << center_.X() << " " << center_.Y() << " " << radius_;
  }
};
}  // namespace geometry

void CheckFunctions(const geometry::IAbstractShape* shape, const geometry::Point& a, const geometry::Point& b) {
  if (shape->ContainsPoint(a)) {
    std::cout << "Given shape contains point A" << std::endl;
  } else {
    std::cout << "Given shape does not contain point A" << std::endl;
  }

  geometry::Segment ab_segment(a, b);
  if (shape->CrossSegment(ab_segment)) {
    std::cout << "Given shape crosses segment AB" << std::endl;
  } else {
    std::cout << "Given shape does not cross segment AB" << std::endl;
  }

  geometry::Vector ab(a, b);
  geometry::IAbstractShape* cloned_shape = shape->Clone();
  cloned_shape->Move(ab)->Print();
  delete cloned_shape;
}

int main() {  // NOLINT
  geometry::IAbstractShape* shape = nullptr;
  char command[10];
  std::cin >> command;

  if (!std::strcmp(command, "point")) {
    int x = 0;
    int y = 0;
    std::cin >> x >> y;
    shape = new geometry::Point(x, y);
  } else if (!std::strcmp(command, "segment")) {
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    std::cin >> x1 >> y1 >> x2 >> y2;
    shape = new geometry::Segment(geometry::Point(x1, y1), geometry::Point(x2, y2));
  } else if (!std::strcmp(command, "ray")) {
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    std::cin >> x1 >> y1 >> x2 >> y2;
    shape = new geometry::Ray(geometry::Point(x1, y1), geometry::Point(x2, y2));
  } else if (!std::strcmp(command, "line")) {
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    std::cin >> x1 >> y1 >> x2 >> y2;
    shape = new geometry::Line(geometry::Point(x1, y1), geometry::Point(x2, y2));
  } else if (!std::strcmp(command, "polygon")) {
    size_t n_points = 0;
    std::cin >> n_points;
    std::vector<geometry::Point> points;
    points.reserve(n_points);
    for (size_t i = 0; i < n_points; ++i) {
      int x = 0;
      int y = 0;
      std::cin >> x >> y;
      points.emplace_back(x, y);
    }
    shape = new geometry::Polygon(points, n_points);
  } else if (!std::strcmp(command, "circle")) {
    int x = 0;
    int y = 0;
    std::cin >> x >> y;
    geometry::Point center(x, y);
    int radius = 0;
    std::cin >> radius;
    shape = new geometry::Circle(center, radius);
  } else {
    std::cerr << "Undefined command" << std::endl;
    return 1;
  }

  int ax = 0;
  int ay = 0;
  int bx = 0;
  int by = 0;
  std::cin >> ax >> ay >> bx >> by;
  geometry::Point a(ax, ay);
  geometry::Point b(bx, by);

  CheckFunctions(shape, a, b);
  delete shape;

  return 0;
}
//ujqlf