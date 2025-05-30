#include"big_integer.h"

BigInteger::BigInteger() : is_negative_(false) {
}

BigInteger::BigInteger(int value) : is_negative_(value < 0) {
  if (value != 0){
    if (value < 0) {
      value = -value;
    }
    while (value > 0) {
      digits_.push_back(value % kBASE);
      value /= kBASE;
    }
  }
}

BigInteger::BigInteger(int64_t value) : is_negative_(value < 0) {
  if (value != 0) {
    if (value < 0) {
      value = -value;
    }
    while (value > 0) {
      int digit = static_cast<int>(value % kBASE);
      digits_.push_back(digit);
      value /= kBASE;
    }
  }
}

BigInteger::BigInteger(const char* value) {
  FromString(value);
}

BigInteger::BigInteger(const std::string& value) {
  FromString(value);
}

BigInteger::BigInteger(BigInteger&& other) noexcept
    : digits_(std::move(other.digits_)), is_negative_(other.is_negative_) {
  other.is_negative_ = false;
}

bool BigInteger::IsNegative() const {
  return is_negative_;
}

BigInteger BigInteger::Abs() const {
  BigInteger result = *this;
  result.is_negative_ = false;
  return result;
}

BigInteger BigInteger::operator+() const {
  return *this;
}

BigInteger BigInteger::operator-() const {
  BigInteger result = *this;
  result.is_negative_ = !is_negative_;
  return result;
}

BigInteger& BigInteger::operator+=(const BigInteger& other) {
  if (is_negative_ == other.is_negative_) {
    int carry = 0;
    for (size_t i = 0; i < std::max(digits_.size(), other.digits_.size()) || carry; ++i) {
      if (i == digits_.size()) {
        digits_.push_back(0);
      }
      if (i < other.digits_.size()) {
        digits_[i] += carry + other.digits_[i];
      } else {
        digits_[i] += carry;
      }
      carry = digits_[i] >= kBASE;
      if (carry) {
        digits_[i] -= kBASE;
      }
      if (digits_[i] < 0 || digits_[i] >= kBASE) {
        throw BigIntegerOverflow();
      }
    }
  } else {
    *this -= -other;
  }
  Trim();
  return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& other) {
  if (is_negative_ == other.is_negative_) {
    if (Abs() >= other.Abs()) {
      int carry = 0;
      for (size_t i = 0; i < other.digits_.size() || carry; ++i) {
        if (i == digits_.size()) {
          digits_.push_back(0);
        }
        if (i < other.digits_.size()) {
          digits_[i] -= carry + other.digits_[i];
        } else {
          digits_[i] -= carry;
        }
        carry = digits_[i] < 0;
        if (carry) {
          digits_[i] += kBASE;
        }
        if (digits_[i] < 0 || digits_[i] >= kBASE) {
          throw BigIntegerOverflow();
        }
      }
      Trim();
    } else {
      *this = -(other - *this);
    }
  } else {
    *this += -other;
  }
  return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& other) {
  std::vector<uint64_t> result(digits_.size() + other.digits_.size(), 0);
  for (size_t i = 0; i < digits_.size(); ++i) {
    for (size_t j = 0; j < other.digits_.size(); ++j) {
      uint64_t product = static_cast<uint64_t>(digits_[i]) * other.digits_[j];
      if (product >= static_cast<uint64_t>(std::numeric_limits<int64_t>::max())) {
        throw BigIntegerOverflow();
      }
      result[i + j] += product;
      if (result[i + j] >= kBASE) {
        result[i + j + 1] += result[i + j] / kBASE;
        result[i + j] %= kBASE;
      }
    }
  }

  digits_ = std::vector<int>(result.begin(), result.end());
  is_negative_ = is_negative_ != other.is_negative_;

  for (size_t i = 0; i < digits_.size(); ++i) {
    if (digits_[i] < 0 || digits_[i] >= kBASE) {
      throw BigIntegerOverflow();
    }
  }

  Trim();

  if (DigitCount() > 30009) {
    throw BigIntegerOverflow();
  }
  return *this;
}




BigInteger& BigInteger::operator=(int value) {
  *this = BigInteger(value);
  return *this;
}

BigInteger& BigInteger::operator=(const BigInteger& other) {
  if (this != &other) {
    digits_ = other.digits_;
    is_negative_ = other.is_negative_;
  }
  return *this;
}

BigInteger& BigInteger::operator=(BigInteger&& other) noexcept {
  if (this != &other) {
    digits_ = std::move(other.digits_);
    is_negative_ = other.is_negative_;
    other.is_negative_ = false;
  }
  return *this;
}

