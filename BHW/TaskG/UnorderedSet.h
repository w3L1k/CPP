#pragma once
#include <iostream>
#include <list>
#include <vector>

template <typename KeyT>
class UnorderedSet {
 public:
  using BucketVector = std::vector<std::list<KeyT>>;

  UnorderedSet() : num_buckets_(0), buckets_(), hash_func_{}, count_(0) {
  }

  explicit UnorderedSet(size_t count) : num_buckets_(count), buckets_(num_buckets_), hash_func_{}, count_(0) {
  }

  template <typename InputIt>
  UnorderedSet(InputIt first, InputIt last)
      : num_buckets_(distance(first, last)), buckets_(num_buckets_), hash_func_{}, count_(0) {
    for (auto it = first; it != last; ++it) {
      Insert(*it);
    }
  }

  UnorderedSet(const UnorderedSet &other)
      : num_buckets_(other.num_buckets_), buckets_(other.buckets_), hash_func_(other.hash_func_), count_(other.count_) {
    for (const auto &bucket : other.buckets_) {
      for (const auto &key : bucket) {
        Insert(key);
      }
    }
  }

  UnorderedSet(UnorderedSet &&other) noexcept
      : num_buckets_(std::move(other.num_buckets_))
      , buckets_(std::move(other.buckets_))
      , hash_func_(std::move(other.hash_func_))
      , count_(std::move(other.count_)) {
    other.count_ = 0;
    other.num_buckets_ = 0;
  }

  UnorderedSet &operator=(const UnorderedSet &other) {
    if (this != &other) {
      num_buckets_ = other.num_buckets_;
      buckets_ = other.buckets_;
      hash_func_ = other.hash_func_;
      count_ = other.count_;
      for (const auto &bucket : other.buckets_) {
        for (const auto &key : bucket) {
          Insert(key);
        }
      }
    }
    return *this;
  }

  UnorderedSet &operator=(UnorderedSet &&other) noexcept {
    if (this != &other) {
      num_buckets_ = other.num_buckets_;
      buckets_ = std::move(other.buckets_);
      hash_func_ = other.hash_func_;
      count_ = other.count_;

      other.num_buckets_ = 0;
      other.count_ = 0;
    }
    return *this;
  }

  ~UnorderedSet() {
    Clear();
  }

  void Clear() {
    for (auto &bucket : buckets_) {
      bucket.clear();
    }
    count_ = 0;
  }

  [[nodiscard]] size_t Size() const {
    return count_;
  }

  [[nodiscard]] bool Empty() const {
    return count_ == 0;
  }

  void Insert(const KeyT &key) {
    if (num_buckets_ == 0) {
      Rehash(1);
    }
    if (buckets_.empty()) {
      Rehash(1);
    }
    size_t bucket_id = FindBucket(key);
    for (auto it = buckets_[bucket_id].begin(); it != buckets_[bucket_id].end(); ++it) {
      if (*it == key) {
        return;
      }
    }
    if (count_ == num_buckets_) {
      Rehash(num_buckets_ * 2);
      bucket_id = FindBucket(key);
    }
    buckets_[bucket_id].emplace_back(key);
    ++count_;
  }

  void Insert(KeyT &&key) {
    if (num_buckets_ == 0) {
      Rehash(1);
    }
    if (buckets_.empty()) {
      Rehash(1);
    }
    size_t bucket_id = FindBucket(key);
    for (auto it = buckets_[bucket_id].begin(); it != buckets_[bucket_id].end(); ++it) {
      if (*it == key) {
        return;
      }
    }
    if (count_ == num_buckets_) {
      Rehash(num_buckets_ * 2);
      bucket_id = FindBucket(key);
    }
    buckets_[bucket_id].emplace_back(std::move(key));
    ++count_;
  }

  void Rehash(size_t new_bucket_count) {
    if (new_bucket_count == num_buckets_ || new_bucket_count < count_) {
      return;
    }

    BucketVector new_buckets(new_bucket_count);
    for (const auto &bucket : buckets_) {
      for (const auto &key : bucket) {
        size_t new_bucket_id = hash_func_(key) % new_bucket_count;
        new_buckets[new_bucket_id].emplace_back(key);
      }
    }

    buckets_.swap(new_buckets);
    num_buckets_ = new_bucket_count;
  }

  void Erase(const KeyT &key) {
    if (buckets_.empty()) {
      return;
    }
    if (num_buckets_ == 0) {
      Rehash(1);
    }
    auto bucket = &buckets_[FindBucket(key)];
    for (auto it = bucket->begin(); it != bucket->end(); ++it) {
      if (*it == key) {
        bucket->erase(it);
        --count_;
        return;
      }
    }
  }

  bool Find(const KeyT &key) const {
    if (num_buckets_ == 0) {
      return false;
    }
    if (buckets_.empty()) {
      return false;
    }
    auto bucket = &buckets_[FindBucket(key)];
    for (const auto &element : *bucket) {
      if (element == key) {
        return true;
      }
    }
    return false;
  }

  void Reserve(std::size_t new_bucket_count) {
    if (new_bucket_count <= num_buckets_) {
      return;
    }

    Rehash(new_bucket_count);
  }

  [[nodiscard]] size_t BucketCount() const {
    return num_buckets_;
  }

  [[nodiscard]] size_t BucketSize(size_t id) const {
    if (id >= num_buckets_) {
      return 0;
    }
    return buckets_[id].size();
  }

  size_t Bucket(const KeyT &key) const {
    return FindBucket(key);
  }

  [[nodiscard]] float LoadFactor() const {
    if (num_buckets_ == 0) {
      return 0.0f;
    }
    return static_cast<float>(count_) / num_buckets_;
  }

 private:
  size_t num_buckets_;
  BucketVector buckets_;
  std::hash<KeyT> hash_func_;
  size_t count_;
  size_t FindBucket(const KeyT &key) const {
    return hash_func_(key) % num_buckets_;
  }
};
