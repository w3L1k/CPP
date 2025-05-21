#include "big_integer.h"
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cmath>

// Определения статических членов
const int BigInteger::BASE = 10000;
const int BigInteger::BASE_DIGITS = 4;
const int BigInteger::MAX_DECIMAL_DIGITS = 30000;


void BigInteger::RemoveLeadingZeros() {
    while (!digits_.empty() && digits_.back() == 0)
        digits_.pop_back();
    if (digits_.empty())
        is_negative_ = false;
}

int BigInteger::DecimalDigitCount() const {
    if (digits_.empty()) return 1;
    int digits = (digits_.size() - 1) * BASE_DIGITS;
    int last = digits_.back();
    while (last) {
        digits++;
        last /= 10;
    }
    return digits;
}

void CheckOverflow(const BigInteger& a) {
    if (a.DecimalDigitCount() > BigInteger::MAX_DECIMAL_DIGITS + 9)
      throw BigIntegerOverflow{};
}

BigInteger::BigInteger() : digits_{0}, is_negative_(false) {}

BigInteger::BigInteger(int value) : is_negative_(value < 0) {
    value = std::abs(value);
    while (value) {
        digits_.push_back(value % BASE);
        value /= BASE;
    }
    if (digits_.empty()) digits_.push_back(0);
}

BigInteger::BigInteger(long long value) : is_negative_(value < 0) {
    value = std::abs(value);
    while (value) {
        digits_.push_back(static_cast<DigitType>(value % BASE));
        value /= BASE;
    }
    if (digits_.empty()) digits_.push_back(0);
}

BigInteger::BigInteger(const char* str) : BigInteger(std::string(str)) {}

BigInteger::BigInteger(const std::string& str) {
    is_negative_ = false;
    digits_.clear();
    std::string s = str;
    if (s.empty()) {
        digits_ = {0};
        return;
    }
    if (s[0] == '-') {
        is_negative_ = true;
        s = s.substr(1);
    }
    for (int i = static_cast<int>(s.length()); i > 0; i -= BASE_DIGITS) {
        int end = i;
        int start = std::max(0, end - BASE_DIGITS);
        int chunk = std::stoi(s.substr(start, end - start));
        digits_.push_back(static_cast<DigitType>(chunk));
    }
    RemoveLeadingZeros();
}

bool BigInteger::IsNegative() const {
    return is_negative_;
}

BigInteger BigInteger::operator+() const {
    return *this;
}

BigInteger BigInteger::operator-() const {
    BigInteger res = *this;
    if (*this != 0)
        res.is_negative_ = !res.is_negative_;
    return res;
}

int BigInteger::CompareAbs(const BigInteger& other) const {
    if (digits_.size() != other.digits_.size())
        return digits_.size() < other.digits_.size() ? -1 : 1;
    for (int i = static_cast<int>(digits_.size()) - 1; i >= 0; --i) {
        if (digits_[i] != other.digits_[i])
            return digits_[i] < other.digits_[i] ? -1 : 1;
    }
    return 0;
}

BigInteger BigInteger::AddUnsigned(const BigInteger& other) const {
    BigInteger result;
    result.digits_.clear();
    DoubleDigitType carry = 0;
    size_t n = std::max(digits_.size(), other.digits_.size());
    for (size_t i = 0; i < n || carry; ++i) {
        DoubleDigitType sum = carry;
        if (i < digits_.size()) sum += digits_[i];
        if (i < other.digits_.size()) sum += other.digits_[i];
        result.digits_.push_back(static_cast<DigitType>(sum % BASE));
        carry = sum / BASE;
    }
    result.RemoveLeadingZeros();
    return result;
}

BigInteger BigInteger::SubtractUnsigned(const BigInteger& other) const {
    BigInteger result;
    result.digits_.clear();
    DoubleDigitType carry = 0;
    for (size_t i = 0; i < digits_.size(); ++i) {
        DoubleDigitType sub = digits_[i] - carry;
        if (i < other.digits_.size())
            sub -= other.digits_[i];
        if (sub >= 0) {
            result.digits_.push_back(static_cast<DigitType>(sub));
            carry = 0;
        } else {
            result.digits_.push_back(static_cast<DigitType>(sub + BASE));
            carry = 1;
        }
    }
    result.RemoveLeadingZeros();
    return result;
}

