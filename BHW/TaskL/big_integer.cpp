#include "big_integer.h"


BigInteger::BigInteger() : is_negative_(false) {
  digits_.push_back(0);
}

BigInteger::BigInteger(uint64_t value) {
  if (value < 0) {
    is_negative_ = true;
    value = -value;
  } else {
    is_negative_ = false;
  }

  if (value == 0) {
    digits_.push_back(0);
  } else {
    while (value > 0) {
      digits_.push_back(value % BASE);
      value /= BASE;
    }
  }
}

BigInteger::BigInteger(const char* str) {
  std::string s(str);
  is_negative_ = false;
  if (s.empty()) {
    digits_.push_back(0);
    return;
  }

  if (s[0] == '-') {
    is_negative_ = true;
    s = s.substr(1);
  } else if (s[0] == '+') {
    s = s.substr(1);
  }

  for (int i = static_cast<int>(s.length()); i > 0; i -= BASE_DIGITS) {
    int begin = std::max(0, i - BASE_DIGITS);
    std::string part = s.substr(begin, i - begin);
    digits_.push_back(static_cast<uint32_t>(std::stoul(part)));
  }

  RemoveLeadingZeros();
}

bool BigInteger::IsNegative() const {
  return is_negative_;
}

void BigInteger::RemoveLeadingZeros() {
  while (digits_.size() > 1 && digits_.back() == 0) {
    digits_.pop_back();
  }

  if (digits_.size() == 1 && digits_[0] == 0) {
    is_negative_ = false;
  }

  // Проверка на переполнение — не более 30009 цифр
  if (digits_.size() > 30009) {
    throw BigIntegerOverflow{};
  }
}
