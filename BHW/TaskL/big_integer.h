#pragma once
#include <stdexcept>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <iostream>

class BigIntegerOverflow : public std::runtime_error {
 public:
  BigIntegerOverflow() : std::runtime_error("BigIntegerOverflow") {
  }
};

class BigIntegerDivisionByZero : public std::runtime_error {
 public:
  BigIntegerDivisionByZero() : std::runtime_error("BigIntegerDivisionByZero") {
  }
};

class BigInteger {
  public:
    BigInteger();
    BigInteger(uint64_t value);
    explicit BigInteger(const char* str);
    bool IsNegative() const;

    BigInteger operator+() const;
    BigInteger operator-() const;

    BigInteger& operator+=(const BigInteger& rhs);
    BigInteger& operator-=(const BigInteger& rhs);
    BigInteger& operator*=(const BigInteger& rhs);

    BigInteger operator+(const BigInteger& rhs) const;
    BigInteger operator-(const BigInteger& rhs) const;
    BigInteger operator*(const BigInteger& rhs) const;

    BigInteger& operator++();
    BigInteger operator++(int);
    BigInteger& operator--();
    BigInteger operator--(int);

    explicit operator bool() const;

    friend bool operator==(const BigInteger& a, const BigInteger& b);
    friend bool operator!=(const BigInteger& a, const BigInteger& b);
    friend bool operator<(const BigInteger& a, const BigInteger& b);
    friend bool operator>(const BigInteger& a, const BigInteger& b);
    friend bool operator<=(const BigInteger& a, const BigInteger& b);
    friend bool operator>=(const BigInteger& a, const BigInteger& b);

    friend std::ostream& operator<<(std::ostream& out, const BigInteger& val);
    friend std::istream& operator>>(std::istream& in, BigInteger& val);
  private:
    static const uint64_t BASE = 1000000000;
    static const int BASE_DIGITS = 9;
    std::vector<uint32_t> digits_;
    bool is_negative_;

    void RemoveLeadingZeros();
    int CompareMagnitude(const BigInteger& other) const;
};
