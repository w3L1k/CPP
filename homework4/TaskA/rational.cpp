#include "rational.h"
#include <numeric> // std::gcd
#include <sstream>

Rational::Rational() : numerator_(0), denominator_(1) {}

Rational::Rational(int value) : numerator_(value), denominator_(1) {} // NOLINT

Rational::Rational(int numerator, int denominator) {
  if (denominator == 0) {
    throw RationalDivisionByZero();
  }
  numerator_ = numerator;
  denominator_ = denominator;
  Normalize();
}

int Rational::GetNumerator() const { return numerator_; }

int Rational::GetDenominator() const { return denominator_; }

void Rational::SetNumerator(int numerator) {
  numerator_ = numerator;
  Normalize();
}

void Rational::SetDenominator(int denominator) {
  if (denominator == 0){
    throw RationalDivisionByZero();
  }
  denominator_ = denominator;
  Normalize();
}

void Rational::Normalize() {
  int gcd = std::gcd(numerator_, denominator_);
  numerator_ /= gcd;
  denominator_ /= gcd;
  if (denominator_ < 0) {
    numerator_ = -numerator_;
    denominator_ = -denominator_;
  }
}

Rational &Rational::operator+=(const Rational &other) {
  numerator_ =
      numerator_ * other.denominator_ + other.numerator_ * denominator_;
  denominator_ *= other.denominator_;
  Normalize();
  return *this;
}

Rational &Rational::operator-=(const Rational &other) {
  numerator_ =
      numerator_ * other.denominator_ - other.numerator_ * denominator_;
  denominator_ *= other.denominator_;
  Normalize();
  return *this;
}

Rational &Rational::operator*=(const Rational &other) {
  numerator_ *= other.numerator_;
  denominator_ *= other.denominator_;
  Normalize();
  return *this;
}

Rational &Rational::operator/=(const Rational &other) {
  if (other.numerator_ == 0) {
    throw RationalDivisionByZero();
  }
  numerator_ *= other.denominator_;
  denominator_ *= other.numerator_;
  Normalize();
  return *this;
}

Rational Rational::operator+() const { 
  return *this; 
}
Rational Rational::operator-() const {
  return {
    Rational(-numerator_, denominator_)
  };
}

Rational &Rational::operator++() {
  *this += Rational(1);
  return *this;
}

Rational Rational::operator++(int) {
  Rational temp = *this;
  ++(*this);
  return temp;
}

Rational &Rational::operator--() {
  *this -= Rational(1);
  return *this;
}

Rational Rational::operator--(int) {
  Rational temp = *this;
  --(*this);
  return temp;
}


Rational operator+(Rational lhs, const Rational &rhs) { return lhs += rhs; }

Rational operator-(Rational lhs, const Rational &rhs) { return lhs -= rhs; }

Rational operator*(Rational lhs, const Rational &rhs) { return lhs *= rhs; }

Rational operator/(Rational lhs, const Rational &rhs) { return lhs /= rhs; }

bool operator==(const Rational &lhs, const Rational &rhs) {
  return lhs.numerator_ == rhs.numerator_ &&
         lhs.denominator_ == rhs.denominator_;
}

bool operator!=(const Rational &lhs, const Rational &rhs) {
  return !(lhs == rhs);
}

bool operator<(const Rational &lhs, const Rational &rhs) {
  return lhs.numerator_ * rhs.denominator_ < rhs.numerator_ * lhs.denominator_;
}

bool operator<=(const Rational &lhs, const Rational &rhs) {
  return !(rhs < lhs);
}

bool operator>(const Rational &lhs, const Rational &rhs) { 
  return rhs < lhs;
}

bool operator>=(const Rational &lhs, const Rational &rhs) {
  return !(lhs < rhs);
}

std::ostream &operator<<(std::ostream &os, const Rational &value) {
  os << value.numerator_;
  if (value.denominator_ != 1) {
    os << "/" << value.denominator_;
  }
  return os;
}

std::istream &operator>>(std::istream &is, Rational &value) {
  std::string token;
  is >> token;
  std::istringstream ss(token);
  int num = 0;
  int denom = 1;
  char delim = 0;
  if (ss >> num) {
    if (ss >> delim && delim == '/' && ss >> denom) {
      value = Rational(num, denom);
    } else {
      value = Rational(num);
    }
  }
  return is;
}
