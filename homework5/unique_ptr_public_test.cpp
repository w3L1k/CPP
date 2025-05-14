#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <memory>
#include <vector>
#include <utility>

#include "unique_ptr.h"
#include "unique_ptr.h"  // check include guards

TEST_CASE("Constructors", "[UniquePtr]") {
  SECTION("Default Constructor") {
    const UniquePtr<int> a;
    REQUIRE_FALSE(a);
    REQUIRE(a.Get() == nullptr);
  }

  SECTION("Pointer Constructor") {
    const UniquePtr<int> a(nullptr);
    REQUIRE_FALSE(a);
    REQUIRE(a.Get() == nullptr);

    auto ptr = new int;
    const UniquePtr<int> b(ptr);
    REQUIRE(b);
    REQUIRE(b.Get() == ptr);
  }

  SECTION("Move Constructor") {
    auto ptr = new int;
    UniquePtr<int> a(ptr);
    const UniquePtr<int> b(std::move(a));
    REQUIRE(b);
    REQUIRE_FALSE(a);  // NOLINT check moved in valid state
    REQUIRE(a.Get() == nullptr);
    REQUIRE(b.Get() == ptr);
    REQUIRE(std::is_nothrow_move_constructible_v<UniquePtr<int>>);
    REQUIRE(!std::is_copy_constructible_v<UniquePtr<int>>);
  }
}

TEST_CASE("Assignment", "[UniquePtr]") {
  auto ptr = new int;
  UniquePtr<int> a(ptr);
  UniquePtr<int> b;

  b = std::move(a);
  REQUIRE(b);
  REQUIRE_FALSE(a);  // NOLINT check moved in valid state
  REQUIRE(a.Get() == nullptr);
  REQUIRE(b.Get() == ptr);

  auto ptr2 = new int;
  b = UniquePtr<int>(ptr2);
  REQUIRE(b);
  REQUIRE(b.Get() == ptr2);

  REQUIRE(std::is_nothrow_move_assignable_v<UniquePtr<int>>);
  REQUIRE(!std::is_copy_assignable_v<UniquePtr<int>>);
}

TEST_CASE("Release", "[UniquePtr]") {
  SECTION("Empty") {
    UniquePtr<int> a;
    REQUIRE(a.Release() == nullptr);
  }

  SECTION("Not Empty") {
    auto ptr = new int;
    UniquePtr<int> a(ptr);
    REQUIRE(a.Release() == ptr);
    REQUIRE(a.Get() == nullptr);
    REQUIRE_FALSE(a);
    delete ptr;
  }
}

TEST_CASE("Reset", "[UniquePtr]") {
  SECTION("Empty") {
    auto ptr = new int;
    UniquePtr<int> a;

    a.Reset();
    REQUIRE(!a);
    REQUIRE(a.Get() == nullptr);

    a.Reset(ptr);
    REQUIRE(a);
    REQUIRE(a.Get() == ptr);
  }

  SECTION("Not Empty") {
    auto ptr1 = new int;
    auto ptr2 = new int;
    UniquePtr<int> a(ptr1);

    a.Reset(ptr2);
    REQUIRE(a);
    REQUIRE(a.Get() == ptr2);

    a.Reset();
    REQUIRE(!a);
    REQUIRE(a.Get() == nullptr);
  }
}

TEST_CASE("Swap", "[UniquePtr]") {
  auto ptr1 = new int;
  auto ptr2 = new int;
  UniquePtr<int> a;
  UniquePtr<int> b(ptr1);
  UniquePtr<int> c(ptr2);

  a.Swap(a);
  REQUIRE(!a);
  REQUIRE(a.Get() == nullptr);

  b.Swap(b);
  REQUIRE(b);
  REQUIRE(b.Get() == ptr1);

  a.Swap(b);
  REQUIRE(a);
  REQUIRE(a.Get() == ptr1);
  REQUIRE(!b);
  REQUIRE(b.Get() == nullptr);

  b.Swap(c);
  REQUIRE(b);
  REQUIRE(b.Get() == ptr2);
  REQUIRE(!c);
  REQUIRE(c.Get() == nullptr);

  a.Swap(b);
  REQUIRE(a);
  REQUIRE(a.Get() == ptr2);
  REQUIRE(b);
  REQUIRE(b.Get() == ptr1);
}

TEST_CASE("Operators", "[UniquePtr]") {
  const UniquePtr<std::pair<int, double>> a(new std::pair<int, double>{});
  REQUIRE(a->first == 0);
  REQUIRE((*a).second == 0.0);

  a->first = 10;
  (*a).second = 11.5;
  REQUIRE(a->first == 10);
  REQUIRE((*a).second == 11.5);

  a.Get()->first = 11;
  a.Get()->second = 0.0;
  REQUIRE(a->first == 11);
  REQUIRE((*a).second == 0.0);
}

#ifdef MAKE_UNIQUE_IMPLEMENTED

TEST_CASE("MakeUnique", "[UniquePtr]") {
  {
    const auto ptr = MakeUnique<std::vector<int>>();
    REQUIRE(ptr->empty());
    REQUIRE(ptr->data() == nullptr);
  }

  {
    const auto ptr = MakeUnique<std::vector<int>>(11);
    REQUIRE(ptr->size() == 11);
  }

  {
    const auto ptr = MakeUnique<std::pair<int, double>>(11, 0.5);
    REQUIRE(ptr->first == 11);
    REQUIRE(ptr->second == 0.5);
  }

  {
    int x = 11;
    const auto ptr = MakeUnique<std::pair<int&, std::unique_ptr<int>>>(x, std::make_unique<int>(11));
    REQUIRE(ptr->first == 11);
    REQUIRE(*(ptr->second) == 11);

    x = -11;
    *(ptr->second) = -11;
    REQUIRE(ptr->first == -11);
    REQUIRE(*(ptr->second) == -11);
  }
}

#endif
