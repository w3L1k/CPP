#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <array>
#include <iostream>
#include <type_traits>

#include "rational.h"

#include "matrix.h"
#include "matrix.h"  // check include guards

template <class T, size_t N, size_t M>
void EqualMatrix(const Matrix<T, N, M>& matrix, const std::array<std::array<T, M>, N>& arr) {
  for (size_t i = 0u; i < N; ++i) {
    for (size_t j = 0u; j < M; ++j) {
      REQUIRE(matrix(i, j) == arr[i][j]);
    }
  }
}

TEST_CASE("AutomaticStorage", "[MatrixBasics]") {
  static_assert(sizeof(Matrix<int, 1, 1>) == sizeof(int));
  static_assert(sizeof(Matrix<int, 17, 2>) == sizeof(int) * 34);
  static_assert(sizeof(Matrix<double, 13, 3>) == sizeof(double) * 39);
}

TEST_CASE("Size", "[MatrixBasics]") {
  const Matrix<int, 6, 7> matrix{};
  REQUIRE(matrix.RowsNumber() == 6);
  REQUIRE(matrix.ColumnsNumber() == 7);
}

TEST_CASE("Indexing", "[MatrixElementAccess]") {
  Matrix<int, 2, 3> a{};
  a(0, 0) = 1;
  a(1, 1) = -1;
  a(0, 2) = 7;
  EqualMatrix(std::as_const(a), std::array<std::array<int, 3>, 2>{1, 0, 7, 0, -1, 0});

  using ResultType = std::remove_const_t<decltype(std::as_const(a)(0, 0))>;
  static_assert((std::is_same_v<ResultType, const int&> || std::is_same_v<ResultType, int>));
}

TEST_CASE("At", "[MatrixElementAccess]") {
  Matrix<int, 2, 3> a{};
  a.At(0, 0) = 1;
  a.At(1, 1) = -1;
  a.At(0, 2) = 7;
  EqualMatrix(a, std::array<std::array<int, 3>, 2>{1, 0, 7, 0, -1, 0});
  REQUIRE_THROWS_AS(a.At(5, 5), MatrixOutOfRange);  // NOLINT

  using ResultType = std::remove_const_t<decltype(std::as_const(a).At(0, 0))>;
  static_assert((std::is_same_v<ResultType, const int&> || std::is_same_v<ResultType, int>));
}

TEST_CASE("Aggregate", "[MatrixInitialization]") {
  Matrix<int, 2, 2> a{1, 2, -2, -1};
  EqualMatrix(a, std::array<std::array<int, 2>, 2>{1, 2, -2, -1});

  Matrix<char, 1, 3> b{{'a', 'c'}};
  EqualMatrix(b, std::array<std::array<char, 3>, 1>{'a', 'c', '\0'});

  Matrix<int16_t, 3, 1> c{{{-1}, 1}};
  EqualMatrix(c, std::array<std::array<int16_t, 1>, 3>{-1, 1, 0});

  Matrix<Rational, 2, 2> d{{{{0, 2}, {2, 3}}, {{-7, 2}, {1, -1}}}};
  EqualMatrix(
      d, std::array<std::array<Rational, 2>, 2>{{Rational{0, 2}, Rational{2, 3}, Rational{-7, 2}, Rational{-1, 1}}});
}