BigInteger operator+(BigInteger lhs, const BigInteger& rhs) {
  return lhs += rhs;
}

BigInteger operator-(BigInteger lhs, const BigInteger& rhs) {
  return lhs -= rhs;
}

BigInteger operator*(BigInteger lhs, const BigInteger& rhs) {
  return lhs *= rhs;
}


BigInteger& BigInteger::operator++() {
  *this += BigInteger(1);
  return *this;
}

BigInteger BigInteger::operator++(int) {
  BigInteger temp(*this);
  *this += BigInteger(1);
  return temp;
}

BigInteger& BigInteger::operator--() {
  *this -= BigInteger(1);
  return *this;
}

BigInteger BigInteger::operator--(int) {
  BigInteger temp(*this);
  *this -= BigInteger(1);
  return temp;
}

BigInteger::operator bool() const {
  return !digits_.empty();
}

bool operator==(const BigInteger& lhs, const BigInteger& rhs) {
  if (lhs.digits_.empty() && rhs.digits_.empty()) {
    return true;
  }
  return lhs.is_negative_ == rhs.is_negative_ && lhs.digits_ == rhs.digits_;
}

bool operator!=(const BigInteger& lhs, const BigInteger& rhs) {
  return !(lhs == rhs);
}

bool operator<(const BigInteger& lhs, const BigInteger& rhs) {
  if (lhs.is_negative_ != rhs.is_negative_) {
    return lhs.is_negative_;
  }
  if (lhs.digits_.size() != rhs.digits_.size()) {
    return lhs.digits_.size() * (lhs.is_negative_ ? -1 : 1) < rhs.digits_.size() * (rhs.is_negative_ ? -1 : 1);
  }
  for (int i = static_cast<int>(lhs.digits_.size()) - 1; i >= 0; --i) {
    if (lhs.digits_[i] != rhs.digits_[i]) {
      return lhs.digits_[i] * (lhs.is_negative_ ? -1 : 1) < rhs.digits_[i] * (rhs.is_negative_ ? -1 : 1);
    }
  }
  return false;
}

bool operator<=(const BigInteger& lhs, const BigInteger& rhs) {
  return !(rhs < lhs);
}

bool operator>(const BigInteger& lhs, const BigInteger& rhs) {
  return rhs < lhs;
}

bool operator>=(const BigInteger& lhs, const BigInteger& rhs) {
  return !(lhs < rhs);
}

std::ostream& operator<<(std::ostream& os, const BigInteger& value) {
  if (value.is_negative_) {
    os << '-';
  }
  os << (value.digits_.empty() ? 0 : value.digits_.back());
  for (int i = static_cast<int>(value.digits_.size()) - 2; i >= 0; --i) {
    os << std::setw(BigInteger::kBaseDigits) << std::setfill('0') << value.digits_[i];
  }
  return os;
}

std::istream& operator>>(std::istream& is, BigInteger& value) {
  std::string s;
  is >> s;
  value = BigInteger(s);
  return is;
}

void BigInteger::Trim() {
  while (!digits_.empty() && digits_.back() == 0) {
    digits_.pop_back();
  }
  if (digits_.empty()) {
    is_negative_ = false;
  }
}



void BigInteger::FromString(const std::string& value) {
  is_negative_ = false;
  digits_.clear();
  int pos = 0;
  if (value[0] == '-') {
    is_negative_ = true;
    pos = 1;
  } else if (value[0] == '+') {
    pos = 1;
  }
  for (int i = static_cast<int>(value.size()) - 1; i >= pos; i -= kBaseDigits) {
    int x = 0;
    for (int j = std::max(pos, i - kBaseDigits + 1); j <= i; ++j) {
      if (x > (std::numeric_limits<int>::max() - (value[j] - '0')) / 10) {
        throw BigIntegerOverflow();
      }
      x = x * 10 + (value[j] - '0');
    }
    if (x < 0 || x >= kBASE) {
      throw BigIntegerOverflow();
    }
    digits_.push_back(x);
  }
  Trim();
}


size_t BigInteger::DigitCount() const{
  if (digits_.empty() || (digits_.size() == 1 && digits_[0] == 0)) {
    return 1;
  }
  size_t digit_count = (digits_.size() - 1) * kBaseDigits;
  int last_digit = digits_.back();
  while (last_digit > 0) {
    last_digit /= 10;
    digit_count++;
  }
  return digit_count;
}