#include "range.h"


RangeIterator::RangeIterator(int current, int step)
    : current_(current), step_(step) {}

int RangeIterator::operator*() const {
  return current_;
}

RangeIterator& RangeIterator::operator++() {
  current_ += step_;
  return *this;
}

bool RangeIterator::operator!=(const RangeIterator& other) const {
  return step_ > 0 ? current_ < other.current_ : current_ > other.current_;
}


Range::Range(int end)
    : begin_(0), end_(end), step_(1) {}

Range::Range(int begin, int end)
    : begin_(begin), end_(end), step_(1) {}

Range::Range(int begin, int end, int step)
    : begin_(begin), end_(end), step_(step) {}

RangeIterator Range::Begin() const {
  if ((step_ > 0 && begin_ >= end_) || (step_ < 0 && begin_ <= end_) || step_ == 0) {
    return {0, step_};  // Пустой диапазон
  }
  return {begin_, step_};
}

RangeIterator Range::End() const {
  return {end_, step_};
}


RangeIterator Range::begin() const {
  return Begin();
}

RangeIterator Range::end() const {
  return End();
}