TEST_CASE("Sum", "[MatrixOperators]") {
  Matrix<Rational, 2, 2> matrix{Rational{3, 4}, Rational{2, 1}, Rational{5, 2}, Rational{0, 1}};
  const Matrix<Rational, 2, 2> delta{Rational{1, 4}, Rational{1, 1}, Rational{-1, 2}, Rational{-1, 1}};

  matrix += delta;
  EqualMatrix(matrix, std::array<std::array<Rational, 2>, 2>{
                          {Rational{1, 1}, Rational{3, 1}, Rational{2, 1}, Rational{-1, 1}}});
  EqualMatrix(matrix += delta, std::array<std::array<Rational, 2>, 2>{
                                   {Rational{5, 4}, Rational{4, 1}, Rational{3, 2}, Rational{-2, 1}}});

  (matrix += delta) = delta;
  EqualMatrix(matrix,
              std::array<std::array<Rational, 2>, 2>{Rational{1, 4}, Rational{1, 1}, Rational{-1, 2}, Rational{-1, 1}});

  EqualMatrix(delta + delta,
              std::array<std::array<Rational, 2>, 2>{Rational{1, 2}, Rational{2, 1}, Rational{-1, 1}, Rational{-2, 1}});
  EqualMatrix(
      delta + Matrix<Rational, 2, 2>{Rational{3, 4}, Rational{2, 1}, Rational{5, 2}, Rational{0, 1}},
      std::array<std::array<Rational, 2>, 2>{{Rational{1, 1}, Rational{3, 1}, Rational{2, 1}, Rational{-1, 1}}});
  EqualMatrix(
      Matrix<Rational, 2, 2>{Rational{3, 4}, Rational{2, 1}, Rational{5, 2}, Rational{0, 1}} + delta,
      std::array<std::array<Rational, 2>, 2>{{Rational{1, 1}, Rational{3, 1}, Rational{2, 1}, Rational{-1, 1}}});

  using ReturnType = std::remove_const_t<decltype(matrix + matrix)>;
  static_assert((std::is_same_v<ReturnType, const Matrix<Rational, 2, 2>&> ||
                 std::is_same_v<ReturnType, Matrix<Rational, 2, 2>>));
}

TEST_CASE("Subtraction", "[MatrixOperators]") {
  Matrix<Rational, 2, 2> matrix{Rational{3, 4}, Rational{2, 1}, Rational{5, 2}, Rational{0, 1}};
  const Matrix<Rational, 2, 2> delta{Rational{1, 4}, Rational{1, 1}, Rational{-1, 2}, Rational{-1, 1}};

  matrix -= delta;
  EqualMatrix(matrix,
              std::array<std::array<Rational, 2>, 2>{{Rational{1, 2}, Rational{1, 1}, Rational{3, 1}, Rational{1, 1}}});
  EqualMatrix(matrix -= delta,
              std::array<std::array<Rational, 2>, 2>{{Rational{1, 4}, Rational{0, 1}, Rational{7, 2}, Rational{2, 1}}});

  (matrix -= delta) = delta;
  EqualMatrix(matrix,
              std::array<std::array<Rational, 2>, 2>{Rational{1, 4}, Rational{1, 1}, Rational{-1, 2}, Rational{-1, 1}});

  EqualMatrix(delta - delta,
              std::array<std::array<Rational, 2>, 2>{Rational{0, 1}, Rational{0, 1}, Rational{0, 1}, Rational{0, 1}});
  EqualMatrix(
      delta - Matrix<Rational, 2, 2>{Rational{3, 4}, Rational{2, 1}, Rational{5, 2}, Rational{0, 1}},
      std::array<std::array<Rational, 2>, 2>{{Rational{-1, 2}, Rational{-1, 1}, Rational{-3, 1}, Rational{-1, 1}}});
  EqualMatrix(Matrix<Rational, 2, 2>{Rational{3, 4}, Rational{2, 1}, Rational{5, 2}, Rational{0, 1}} - delta,
              std::array<std::array<Rational, 2>, 2>{{Rational{1, 2}, Rational{1, 1}, Rational{3, 1}, Rational{1, 1}}});

  using ReturnType = std::remove_const_t<decltype(matrix - matrix)>;
  static_assert((std::is_same_v<ReturnType, const Matrix<Rational, 2, 2>&> ||
                 std::is_same_v<ReturnType, Matrix<Rational, 2, 2>>));
}

