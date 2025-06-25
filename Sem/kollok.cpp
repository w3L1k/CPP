#include <bitset>
#include <cstdint>
#include <string>
#include <iostream>

class BitMask {
 public:
  BitMask() : mask_(0) {
  }
  explicit BitMask(uint32_t mask) : mask_(mask) {
  }

  BitMask operator|(const BitMask&& other) const {
    return BitMask(mask_ | other.mask_);
  }
  BitMask operator&(const BitMask& other) const {
    return BitMask(mask_ & other.mask_);
  }

  BitMask operator~() const {
    return BitMask(~mask_);
  }

  bool hasFlag(int pos) const {
    return (mask_ >> pos) & 1;
  }

  std::string toString() const {
    return std::bitset<32>(mask_).to_string();
  }

 private:
  uint32_t mask_;
};

int main() {
  BitMask a(0b00000000000000000000000000001010);
  BitMask b(0b00000000000000000000000000000101);
  BitMask f;
  BitMask c = a | BitMask(b);
  BitMask d = a & b;
  BitMask e = ~a;

  std::cout << "a :" << a.toString() << '\n';
  std::cout << "b :" << b.toString() << '\n';
  std::cout << "a | b : " << c.toString() << '\n';
  std::cout << "a & b : " << d.toString() << '\n';
  std::cout << "~a :" << e.toString() << '\n';

  std::cout << a.hasFlag(1) << '\n';
  std::cout << a.hasFlag(0) << '\n';

  return 0;
}
