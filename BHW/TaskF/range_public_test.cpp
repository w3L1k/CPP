#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "range.h"
#include "range.h"  // check include guards

TEST_CASE("End", "[Range]") {
  const int end = 5;

  {
    int i = 0;
    for (auto x : Range(end)) {
      REQUIRE(x == i);
      ++i;
    }
    REQUIRE(i == end);
  }

  {
    const auto range = Range(end);
    int i = 0;
    for (auto x : range) {
      REQUIRE(x == i);
      ++i;
    }
    REQUIRE(i == end);
  }

  {
    for ([[maybe_unused]] auto x : Range(0)) {
      REQUIRE(false);
    }

    for ([[maybe_unused]] auto x : Range(-1)) {
      REQUIRE(false);
    }
  }
}

TEST_CASE("BeginEnd", "[Range]") {
  const int begin = -2;
  const int end = 5;

  {
    int i = begin;
    for (auto x : Range(begin, end)) {
      REQUIRE(x == i);
      ++i;
    }
    REQUIRE(i == end);
  }

  {
    const auto range = Range(begin, end);
    int i = begin;
    for (auto x : range) {
      REQUIRE(x == i);
      ++i;
    }
    REQUIRE(i == end);
  }

  {
    for ([[maybe_unused]] auto x : Range(2, 2)) {
      REQUIRE(false);
    }

    for ([[maybe_unused]] auto x : Range(2, -1)) {
      REQUIRE(false);
    }
  }
}

TEST_CASE("StepOne", "[Range]") {
  const int begin = -2;
  const int end = 5;
  const int step = 1;

  {
    int i = begin;
    for (auto x : Range(begin, end, step)) {
      REQUIRE(x == i);
      i += step;
    }
    REQUIRE(i == end);
  }

  {
    const auto range = Range(begin, end, step);
    int i = begin;
    for (auto x : range) {
      REQUIRE(x == i);
      i += step;
    }
    REQUIRE(i == end);
  }

  {
    for ([[maybe_unused]] auto x : Range(2, 2, 1)) {
      REQUIRE(false);
    }

    for ([[maybe_unused]] auto x : Range(2, -1, 1)) {
      REQUIRE(false);
    }
  }
}

TEST_CASE("StepMinusOne", "[Range]") {
  const int begin = 5;
  const int end = -2;
  const int step = -1;

  {
    int i = begin;
    for (auto x : Range(begin, end, step)) {
      REQUIRE(x == i);
      i += step;
    }
    REQUIRE(i == end);
  }

  {
    const auto range = Range(begin, end, step);
    int i = begin;
    for (auto x : range) {
      REQUIRE(x == i);
      i += step;
    }
    REQUIRE(i == end);
  }

  {
    for ([[maybe_unused]] auto x : Range(2, 2, -1)) {
      REQUIRE(false);
    }

    for ([[maybe_unused]] auto x : Range(2, 4, -1)) {
      REQUIRE(false);
    }
  }
}

TEST_CASE("PositiveStepDividesDistance", "[Range]") {  // step > 0, (end - begin) % step == 0
  const int begin = -4;
  const int end = 8;
  const int step = 3;

  {
    int i = begin;
    for (auto x : Range(begin, end, step)) {
      REQUIRE(x == i);
      i += step;
    }
    REQUIRE(i == end);
  }

  {
    const auto range = Range(begin, end, step);
    int i = begin;
    for (auto x : range) {
      REQUIRE(x == i);
      i += step;
    }
    REQUIRE(i == end);
  }

  {
    for ([[maybe_unused]] auto x : Range(2, 2, 2)) {
      REQUIRE(false);
    }

    for ([[maybe_unused]] auto x : Range(2, -4, 2)) {
      REQUIRE(false);
    }
  }
}

TEST_CASE("NegativeStepDividesDistance", "[Range]") {  // step < 0, (end - begin) % step == 0
  const int begin = 8;
  const int end = -4;
  const int step = -3;

  {
    int i = begin;
    for (auto x : Range(begin, end, step)) {
      REQUIRE(x == i);
      i += step;
    }
    REQUIRE(i == end);
  }

  {
    const auto range = Range(begin, end, step);
    int i = begin;
    for (auto x : range) {
      REQUIRE(x == i);
      i += step;
    }
    REQUIRE(i == end);
  }

  {
    for ([[maybe_unused]] auto x : Range(2, 2, -2)) {
      REQUIRE(false);
    }

    for ([[maybe_unused]] auto x : Range(2, 4, -2)) {
      REQUIRE(false);
    }
  }
}

