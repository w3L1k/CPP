#ifndef RANGE_H_
#define RANGE_H_

class RangeIterator {
 public:
  RangeIterator(int current, int step);

  int operator*() const;
  RangeIterator& operator++();
  bool operator!=(const RangeIterator& other) const;

 private:
  int current_;
  int step_;
};

class Range {
 public:
  explicit Range(int end);
  Range(int begin, int end);
  Range(int begin, int end, int step);

  RangeIterator Begin() const;
  RangeIterator End() const;


  RangeIterator begin() const;
  RangeIterator end() const;

 private:
  int begin_;
  int end_;
  int step_;
};

#endif  // RANGE_H_
