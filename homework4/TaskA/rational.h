#pragma once
#include <iostream>
#include <stdexcept>

class RationalDivisionByZero : public std::runtime_error {
public:
  RationalDivisionByZero() : std::runtime_error("Division by zero") {}
};

class Rational {
public:
  Rational();
  Rational(int value); // NOLINT
  Rational(int numerator, int denominator);

  int GetNumerator() const;
  int GetDenominator() const;

  void SetNumerator(int numerator);
  void SetDenominator(int denominator);

  Rational &operator+=(const Rational &other);
  Rational &operator-=(const Rational &other);
  Rational &operator*=(const Rational &other);
  Rational &operator/=(const Rational &other);

  Rational operator+() const;
  Rational operator-() const;

  Rational &operator++();   // префикс
  Rational operator++(int); // постфикс
  Rational &operator--();
  Rational operator--(int);

  friend Rational operator+(Rational lhs, const Rational &rhs);
  friend Rational operator-(Rational lhs, const Rational &rhs);
  friend Rational operator*(Rational lhs, const Rational &rhs);
  friend Rational operator/(Rational lhs, const Rational &rhs);

  friend bool operator==(const Rational &lhs, const Rational &rhs);
  friend bool operator!=(const Rational &lhs, const Rational &rhs);
  friend bool operator<(const Rational &lhs, const Rational &rhs);
  friend bool operator<=(const Rational &lhs, const Rational &rhs);
  friend bool operator>(const Rational &lhs, const Rational &rhs);
  friend bool operator>=(const Rational &lhs, const Rational &rhs);

  friend std::ostream &operator<<(std::ostream &os, const Rational &value);
  friend std::istream &operator>>(std::istream &is, Rational &value);

private:
  int numerator_;
  int denominator_;

  void Normalize();
};