TEST_CASE("ArbitraryPositiveStep", "[Range]") {  // step > 0, (end - begin) % step != 0
  const int begin = -7;
  const int end = 19;
  const int step = 5;

  {
    int i = begin;
    for (auto x : Range(begin, end, step)) {
      REQUIRE(x == i);
      i += step;
    }
    REQUIRE(i == begin + (end - begin + step - 1) / step * step);
  }

  {
    const auto range = Range(begin, end, step);
    int i = begin;
    for (auto x : range) {
      REQUIRE(x == i);
      i += step;
    }
    REQUIRE(i == begin + (end - begin + step - 1) / step * step);
  }

  {
    for ([[maybe_unused]] auto x : Range(2, 2, 3)) {
      REQUIRE(false);
    }

    for ([[maybe_unused]] auto x : Range(2, -4, 5)) {
      REQUIRE(false);
    }
  }
}

TEST_CASE("ArbitraryNegativeStep", "[Range]") {  // step < 0, (end - begin) % step != 0
  const int begin = 8;
  const int end = -14;
  const int step = -4;

  {
    int i = begin;
    for (auto x : Range(begin, end, step)) {
      REQUIRE(x == i);
      i += step;
    }
    REQUIRE(i == begin + (end - begin + step - 1) / step * step);
  }

  {
    const auto range = Range(begin, end, step);
    int i = begin;
    for (auto x : range) {
      REQUIRE(x == i);
      i += step;
    }
    REQUIRE(i == begin + (end - begin + step - 1) / step * step);
  }

  {
    for ([[maybe_unused]] auto x : Range(2, 2, -3)) {
      REQUIRE(false);
    }

    for ([[maybe_unused]] auto x : Range(2, 7, -3)) {
      REQUIRE(false);
    }
  }
}

TEST_CASE("ZeroStep", "[Range]") {
  for ([[maybe_unused]] auto x : Range(2, 2, 0)) {
    REQUIRE(false);
  }

  for ([[maybe_unused]] auto x : Range(2, 5, 0)) {
    REQUIRE(false);
  }

  for ([[maybe_unused]] auto x : Range(2, -7, 0)) {
    REQUIRE(false);
  }
}

TEST_CASE("SequenceIsGenerated", "[Range]") {
  for ([[maybe_unused]] auto x : Range(std::numeric_limits<int>::max())) {
    REQUIRE(true);
    break;
  }

  for ([[maybe_unused]] auto x : Range(4, std::numeric_limits<int>::max())) {
    REQUIRE(true);
    break;
  }

  for ([[maybe_unused]] auto x : Range(10, std::numeric_limits<int>::max(), 3)) {
    REQUIRE(true);
    break;
  }

  for ([[maybe_unused]] auto x : Range(std::numeric_limits<int>::max(), std::numeric_limits<int>::min(), -1)) {
    REQUIRE(true);
    break;
  }
}

#ifdef REVERSE_RANGE_IMPLEMENTED

TEST_CASE("ReverseEnd", "[ReverseRange]") {
  const int end = 5;

  const auto range = Range(end);
  int i = end - 1;
  for (auto it = range.rbegin(); it != range.rend(); ++it) {
    REQUIRE(*it == i);
    --i;
  }
  REQUIRE(i == -1);

  for ([[maybe_unused]] auto it = Range(0).rbegin(); it != Range(0).rend(); ++it) {
    REQUIRE(false);
  }

  for ([[maybe_unused]] auto it = Range(-1).rbegin(); it != Range(-1).rend(); ++it) {
    REQUIRE(false);
  }
}

TEST_CASE("ReverseBeginEnd", "[ReverseRange]") {
  const int begin = -2;
  const int end = 5;

  const auto range = Range(begin, end);
  int i = end - 1;
  for (auto it = range.rbegin(); it != range.rend(); ++it) {
    REQUIRE(*it == i);
    --i;
  }
  REQUIRE(i == begin - 1);

  for ([[maybe_unused]] auto it = Range(2, 2).rbegin(); it != Range(2, 2).rend(); ++it) {
    REQUIRE(false);
  }

  for ([[maybe_unused]] auto it = Range(2, -1).rbegin(); it != Range(2, -1).rend(); ++it) {
    REQUIRE(false);
  }
}

TEST_CASE("ReverseStepOne", "[ReverseRange]") {
  const int begin = -2;
  const int end = 5;
  const int step = 1;

  const auto range = Range(begin, end, step);
  int i = end - step;
  for (auto it = range.rbegin(); it != range.rend(); ++it) {
    REQUIRE(*it == i);
    i -= step;
  }
  REQUIRE(i == begin - step);

  for ([[maybe_unused]] auto it = Range(2, 2, 1).rbegin(); it != Range(2, 2, 1).rend(); ++it) {
    REQUIRE(false);
  }

  for ([[maybe_unused]] auto it = Range(2, -1, 1).rbegin(); it != Range(2, -1, 1).rend(); ++it) {
    REQUIRE(false);
  }
}