BigInteger& BigInteger::operator+=(const BigInteger& other) {
    if (is_negative_ == other.is_negative_) {
        *this = this->AddUnsigned(other);
        is_negative_ = other.is_negative_;
    } else {
        if (this->CompareAbs(other) >= 0) {
            *this = this->SubtractUnsigned(other);
        } else {
            *this = other.SubtractUnsigned(*this);
            is_negative_ = other.is_negative_;
        }
    }
    CheckOverflow(*this);
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& other) {
    *this += (-other);
    return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& other) {
    BigInteger result;
    result.digits_.assign(digits_.size() + other.digits_.size(), 0);
    for (size_t i = 0; i < digits_.size(); ++i) {
        DoubleDigitType carry = 0;
        for (size_t j = 0; j < other.digits_.size() || carry; ++j) {
            DoubleDigitType prod = result.digits_[i + j] +
                static_cast<DoubleDigitType>(digits_[i]) * (j < other.digits_.size() ? other.digits_[j] : 0) + carry;
            result.digits_[i + j] = static_cast<DigitType>(prod % BASE);
            carry = prod / BASE;
        }
    }
    result.is_negative_ = is_negative_ != other.is_negative_;
    result.RemoveLeadingZeros();
    CheckOverflow(result);
    return *this = result;
}

BigInteger& BigInteger::operator+=(int other) {
    return *this += BigInteger(other);
}
BigInteger& BigInteger::operator-=(int other) {
    return *this -= BigInteger(other);
}
BigInteger& BigInteger::operator*=(int other) {
    return *this *= BigInteger(other);
}

BigInteger& BigInteger::operator++() {
    return *this += 1;
}
BigInteger BigInteger::operator++(int) {
    BigInteger temp = *this;
    ++(*this);
    return temp;
}
BigInteger& BigInteger::operator--() {
    return *this -= 1;
}
BigInteger BigInteger::operator--(int) {
    BigInteger temp = *this;
    --(*this);
    return temp;
}

BigInteger::operator bool() const {
    return !digits_.empty() && !(digits_.size() == 1 && digits_[0] == 0);
}

bool operator==(const BigInteger& a, const BigInteger& b) {
    return a.is_negative_ == b.is_negative_ && a.digits_ == b.digits_;
}
bool operator!=(const BigInteger& a, const BigInteger& b) {
    return !(a == b);
}
bool operator<(const BigInteger& a, const BigInteger& b) {
    if (a.is_negative_ != b.is_negative_)
        return a.is_negative_;
    int cmp = a.CompareAbs(b);
    return a.is_negative_ ? cmp > 0 : cmp < 0;
}
bool operator>(const BigInteger& a, const BigInteger& b) {
    return b < a;
}
bool operator<=(const BigInteger& a, const BigInteger& b) {
    return !(b < a);
}
bool operator>=(const BigInteger& a, const BigInteger& b) {
    return !(a < b);
}

std::ostream& operator<<(std::ostream& out, const BigInteger& value) {
    if (value.IsNegative() && value)
        out << '-';
    if (value.digits_.empty()) {
        out << "0";
        return out;
    }
    out << value.digits_.back();
    for (int i = static_cast<int>(value.digits_.size()) - 2; i >= 0; --i)
        out << std::setw(BigInteger::BASE_DIGITS) << std::setfill('0') << value.digits_[i];
    return out;
}

std::istream& operator>>(std::istream& in, BigInteger& value) {
    std::string s;
    in >> s;
    value = BigInteger(s);
    return in;
}

BigInteger operator+(BigInteger lhs, const BigInteger& rhs) {
    lhs += rhs;
    return lhs;
}
BigInteger operator-(BigInteger lhs, const BigInteger& rhs) {
    lhs -= rhs;
    return lhs;
}
BigInteger operator*(BigInteger lhs, const BigInteger& rhs) {
    lhs *= rhs;
    return lhs;
}
BigInteger operator+(BigInteger lhs, int rhs) {
    lhs += rhs;
    return lhs;
}
BigInteger operator-(BigInteger lhs, int rhs) {
    lhs -= rhs;
    return lhs;
}
BigInteger operator*(BigInteger lhs, int rhs) {
    lhs *= rhs;
    return lhs;
}
