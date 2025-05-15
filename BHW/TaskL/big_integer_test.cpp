#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>

#include "big_integer.h"
#include "big_integer.h"  // check include guards

TEST_CASE("Constructors") {
  std::ostringstream oss;

  BigInteger a(100050008);
  oss << a << '\n';

  BigInteger b(-9000000002);
  oss << b << '\n';

  std::string x_str("1234056789837693278967293875983479857354986798379643835986743598760346745869837498567983769837");
  BigInteger x(x_str.c_str());
  oss << x << '\n';

  std::string y_str("-893749834789698437683498584389573498678943769847398567984327647967984758974398678489509280024");
  BigInteger y(y_str.c_str());
  oss << y << '\n';

  std::string z_str("+102850932486325804128692015804067243109794869810234630820960236842390602398968209386023860120");
  BigInteger z(z_str.c_str());
  oss << z << '\n';

  REQUIRE_FALSE(a.IsNegative());
  REQUIRE(b.IsNegative());
  REQUIRE_FALSE(x.IsNegative());
  REQUIRE(y.IsNegative());
  REQUIRE_FALSE(z.IsNegative());

  REQUIRE(oss.str() == std::string("100050008\n") + std::string("-9000000002\n") + x_str + "\n" + y_str + "\n" +
                           z_str.substr(1) + "\n");
}

TEST_CASE("UnaryOperators") {
  std::istringstream iss("1234567890123456789012345 -1245673456789345012389012");
  std::ostringstream oss;

  BigInteger a;
  BigInteger b;
  iss >> a >> b;

  oss << +a << ' ' << +b << '\n';
  oss << -a << ' ' << -b << '\n';
  REQUIRE(
      oss.str() ==
      "1234567890123456789012345 -1245673456789345012389012\n-1234567890123456789012345 1245673456789345012389012\n");
}

TEST_CASE("CompoundAdd") {
  BigInteger x(193);
  x += x;
  REQUIRE(x == BigInteger(386));
  (x += x) = BigInteger(-11);
  REQUIRE(x == BigInteger(-11));
  x += BigInteger(11);
  REQUIRE(x == BigInteger(0));
  REQUIRE_FALSE(x.IsNegative());
}

TEST_CASE("Sum") {
  const std::string large(24, '9');
  const std::string res = "1" + std::string(23, '9') + "8";
  REQUIRE(BigInteger(1234567890) + BigInteger(987654321) == BigInteger("2222222211"));
  REQUIRE(BigInteger(large.c_str()) + BigInteger(large.c_str()) == BigInteger(res.c_str()));
  REQUIRE(-BigInteger(large.c_str()) + -BigInteger(large.c_str()) == -BigInteger(res.c_str()));
  REQUIRE(BigInteger(res.c_str()) + -BigInteger(large.c_str()) == BigInteger(large.c_str()));
  REQUIRE(-BigInteger(res.c_str()) + BigInteger(large.c_str()) == -BigInteger(large.c_str()));
}

TEST_CASE("CompoundSubtract") {
  BigInteger x(193);
  x -= -x;
  REQUIRE(x == BigInteger(386));
  (x -= x) = BigInteger(-11);
  REQUIRE(x == BigInteger(-11));
  x -= BigInteger(-11);
  REQUIRE(x == BigInteger(0));
  REQUIRE_FALSE(x.IsNegative());
}

TEST_CASE("Subtraction") {
  const std::string large(24, '9');
  const std::string res = "1" + std::string(23, '9') + "8";
  REQUIRE(BigInteger(1234567890) - BigInteger(987654321) == BigInteger("246913569"));
  REQUIRE(BigInteger(res.c_str()) - BigInteger(large.c_str()) == BigInteger(large.c_str()));
  REQUIRE(-BigInteger(res.c_str()) - -BigInteger(large.c_str()) == -BigInteger(large.c_str()));
  REQUIRE(BigInteger(large.c_str()) - -BigInteger(large.c_str()) == BigInteger(res.c_str()));
  REQUIRE(-BigInteger(large.c_str()) - BigInteger(large.c_str()) == -BigInteger(res.c_str()));
}

TEST_CASE("CompoundMultiply") {
  BigInteger x(193);
  x *= -x;
  REQUIRE(x == BigInteger(-37249));
  (x *= x) = BigInteger(-11);
  REQUIRE(x == BigInteger(-11));
  x *= BigInteger(0);
  REQUIRE(x == BigInteger(0));
  REQUIRE_FALSE(x.IsNegative());
}