TEST_CASE("MatrixMultiplication", "[MatrixOperators]") {
  Matrix<Rational, 3, 2> matrix{Rational{-1, 1}, Rational{1, 2}, Rational{3, 4},
                                Rational{-1, 4}, Rational{0, 1}, Rational{2, 1}};
  const Matrix<Rational, 2, 2> delta{Rational{1, 1}, Rational{1, 2}, Rational{4, 1}, Rational{-3, 2}};

  matrix *= delta;
  EqualMatrix(matrix, std::array<std::array<Rational, 2>, 3>{Rational{1, 1}, Rational{-5, 4}, Rational{-1, 4},
                                                             Rational{3, 4}, Rational{8, 1}, Rational{-3, 1}});
  EqualMatrix(matrix *= delta,
              std::array<std::array<Rational, 2>, 3>{Rational{-4, 1}, Rational{19, 8}, Rational{11, 4}, Rational{-5, 4},
                                                     Rational{-4, 1}, Rational{17, 2}});

  (matrix *= delta) = {};
  EqualMatrix(matrix, std::array<std::array<Rational, 2>, 3>{});

  const Matrix<Rational, 2, 1> other{Rational{-1, 2}, Rational{2}};

  EqualMatrix(delta * other, std::array<std::array<Rational, 1>, 2>{Rational{1, 2}, Rational{-5, 1}});
  EqualMatrix(other * Matrix<Rational, 1, 2>{Rational{4, 1}, Rational{1, 2}},
              std::array<std::array<Rational, 2>, 2>{Rational{-2, 1}, Rational{-1, 4}, Rational{8, 1}, Rational{1, 1}});
  EqualMatrix(Matrix<Rational, 1, 2>{Rational{2, 1}, Rational{1, 2}} * other,
              std::array<std::array<Rational, 1>, 1>{Rational{0}});

  using ReturnType = std::remove_const_t<decltype(matrix * other)>;
  static_assert((std::is_same_v<ReturnType, const Matrix<Rational, 3, 1>&> ||
                 std::is_same_v<ReturnType, Matrix<Rational, 3, 1>>));
}

TEST_CASE("ScalarMultiplication", "[MatrixOperators]") {
  Matrix<Rational, 3, 2> matrix{Rational{-1, 1}, Rational{1, 2}, Rational{3, 4},
                                Rational{-1, 4}, Rational{0, 1}, Rational{2, 1}};
  const int delta = -2;

  matrix *= delta;
  EqualMatrix(matrix, std::array<std::array<Rational, 2>, 3>{
                          {Rational{2, 1}, Rational{-1}, Rational{-3, 2}, Rational{1, 2}, Rational{0}, Rational{-4}}});
  EqualMatrix(matrix *= delta, std::array<std::array<Rational, 2>, 3>{
                                   {Rational{-4}, Rational{2}, Rational{3}, Rational{-1}, Rational{0}, Rational{8}}});

  (matrix *= delta) = {Rational{1, 2}, Rational{-1, 2}, Rational{1}};
  EqualMatrix(matrix, std::array<std::array<Rational, 2>, 3>{Rational{1, 2}, Rational{-1, 2}, Rational{1}});

  EqualMatrix(matrix * delta, std::array<std::array<Rational, 2>, 3>{Rational{-1}, Rational{1}, Rational{-2}});
  EqualMatrix(-1 * Matrix<int, 2, 2>{1, -2, 3, -4}, std::array<std::array<int, 2>, 2>{-1, 2, -3, 4});
  EqualMatrix(Matrix<int, 2, 2>{3, 2, -1, -4} * 2, std::array<std::array<int, 2>, 2>{6, 4, -2, -8});

  using ReturnType = std::remove_const_t<decltype(matrix * delta)>;
  static_assert((std::is_same_v<ReturnType, const Matrix<Rational, 3, 2>&> ||
                 std::is_same_v<ReturnType, Matrix<Rational, 3, 2>>));
}

