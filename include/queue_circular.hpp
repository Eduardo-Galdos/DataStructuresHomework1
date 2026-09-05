#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

template<typename T>
class QueueCircular {
private:
  T *data_ = nullptr;
  std::size_t head_ = 0;
  std::size_t size_ = 0;
  std::size_t capacity_ = 0;
  std::size_t moves_ = 0;

  void grow();
  std::size_t physical_index(std::size_t logical) const noexcept;

public:
  QueueCircular() = default;
  QueueCircular(const QueueCircular &other);
  QueueCircular(QueueCircular &&other) noexcept;
  QueueCircular &operator=(const QueueCircular &other);
  QueueCircular &operator=(QueueCircular &&other) noexcept;
  ~QueueCircular();

  void push(const T &x);
  void push(T &&x);
  void pop();

  T &front();
  const T &front() const;

  bool empty() const noexcept { return size_ == 0; }
  std::size_t size() const noexcept { return size_; }
  std::size_t capacity() const noexcept { return capacity_; }

  std::size_t moves() const noexcept { return moves_; }
  void reset_counters() noexcept { moves_ = 0; }
};

// Restricción didáctica: T debe ser construible por defecto y asignable.
// pop() NO debe desplazar los elementos restantes.

template<typename T>
std::size_t QueueCircular<T>::physical_index(std::size_t logical) const noexcept {
  return capacity_ == 0 ? 0 : (head_ + logical) % capacity_;
}

template<typename T>
void QueueCircular<T>::grow() {
  std::size_t new_cap;
  capacity_ == 0 ? new_cap = 1 : new_cap = capacity_ * 2;

  T* dataTemp = new T[new_cap];
  for(std::size_t i = 0; i < size_; i++){
    dataTemp[i] = std::move(data_[physical_index(i)]);
    moves_++;
  }

  delete[] data_;
  data_ = dataTemp;
  head_ = 0;
  capacity_ = new_cap;

  return;
}

template<typename T>
QueueCircular<T>::QueueCircular(const QueueCircular &other) {
  
  other.capacity_ == 0 ? data_ = nullptr : data_ = new T[other.capacity_];
  
  for(std::size_t i = 0; i < other.size_; i++)
    data_[i] = other.data_[physical_index(i)];

  head_ = other.head_;
  size_ = other.size_; 
  capacity_ = other.capacity_;
  moves_ = other.moves_;

}

template<typename T>
QueueCircular<T>::QueueCircular(QueueCircular &&other) noexcept {
  
  data_ = other.data_;
  head_ = other.head_;
  moves_ = other.moves_;
  size_ = other.size_;
  capacity_ = other.capacity_;

  other.data_ = nullptr;
  other.head_ = 0;
  other.moves_ = 0;
  other.size_ = 0;
  other.capacity_ = 0;
}

template<typename T>
QueueCircular<T> &QueueCircular<T>::operator=(const QueueCircular &other) {
  if(this == &other)
    return *this;
  
  delete data_;
  other.capacity_ == 0 ? data_ = nullptr : data_ = new T[other.capacity_];
  
  for(std::size_t i = 0; i < other.size_; i++)
    data_[i] = other.data_[physical_index(i)];

  capacity_ = other.capacity_;
  size_ = other.size_;
  moves_ = other.moves_;
  head_ = other.head_;

  return *this;
}

template<typename T>
QueueCircular<T> &QueueCircular<T>::operator=(QueueCircular &&other) noexcept {
  if(this == &other)
    return *this;

  delete data_;

  data_ = other.data_;
  head_ = other.head_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  moves_ = other.moves_;

  other.size_ = 0;
  other.head_ = 0;
  other.data_ = nullptr;
  other.moves_ = 0;
  other.size_ = 0;

  return *this;
}

template<typename T>
QueueCircular<T>::~QueueCircular() {
  delete[] data_;
}

template<typename T>
void QueueCircular<T>::push(const T &x) {
  if(size_ == capacity_)
    grow();

  data_[physical_index(size_)] = x;
  size_++;

  return;
}

template<typename T>
void QueueCircular<T>::push(T &&x) {
  if(size_ == capacity_)
    grow();

  data_[physical_index(size_)] = std::move(x);
  size_++;
}

template<typename T>
void QueueCircular<T>::pop() {
  if(empty())
    throw std::out_of_range("Cant pop an empty queue");

  size_--;
  head_ = (head_ + 1) % capacity_;
}

template<typename T>
T &QueueCircular<T>::front() {
  if(empty())
    throw std::out_of_range("Cant get front of an empty queue");

  return data_[head_];
}

template<typename T>
const T &QueueCircular<T>::front() const {
  if(empty())
    throw std::out_of_range("Cant get front of an empty queue");

  return data_[head_];
}