TEST_CASE("Multiplication") {
  const std::string large(24, '9');
  const BigInteger x(1234567890);
  const BigInteger y(9876543210);
  const BigInteger res("12193263111263526900");
  REQUIRE(x * y == res);
  REQUIRE(x * -y == -res);
  REQUIRE(-x * y == -res);
  REQUIRE(-x * -y == res);
  REQUIRE_THROWS_AS((void)(BigInteger(std::string(50'000, '1').c_str()) * BigInteger(large.c_str())),
                    BigIntegerOverflow);  // NOLINT
}

TEST_CASE("Increment") {
  BigInteger x = 0;
  REQUIRE(++x == BigInteger(1));
  REQUIRE(x++ == BigInteger(1));
  REQUIRE(x == BigInteger(2));
  ++x = 0;
  REQUIRE(x == BigInteger(0));
  (void)(--x)++;
  REQUIRE(x == BigInteger(0));
  REQUIRE_FALSE(x.IsNegative());
}

TEST_CASE("Decrement") {
  BigInteger x = 0;
  REQUIRE(--x == BigInteger(-1));
  REQUIRE(x-- == BigInteger(-1));
  REQUIRE(x == BigInteger(-2));
  --x = 0;
  REQUIRE(x == BigInteger(0));
  (void)(++x)--;
  REQUIRE(x == BigInteger(0));
  REQUIRE_FALSE(x.IsNegative());
}

template <class T>
void CheckComparisonEqual(const T& lhs, const T& rhs) {
  REQUIRE(lhs == rhs);
  REQUIRE(lhs <= rhs);
  REQUIRE(lhs >= rhs);
  REQUIRE_FALSE(lhs != rhs);
  REQUIRE_FALSE(lhs < rhs);
  REQUIRE_FALSE(lhs > rhs);
}

template <class T>
void CheckComparisonLess(const T& lhs, const T& rhs) {
  REQUIRE_FALSE(lhs == rhs);
  REQUIRE(lhs <= rhs);
  REQUIRE_FALSE(lhs >= rhs);
  REQUIRE(lhs != rhs);
  REQUIRE(lhs < rhs);
  REQUIRE_FALSE(lhs > rhs);
}

template <class T>
void CheckComparisonGreater(const T& lhs, const T& rhs) {
  REQUIRE_FALSE(lhs == rhs);
  REQUIRE_FALSE(lhs <= rhs);
  REQUIRE(lhs >= rhs);
  REQUIRE(lhs != rhs);
  REQUIRE_FALSE(lhs < rhs);
  REQUIRE(lhs > rhs);
}

TEST_CASE("RelationalOperators") {
  const BigInteger positive("1234567890123456789");
  const auto positive_copy = positive;
  const BigInteger negative("-9876543210987654321");
  const auto negative_copy = negative;
  const BigInteger zero(0);

  CheckComparisonLess(negative, zero);
  CheckComparisonLess(negative, positive);
  CheckComparisonLess(zero, positive);

  CheckComparisonGreater(zero, negative);
  CheckComparisonGreater(positive, negative);
  CheckComparisonGreater(positive, zero);

  CheckComparisonEqual(zero, zero);
  CheckComparisonEqual(positive, positive);
  CheckComparisonEqual(negative, negative);

  CheckComparisonEqual(positive, positive_copy);
  CheckComparisonEqual(negative_copy, negative);
}

#ifdef BIG_INTEGER_DIVISION_IMPLEMENTED

TEST_CASE("CompoundDivision") {
  BigInteger x(193);
  x /= BigInteger(-5);
  REQUIRE(x == BigInteger(-38));
  (x /= x) = BigInteger(-11);
  REQUIRE(x == BigInteger(-11));
  x /= BigInteger(3);
  REQUIRE(x == BigInteger(-3));
  REQUIRE_THROWS_AS(x /= BigInteger(0), BigIntegerDivisionByZero);  // NOLINT
}

TEST_CASE("Division") {
  const BigInteger x(1234567890);
  const BigInteger y(9876543210);

  REQUIRE(x / y == BigInteger(0));
  REQUIRE(x / -y == BigInteger(0));
  REQUIRE(-x / y == BigInteger(0));
  REQUIRE(-x / -y == BigInteger(0));

  REQUIRE(y / x == BigInteger(8));
  REQUIRE(y / -x == BigInteger(-8));
  REQUIRE(-y / x == BigInteger(-8));
  REQUIRE(-y / -x == BigInteger(8));
}

TEST_CASE("CompoundResidual") {
  BigInteger x(193);
  x %= BigInteger(-123);
  REQUIRE(x == BigInteger(70));
  (x %= x) = BigInteger(-11);
  REQUIRE(x == BigInteger(-11));
  x %= BigInteger(3);
  REQUIRE(x == BigInteger(-2));
  REQUIRE_THROWS_AS(x %= BigInteger(0), BigIntegerDivisionByZero);  // NOLINT
}

TEST_CASE("Residual") {
  const BigInteger x(1234567890);
  const BigInteger y(9876543210);

  REQUIRE(x % y == x);
  REQUIRE(x % -y == x);
  REQUIRE(-x % y == -x);
  REQUIRE(-x % -y == -x);

  REQUIRE(y % x == BigInteger(90));
  REQUIRE(y % -x == BigInteger(90));
  REQUIRE(-y % x == BigInteger(-90));
  REQUIRE(-y % -x == BigInteger(-90));
}

#endif  // BIG_INTEGER_DIVISION_IMPLEMENTED