TEST_CASE("ScalarDivision", "[MatrixOperators]") {
  Matrix<Rational, 3, 2> matrix{Rational{-1, 1}, Rational{1, 2}, Rational{3, 4},
                                Rational{-1, 4}, Rational{0, 1}, Rational{2, 1}};
  const int delta = -2;

  matrix /= delta;
  EqualMatrix(matrix, std::array<std::array<Rational, 2>, 3>{{Rational{1, 2}, Rational{-1, 4}, Rational{-3, 8},
                                                              Rational{1, 8}, Rational{0}, Rational{-1}}});
  EqualMatrix(matrix /= delta, std::array<std::array<Rational, 2>, 3>{{Rational{-1, 4}, Rational{1, 8}, Rational{3, 16},
                                                                       Rational{-1, 16}, Rational{0}, Rational{1, 2}}});

  (matrix /= delta) = {Rational{1, 2}, Rational{-1, 2}, Rational{1}};
  EqualMatrix(matrix, std::array<std::array<Rational, 2>, 3>{Rational{1, 2}, Rational{-1, 2}, Rational{1}});

  EqualMatrix(matrix / delta, std::array<std::array<Rational, 2>, 3>{Rational{-1, 4}, Rational{1, 4}, Rational{-1, 2}});
  EqualMatrix(Matrix<int, 2, 2>{90, 2, -8, -4} / 2, std::array<std::array<int, 2>, 2>{45, 1, -4, -2});

  using ReturnType = std::remove_const_t<decltype(matrix / delta)>;
  static_assert((std::is_same_v<ReturnType, const Matrix<Rational, 3, 2>&> ||
                 std::is_same_v<ReturnType, Matrix<Rational, 3, 2>>));
}

TEST_CASE("Equality", "[MatrixOperators]") {
  Matrix<int, 3, 3> a{1, 2, 3, 4, 5, 6, 7, 8, 9};
  Matrix<int, 3, 3> b = a;
  Matrix<int, 3, 3> c{1, 2, 3, 4, 5, 6, 7, 8, -9};

  REQUIRE(a == a);
  REQUIRE(b == b);
  REQUIRE(c == c);
  REQUIRE(a == b);
  REQUIRE(b != c);
  REQUIRE(a != c);
}

TEST_CASE("Input", "[MatrixOperators]") {
  {
    std::stringstream ss{"-5"};

    Matrix<int, 1, 1> matrix{};
    ss >> matrix;
    EqualMatrix(matrix, std::array<std::array<int, 1>, 1>{-5});
  }

  {
    std::stringstream ss{"-5 1\n0 10"};

    Matrix<int, 2, 2> matrix{};
    ss >> matrix;
    EqualMatrix(matrix, std::array<std::array<int, 2>, 2>{-5, 1, 0, 10});
  }

  {
    std::stringstream ss{"-5 1\n10 0\n-7 -1\na b"};

    Matrix<int, 3, 2> a{};
    Matrix<char, 1, 2> b{};
    ss >> a >> b;
    EqualMatrix(a, std::array<std::array<int, 2>, 3>{-5, 1, 10, 0, -7, -1});
    EqualMatrix(b, std::array<std::array<char, 2>, 1>{'a', 'b'});
  }
}

TEST_CASE("Output", "[MatrixOperators]") {
  {
    Matrix<int, 1, 1> matrix{-5};

    std::stringstream ss;
    ss << matrix;
    REQUIRE(ss.str() == "-5\n");
  }

  {
    Matrix<int, 2, 2> matrix{-5, 1, 0, 10};

    std::stringstream ss;
    ss << matrix;
    REQUIRE(ss.str() == "-5 1\n0 10\n");
  }

  {
    Matrix<int, 3, 2> a{-5, 1, 10, 0, -7, -1};
    Matrix<char, 1, 2> b{'a', 'b'};

    std::stringstream ss;
    ss << a << '\n' << b;
    REQUIRE(ss.str() == "-5 1\n10 0\n-7 -1\n\na b\n");
  }
}

