#include <string>
template <typename T>
struct HasSerialize {
  template <typename U>

  static auto test(int) -> std::is_same<
      decltype(std::declval<const U>().serialize()),
      std::string
  >
  template <typename U>
  static std::false_type test(...);

  static constexpr bool value = decltype(test<T>(0))::value;
};

class Data {
 public:
  std::string serialize() const {
    return "";
  };
};
template <typename T>
void save(const T& obj) {
  static_assert(HasSerialize<T>::value, "requires serialize method");
  obj.serialize();
}
void demo() {
  Data d;
  save(d);
}
