#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <cstdint>

class BigIntegerOverflow : public std::runtime_error {
 public:
  BigIntegerOverflow() : std::runtime_error("BigIntegerOverflow") {}
};

class BigIntegerDivisionByZero : public std::runtime_error {
 public:
  BigIntegerDivisionByZero() : std::runtime_error("BigIntegerDivisionByZero") {}
};

class BigInteger {
 public:
  BigInteger();
  BigInteger(int value);
  BigInteger(long long value);
  BigInteger(const char* str);
  BigInteger(const std::string& str);

  bool IsNegative() const;

  BigInteger operator+() const;
  BigInteger operator-() const;

  BigInteger& operator+=(const BigInteger& other);
  BigInteger& operator-=(const BigInteger& other);
  BigInteger& operator*=(const BigInteger& other);

  BigInteger& operator+=(int other);
  BigInteger& operator-=(int other);
  BigInteger& operator*=(int other);

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

  friend std::ostream& operator<<(std::ostream& out, const BigInteger& value);
  friend std::istream& operator>>(std::istream& in, BigInteger& value);

 private:
  using DigitType = uint16_t;
  using DoubleDigitType = uint32_t;

  static const int BASE;
  static const int BASE_DIGITS;
  static const int MAX_DECIMAL_DIGITS;

  std::vector<DigitType> digits_;
  bool is_negative_ = false;

  void RemoveLeadingZeros();
  int DecimalDigitCount() const;

  int CompareAbs(const BigInteger& other) const;
  BigInteger AddUnsigned(const BigInteger& other) const;
  BigInteger SubtractUnsigned(const BigInteger& other) const;
};

BigInteger operator+(BigInteger lhs, const BigInteger& rhs);
BigInteger operator-(BigInteger lhs, const BigInteger& rhs);
BigInteger operator*(BigInteger lhs, const BigInteger& rhs);

BigInteger operator+(BigInteger lhs, int rhs);
BigInteger operator-(BigInteger lhs, int rhs);
BigInteger operator*(BigInteger lhs, int rhs);

#endif // BIG_INTEGER_H