TEST_CASE("GetTransposed", "[MatrixMethods]") {
  {
    Matrix<int, 1, 1> matrix{-1};
    REQUIRE(matrix == GetTransposed(matrix));

    using ReturnType = std::remove_const_t<decltype(GetTransposed(matrix))>;
    static_assert((std::is_same_v<ReturnType, Matrix<int, 1, 1>>));
  }

  {
    Matrix<int, 2, 2> matrix{1, 2, 3, 4};
    EqualMatrix(GetTransposed(matrix), std::array<std::array<int, 2>, 2>{1, 3, 2, 4});

    using ReturnType = std::remove_const_t<decltype(GetTransposed(matrix))>;
    static_assert((std::is_same_v<ReturnType, Matrix<int, 2, 2>>));
  }

  {
    Matrix<int, 3, 2> matrix{1, 2, 3, 4, 5, 6};
    EqualMatrix(GetTransposed(matrix), std::array<std::array<int, 3>, 2>{1, 3, 5, 2, 4, 6});

    using ReturnType = std::remove_const_t<decltype(GetTransposed(matrix))>;
    static_assert((std::is_same_v<ReturnType, Matrix<int, 2, 3>>));
  }
}

#ifdef MATRIX_SQUARE_MATRIX_IMPLEMENTED

TEST_CASE("Transpose", "[MatrixMethods]") {
  {
    Matrix<int, 2, 2> matrix{-1, 4, 9, 2};
    Transpose(matrix);
    EqualMatrix(matrix, std::array<std::array<int, 2>, 2>{-1, 9, 4, 2});
  }

  {
    Matrix<int, 3, 3> matrix{-1, 4, 9, 2, 5, -7, 0, 2, 0};
    Transpose(matrix);
    EqualMatrix(matrix, std::array<std::array<int, 3>, 3>{-1, 2, 0, 4, 5, 2, 9, -7, 0});
  }

  {
    Matrix<Rational, 3, 3> matrix{Rational{1},    Rational{1, 2}, Rational{1, 3}, Rational{1, 4}, Rational{1, 5},
                                  Rational{1, 6}, Rational{1, 7}, Rational{1, 8}, Rational{1, 9}};
    Transpose(matrix);
    EqualMatrix(matrix, std::array<std::array<Rational, 3>, 3>{Rational{1}, Rational{1, 4}, Rational{1, 7},
                                                               Rational{1, 2}, Rational{1, 5}, Rational{1, 8},
                                                               Rational{1, 3}, Rational{1, 6}, Rational{1, 9}});
  }
}

TEST_CASE("Trace", "[MatrixMethods]") {
  {
    Matrix<int, 2, 2> matrix{-1, 4, 9, 2};
    REQUIRE(Trace(matrix) == 1);
  }

  {
    Matrix<int, 3, 3> matrix{-1, 4, 9, 2, 5, -7, 0, 2, 0};
    REQUIRE(Trace(matrix) == 4);
  }

  {
    Matrix<Rational, 3, 3> matrix{Rational{1},    Rational{1, 2}, Rational{1, 3}, Rational{1, 4}, Rational{1, 5},
                                  Rational{1, 6}, Rational{1, 7}, Rational{1, 8}, Rational{1, 9}};
    REQUIRE(Trace(matrix) == Rational{59, 45});
  }
}

TEST_CASE("Determinant", "[MatrixMethods]") {
  {
    Matrix<int, 1, 1> matrix{3};
    REQUIRE(Determinant(matrix) == 3);
  }

  {
    Matrix<int, 2, 2> matrix{-1, 4, 9, 2};
    REQUIRE(Determinant(matrix) == -38);
  }

  {
    Matrix<int, 3, 3> matrix{-1, 4, 9, 2, 5, -7, 0, 2, 0};
    REQUIRE(Determinant(matrix) == 22);
  }

  {
    Matrix<Rational, 3, 3> matrix{Rational{1},    Rational{1, 2}, Rational{1, 3}, Rational{1, 4}, Rational{1, 5},
                                  Rational{1, 6}, Rational{1, 7}, Rational{1, 8}, Rational{1, 9}};
    REQUIRE(Determinant(matrix) == Rational{1, 3360});
  }
}

