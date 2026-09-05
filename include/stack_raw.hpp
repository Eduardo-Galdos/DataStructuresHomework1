#ifndef STACKRAW
#define STACKRAW

#include <cstddef>
#include <stdexcept>
#include <utility>

template<typename T>
class StackRaw {
private:
  T *data_ = nullptr;
  std::size_t size_ = 0;
  std::size_t capacity_ = 0;

  void grow();

public:
  StackRaw() = default;
  StackRaw(const StackRaw &other);
  StackRaw(StackRaw &&other) noexcept;
  StackRaw &operator=(const StackRaw &other);
  StackRaw &operator=(StackRaw &&other) noexcept;
  ~StackRaw();

  void push(const T &x);
  void push(T &&x);
  void pop();

  T &top();
  const T &top() const;

  bool empty() const noexcept { return size_ == 0; }
  std::size_t size() const noexcept { return size_; }
  std::size_t capacity() const noexcept { return capacity_; }
};

// Restricción didáctica: T debe ser construible por defecto y asignable.
// No se permite usar std::vector dentro de esta clase.

template<typename T>
void StackRaw<T>::grow() {
  if(capacity_ == 0)
    capacity_ = 1;

  capacity_ = capacity_ * 2;
  T* dataTemp = new T[capacity_];

  for(std::size_t i = 0; i < size_; i++)
    dataTemp[i] = std::move(data_[i]);

  delete[] data_; 
  data_ = dataTemp;

  return;
}

template<typename T>


StackRaw<T>::StackRaw(const StackRaw &other) {

  other.capacity_ == 0 ? this->data_ = nullptr : this->data_ =  new T[other.capacity_];

  for(std::size_t i = 0; i < other.size_; i++)
    this->data_[i] = other.data_[i];
  

  this->size_ = other.size_;
  this->capacity_ = other.capacity_;
}

template<typename T>
StackRaw<T>::StackRaw(StackRaw &&other) noexcept {
  
  this->data_ = other.data_;
  this->size_ = other.size_;
  this->capacity_ = other.capacity_;

  other.data_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

template<typename T>
StackRaw<T> &StackRaw<T>::operator=(const StackRaw &other) {
  
  if(this == &other)
    return *this;
  delete[] this->data_;
  other.capacity_ == 0 ? data_ = nullptr : this->data_ = new T[other.capacity_];
  

  for(std::size_t i = 0; i < other.size_; i++)
    this->data_[i] = other.data_[i];

  this->size_ = other.size_;
  this->capacity_ = other.capacity_;

  return *this;
}

template<typename T>
StackRaw<T> &StackRaw<T>::operator=(StackRaw &&other) noexcept {
  if(this == &other)
    return *this;
  
  delete[] this->data_;

  this->data_ = other.data_;
  this->capacity_ = other.capacity_;
  this->size_ = other.size_;

  other.data_ = nullptr;
  other.capacity_ = 0;
  other.size_ = 0;

  return *this;
}

template<typename T>
StackRaw<T>::~StackRaw() {
  delete[] data_;
}

template<typename T>
void StackRaw<T>::push(const T &x) {
  
  if(size_ == capacity_)
      grow();
  data_[size_] = x;
  size_++;

  return;    
}

template<typename T>
void StackRaw<T>::push(T &&x) {
  if(size_ == capacity_)
    grow();

  data_[size_] = std::move(x);
  size_++;

  return;
}

template<typename T>
void StackRaw<T>::pop() {
  if(empty())
    throw std::out_of_range("Cant pop an empty stack");  
  size_--;
  
  return;
}

template<typename T>
T &StackRaw<T>::top() {
  if(empty())
    throw std::out_of_range("Cant get top of an empty stack");

  return data_[size_ - 1];
}

//top q modifica esta hecho para un s.top = T

template<typename T>
const T &StackRaw<T>::top() const {
  if(empty())
    throw std::out_of_range("Cant get top of and empty stack");

  return data_[size_ - 1];
}



#endif
