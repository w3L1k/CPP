#ifndef RANGE_H_
#define RANGE_H_

class RangeIterator {
 public:
  RangeIterator(int start, int step) : value_(start), step_(step) {}

  int operator*() const { return value_; }

  RangeIterator& operator++() {
    value_ += step_;
    return *this;
  }

  bool operator!=(const RangeIterator& other) const {
    if (step_ > 0) {
      return value_ < other.value_;
    }
    if (step_ < 0) {
      return value_ > other.value_;
    }
    return false;
  }

 private:
  int value_;
  int step_;
};

class Range {
 public:
  explicit Range(int end) : start_(0), end_(end), step_(1) {}
  Range(int start, int end) : start_(start), end_(end), step_(1) {}
  Range(int start, int end, int step) : start_(start), end_(end), step_(step) {}

  RangeIterator begin() const { return RangeIterator(start_, step_); }//NOLINT

  RangeIterator end() const { return RangeIterator(end_, step_); }//NOLINT

 private:
  int start_;
  int end_;
  int step_;
};

#endif
