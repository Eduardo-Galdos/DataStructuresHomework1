#ifndef QUEUESHIFT
#define QUEUESHIFT

#include <cstddef>
#include <stdexcept>
#include <utility>

template<typename T>
class QueueShift {
private:
  T *data_ = nullptr;
  std::size_t size_ = 0;
  std::size_t capacity_ = 0;
  std::size_t moves_ = 0;

  void grow();

public:
  QueueShift() = default;
  QueueShift(const QueueShift &other);
  QueueShift(QueueShift &&other) noexcept;
  QueueShift &operator=(const QueueShift &other);
  QueueShift &operator=(QueueShift &&other) noexcept;
  ~QueueShift();

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
// moves_ cuenta transferencias debidas a redimensionamiento o desplazamiento,
// no la asignación normal del elemento que se inserta.

template<typename T>
void QueueShift<T>::grow() {
  if(capacity_ == 0)
    capacity_ = 1;
  
  capacity_ = capacity_ * 2;
  T* dataTemp = new T[capacity_];

  for(std::size_t i = 0; i < size_; i++){
    dataTemp[i] = std::move(data_[i]);
    moves_++;
  }
  
  delete[] data_;

  data_ = dataTemp;
  return;

}

template<typename T>
QueueShift<T>::QueueShift(const QueueShift &other) {

  other.capacity_ == 0 ? data_ = nullptr : data_ = new T[other.capacity_];
  
  for(std::size_t i = 0; i < other.size_; i++)
    data_[i] = other.data_[i];

  capacity_ = other.capacity_;
  size_ = other.size_;
  moves_ = other.moves_;
}

template<typename T>
QueueShift<T>::QueueShift(QueueShift &&other) noexcept {
  
  data_ = other.data_;
  capacity_ = other.capacity_;
  size_ = other.size_;
  moves_ = other.moves_;

  other.data_ = nullptr;
  other.capacity_ = 0;
  other.size_ = 0;
  other.moves_ = 0;  
}

template<typename T>
QueueShift<T> &QueueShift<T>::operator=(const QueueShift &other) {
  if(this == &other)
    return *this;
  delete[] data_;
  other.capacity_ == 0 ? data_ = nullptr : data_ = new T[other.capacity_];

  for(std::size_t i = 0; i < other.size_; i++)
    data_[i] = other.data_[i];

  size_ = other.size_;
  capacity_ = other.capacity_;
  moves_ = other.moves_;

  return *this;
}

template<typename T>
QueueShift<T> &QueueShift<T>::operator=(QueueShift &&other) noexcept {
  // TODO: liberar el recurso actual, transferir ownership y vaciar el origen.
  if(this == &other)
    return *this;

  delete[] data_;
  
  data_ = other.data_;
  capacity_ = other.capacity_;
  moves_ = other.moves_;
  size_ = other.size_;

  other.data_ = nullptr;
  other.capacity_ = 0;
  other.moves_ = 0;
  other.size_= 0;
  
  return *this;
}

template<typename T>
QueueShift<T>::~QueueShift() {
  delete[] data_;
}

template<typename T>
void QueueShift<T>::push(const T &x) {
  if(size_ == capacity_)
    grow();

  data_[size_] = x;
  size_++;

  return;
}

template<typename T>
void QueueShift<T>::push(T &&x) {
  if(size_ == capacity_)
    grow();

  data_[size_] = std::move(x);
  size_++;

  return;
}

template<typename T>
void QueueShift<T>::pop() {
  if(empty())
    throw std::out_of_range("Cant pop an empty queue");

  for(std::size_t i = 0; i < size_ - 1; i++){
    data_[i] = std::move(data_[i + 1]);
    moves_++;
  }

  size_--;

  return;
}

template<typename T>
T &QueueShift<T>::front() {
  if(empty())
    throw std::out_of_range("Cant get front of an empty queue");
  return data_[0];
}

template<typename T>
const T &QueueShift<T>::front() const {
  if(empty())
    throw std::out_of_range("Cant get front of an empty queue");
  return data_[0];
}

#endif