TEST_CASE("Inverse", "[MatrixMethods]") {
  {
    Matrix<Rational, 1, 1> matrix{3};
    Inverse(matrix);
    EqualMatrix(matrix, std::array<std::array<Rational, 1>, 1>{Rational{1, 3}});
  }

  {
    Matrix<Rational, 2, 2> matrix{-1, 4, 9, 2};
    Inverse(matrix);
    EqualMatrix(matrix, std::array<std::array<Rational, 2>, 2>{Rational{-1, 19}, Rational{2, 19}, Rational{9, 38},
                                                               Rational{1, 38}});
  }

  {
    Matrix<Rational, 3, 3> matrix{-1, 4, 9, 2, 5, -7, 0, 2, 0};
    Inverse(matrix);
    EqualMatrix(matrix, std::array<std::array<Rational, 3>, 3>{Rational{7, 11}, Rational{9, 11}, Rational{-73, 22},
                                                               Rational{0}, Rational{0}, Rational{1, 2},
                                                               Rational{2, 11}, Rational{1, 11}, Rational{-13, 22}});
  }

  {
    Matrix<Rational, 3, 3> matrix{Rational{1},    Rational{1, 2}, Rational{1, 3}, Rational{1, 4}, Rational{1, 5},
                                  Rational{1, 6}, Rational{1, 7}, Rational{1, 8}, Rational{1, 9}};
    Inverse(matrix);
    EqualMatrix(matrix, std::array<std::array<Rational, 3>, 3>{Rational{14, 3}, Rational{-140, 3}, Rational{56},
                                                               Rational{-40, 3}, Rational{640, 3}, Rational{-280},
                                                               Rational{9}, Rational{-180}, Rational{252}});
  }
}

TEST_CASE("GetInversed", "[MatrixMethods]") {
  {
    Matrix<Rational, 1, 1> matrix{3};
    EqualMatrix(GetInversed(matrix), std::array<std::array<Rational, 1>, 1>{Rational{1, 3}});

    using ReturnType = std::remove_const_t<decltype(GetInversed(matrix))>;
    static_assert((std::is_same_v<ReturnType, Matrix<Rational, 1, 1>>));
  }

  {
    Matrix<Rational, 2, 2> matrix{-1, 4, 9, 2};
    EqualMatrix(GetInversed(matrix), std::array<std::array<Rational, 2>, 2>{Rational{-1, 19}, Rational{2, 19},
                                                                            Rational{9, 38}, Rational{1, 38}});

    using ReturnType = std::remove_const_t<decltype(GetInversed(matrix))>;
    static_assert((std::is_same_v<ReturnType, Matrix<Rational, 2, 2>>));
  }

  {
    Matrix<Rational, 3, 3> matrix{-1, 4, 9, 2, 5, -7, 0, 2, 0};
    EqualMatrix(GetInversed(matrix), std::array<std::array<Rational, 3>, 3>{
                                         Rational{7, 11}, Rational{9, 11}, Rational{-73, 22}, Rational{0}, Rational{0},
                                         Rational{1, 2}, Rational{2, 11}, Rational{1, 11}, Rational{-13, 22}});

    using ReturnType = std::remove_const_t<decltype(GetInversed(matrix))>;
    static_assert((std::is_same_v<ReturnType, Matrix<Rational, 3, 3>>));
  }

  {
    Matrix<Rational, 3, 3> matrix{Rational{1},    Rational{1, 2}, Rational{1, 3}, Rational{1, 4}, Rational{1, 5},
                                  Rational{1, 6}, Rational{1, 7}, Rational{1, 8}, Rational{1, 9}};
    EqualMatrix(GetInversed(matrix), std::array<std::array<Rational, 3>, 3>{
                                         Rational{14, 3}, Rational{-140, 3}, Rational{56}, Rational{-40, 3},
                                         Rational{640, 3}, Rational{-280}, Rational{9}, Rational{-180}, Rational{252}});

    using ReturnType = std::remove_const_t<decltype(GetInversed(matrix))>;
    static_assert((std::is_same_v<ReturnType, Matrix<Rational, 3, 3>>));
  }
}
#endif  // MATRIX_SQUARE_MATRIX_IMPLEMENTED