TEST_CASE("ReverseStepMinusOne", "[ReverseRange]") {
  const int begin = 5;
  const int end = -2;
  const int step = -1;

  const auto range = Range(begin, end, step);
  int i = end - step;
  for (auto it = range.rbegin(); it != range.rend(); ++it) {
    REQUIRE(*it == i);
    i -= step;
  }
  REQUIRE(i == begin - step);

  for ([[maybe_unused]] auto it = Range(2, 2, -1).rbegin(); it != Range(2, 2, -1).rend(); ++it) {
    REQUIRE(false);
  }

  for ([[maybe_unused]] auto it = Range(2, 4, -1).rbegin(); it != Range(2, 4, -1).rend(); ++it) {
    REQUIRE(false);
  }
}

TEST_CASE("ReversePositiveStepDividesDistance", "[ReverseRange]") {  // step > 0, (end - begin) % step == 0
  const int begin = -4;
  const int end = 8;
  const int step = 3;

  const auto range = Range(begin, end, step);
  int i = end - step;
  for (auto it = range.rbegin(); it != range.rend(); ++it) {
    REQUIRE(*it == i);
    i -= step;
  }
  REQUIRE(i == begin - step);

  for ([[maybe_unused]] auto it = Range(2, 2, 2).rbegin(); it != Range(2, 2, 2).rend(); ++it) {
    REQUIRE(false);
  }

  for ([[maybe_unused]] auto it = Range(2, -4, 2).rbegin(); it != Range(2, -4, 2).rend(); ++it) {
    REQUIRE(false);
  }
}

TEST_CASE("ReverseNegativeStepDividesDistance", "[ReverseRange]") {  // step < 0, (end - begin) % step == 0
  const int begin = 8;
  const int end = -4;
  const int step = -3;

  const auto range = Range(begin, end, step);
  int i = end - step;
  for (auto it = range.rbegin(); it != range.rend(); ++it) {
    REQUIRE(*it == i);
    i -= step;
  }
  REQUIRE(i == begin - step);

  for ([[maybe_unused]] auto it = Range(2, 2, -2).rbegin(); it != Range(2, 2, -2).rend(); ++it) {
    REQUIRE(false);
  }

  for ([[maybe_unused]] auto it = Range(2, 4, -2).rbegin(); it != Range(2, 4, -2).rend(); ++it) {
    REQUIRE(false);
  }
}

TEST_CASE("ReverseArbitraryPositiveStep", "[ReverseRange]") {  // step > 0, (end - begin) % step != 0
  const int begin = -7;
  const int end = 19;
  const int step = 5;

  const auto range = Range(begin, end, step);
  int i = begin + (end - begin + step - 1) / step * step - step;
  for (auto it = range.rbegin(); it != range.rend(); ++it) {
    REQUIRE(*it == i);
    i -= step;
  }
  REQUIRE(i == begin - step);

  for ([[maybe_unused]] auto it = Range(2, 2, 3).rbegin(); it != Range(2, 2, 3).rend(); ++it) {
    REQUIRE(false);
  }

  for ([[maybe_unused]] auto it = Range(2, -4, 5).rbegin(); it != Range(2, -4, 5).rend(); ++it) {
    REQUIRE(false);
  }
}

TEST_CASE("ReverseArbitraryNegativeStep", "[ReverseRange]") {  // step < 0, (end - begin) % step != 0
  const int begin = 8;
  const int end = -14;
  const int step = -4;

  const auto range = Range(begin, end, step);
  int i = begin + (end - begin + step - 1) / step * step - step;
  for (auto it = range.rbegin(); it != range.rend(); ++it) {
    REQUIRE(*it == i);
    i -= step;
  }
  REQUIRE(i == begin - step);

  for ([[maybe_unused]] auto it = Range(2, 2, -3).rbegin(); it != Range(2, 2, -3).rend(); ++it) {
    REQUIRE(false);
  }

  for ([[maybe_unused]] auto it = Range(2, 7, -3).rbegin(); it != Range(2, 7, -3).rend(); ++it) {
    REQUIRE(false);
  }
}

TEST_CASE("ReverseZeroStep", "[ReverseRange]") {
  for ([[maybe_unused]] auto it = Range(2, 2, 0).rbegin(); it != Range(2, 2, 0).rend(); ++it) {
    REQUIRE(false);
  }

  for ([[maybe_unused]] auto it = Range(2, 5, 0).rbegin(); it != Range(2, 5, 0).rend(); ++it) {
    REQUIRE(false);
  }

  for ([[maybe_unused]] auto it = Range(2, -7, 0).rbegin(); it != Range(2, -7, 0).rend(); ++it) {
    REQUIRE(false);
  }
}

#endif  // REVERSE_RANGE_IMPLEMENTED
