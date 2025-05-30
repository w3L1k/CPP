#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <cstdint>

class BigIntegerOverflow : public std::runtime_error {
 public:
  BigIntegerOverflow() : std::runtime_error("BigInteger overflow") {
  }
};

class BigIntegerDivisionByZero : public std::runtime_error {
 public:
  BigIntegerDivisionByZero() : std::runtime_error("Division by zero") {
  }
};

class BigInteger {
 private:
  std::vector<int> digits_;
  bool is_negative_;

  static const int kBASE = 10000;
  static const int kBaseDigits = 4;

 public:
  BigInteger();
  BigInteger(int value);      // NOLINT
  BigInteger(int64_t value);  // NOLINT
  explicit BigInteger(const char* value);
  explicit BigInteger(const std::string& value);

  BigInteger(const BigInteger& other) = default;
  BigInteger(BigInteger&& other) noexcept;

  bool IsNegative() const;
  BigInteger Abs() const;

  BigInteger operator+() const;
  BigInteger operator-() const;

  BigInteger& operator+=(const BigInteger& other);
  BigInteger& operator-=(const BigInteger& other);
  BigInteger& operator*=(const BigInteger& other);

  BigInteger& operator=(int value);
  BigInteger& operator=(const BigInteger& other);
  BigInteger& operator=(BigInteger&& other) noexcept;

  friend BigInteger operator+(BigInteger lhs, const BigInteger& rhs);
  friend BigInteger operator-(BigInteger lhs, const BigInteger& rhs);
  friend BigInteger operator*(BigInteger lhs, const BigInteger& rhs);


  BigInteger& operator++();
  BigInteger operator++(int);
  BigInteger& operator--();
  BigInteger operator--(int);

  explicit operator bool() const;

  friend bool operator==(const BigInteger& lhs, const BigInteger& rhs);
  friend bool operator!=(const BigInteger& lhs, const BigInteger& rhs);
  friend bool operator<(const BigInteger& lhs, const BigInteger& rhs);
  friend bool operator<=(const BigInteger& lhs, const BigInteger& rhs);
  friend bool operator>(const BigInteger& lhs, const BigInteger& rhs);
  friend bool operator>=(const BigInteger& lhs, const BigInteger& rhs);

  friend std::ostream& operator<<(std::ostream& os, const BigInteger& value);
  friend std::istream& operator>>(std::istream& is, BigInteger& value);

 private:
  void Trim();
  void FromString(const std::string& value);
  size_t DigitCount() const;
};