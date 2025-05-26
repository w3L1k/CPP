#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>
 
namespace geometry {
    class Vector;
 
    class AbstractShape;
    class Point;
    class Segment;
    class Ray;
    class Line;
    class Polygon;
    class Circle;
 
    class Vector {
    private:
        double x_ = 0;
        double y_ = 0;
    public:
        Vector() = default;
        Vector(double x, double y) : x_(x), y_(y) {}
        Vector(const Point& A, const Point& B) : x_(B.X() - A.X()), y_(B.Y() - A.Y()) {}
        double X() const { return x_; }
        double Y() const { return y_; }
        double Length() const { return std::sqrt(x_ * x_ + y_ * y_); }

        Vector operator+(const Vector& other) const {
            return Vector(x_ + other.x_, y_ + other.y_);
        }
        Vector operator-(const Vector& other) const {
            return Vector(x_ - other.x_, y_ - other.y_);
        }
        Vector operator*(double scalar) const {
            return Vector(x_ * scalar, y_ * scalar);
        }
        double Dot(const Vector& other) const {
            return x_ * other.x_ + y_ * other.y_;
        }
        double Cross(const Vector& other) const {
            return x_ * other.y_ - y_ * other.x_;
        }

    };
 
    class AbstractShape {
    public:
        virtual ~AbstractShape() = default;
        virtual bool ContainsPoint(const Point& point) const = 0;
        virtual bool CrossSegment(const Segment& segment) const = 0;
        virtual AbstractShape* Clone() const = 0;
        virtual AbstractShape* Move(const Vector& vector) = 0;
        virtual void Print(std::ostream& out) const = 0;
    };
 
    class Point : public AbstractShape {
        private:
            double x_ = 0;
            double y_ = 0;
        public:
            Point() = default;
            Point(double x, double y) : x_(x), y_(y) {}
            double X() const { return x_; }
            double Y() const { return y_; }
            AbstractShape* Clone() const override {
                return new Point(*this);
            }
            AbstractShape* Move(const Vector& vector) override;
            bool ContainsPoint(const Point& point) const override {
                return (x_ == point.x_ && y_ == point.y_);
            }
            bool CrossSegment(const Segment& segment) const override;
            void Print(std::ostream& out) const override {
                std::cout << "Point(" << x_ << ", " << y_ << ")" << std::endl;
            }
    };
 
    class Segment : public AbstractShape {
        // implement
    };
 
    class Line : public AbstractShape {
        // implement
    };
 
    class Ray : public AbstractShape {
        // implement
    };
 
    class Polygon : public AbstractShape {
        // implement
    };
 
    class Circle : public AbstractShape {
        //implement
    };
}
 
 
void CheckFunctions(const geometry::AbstractShape* shape, const geometry::Point& A, const geometry::Point& B) {
    if (shape->ContainsPoint(A)) {
        std::cout << "Given shape contains point A" << std::endl;
    } else {
        std::cout << "Given shape does not contain point A" << std::endl;
    }
 
    // //geometry::Segment AB(A, B);
    // if (shape->CrossSegment(AB)) {
    //     std::cout << "Given shape crosses segment AB" << std::endl;
    // } else {
    //     std::cout << "Given shape does not cross segment AB" << std::endl;
    // }
 
    geometry::Vector ab(A, B);
    geometry::AbstractShape* clonedShape = shape->Clone();
    clonedShape->Move(ab)->Print(std::cout);
    delete clonedShape;
}
 
int main() {
    geometry::AbstractShape* shape;
    char command[10];
    std::cin >> command;
    if (!strcmp(command, "point")) {
        int x, y;
        std::cin >> x >> y;
        shape = new geometry::Point(x, y);
    // } else if (!strcmp(command, "segment")) {
    //     int x1, y1, x2, y2;
    //     std::cin >> x1 >> y1 >> x2 >> y2;
    //     shape = new geometry::Segment(geometry::Point(x1, y1), geometry::Point(x2, y2));
    // } else if (!strcmp(command, "ray")) {
    //     int x1, y1, x2, y2;
    //     std::cin >> x1 >> y1 >> x2 >> y2;
    //     shape = new geometry::Ray(geometry::Point(x1, y1), geometry::Point(x2, y2));
    // } else if (!strcmp(command, "line")) {
    //     int x1, y1, x2, y2;
    //     std::cin >> x1 >> y1 >> x2 >> y2;
    //     shape = new geometry::Line(geometry::Point(x1, y1), geometry::Point(x2, y2));
    // } else if (!strcmp(command, "polygon")) {
    //     size_t n_points;
    //     std::cin >> n_points;
    //     std::vector<geometry::Point> points;
    //     points.reserve(n_points);
    //     for (size_t i = 0; i < n_points; ++i) {
    //         int x, y;
    //         std::cin >> x >> y;
    //         points.push_back(geometry::Point(x, y));
    //     }
    //     shape = new geometry::Polygon(points, n_points);
    // } else if (!strcmp(command, "circle")) {
    //     int x, y;
    //     std::cin >> x >> y;
    //     Point center(x, y);
    //     int radius;
    //     std::cin >> radius;
    //     shape = new geometry::Circle(center, radius);
    // } else { 
    //     std::cerr << "Undefined command" << std::endl;
    //     return 1;
    }
 
    int ax, ay, bx, by;
    std::cin >> ax >> ay >> bx >> by;
    geometry::Point A(ax, ay), B(bx, by);
 
    CheckFunctions(shape, A, B);
 
    return 0;
}