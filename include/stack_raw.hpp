#pragma once

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
  throw std::logic_error("TODO StackRaw::grow");
}

template<typename T>
StackRaw<T>::StackRaw(const StackRaw &) {
  throw std::logic_error("TODO StackRaw copy constructor");
}

template<typename T>
StackRaw<T>::StackRaw(StackRaw &&) noexcept {
  // TODO: transferir ownership y dejar el origen vacío.
}

template<typename T>
StackRaw<T> &StackRaw<T>::operator=(const StackRaw &) {
  throw std::logic_error("TODO StackRaw copy assignment");
}

template<typename T>
StackRaw<T> &StackRaw<T>::operator=(StackRaw &&) noexcept {
  // TODO: liberar el recurso actual, transferir ownership y vaciar el origen.
  return *this;
}

template<typename T>
StackRaw<T>::~StackRaw() {
  delete[] data_;
}

template<typename T>
void StackRaw<T>::push(const T &) {
  throw std::logic_error("TODO StackRaw::push(const T&)");
}

template<typename T>
void StackRaw<T>::push(T &&) {
  throw std::logic_error("TODO StackRaw::push(T&&)");
}

template<typename T>
void StackRaw<T>::pop() {
  throw std::logic_error("TODO StackRaw::pop");
}

template<typename T>
T &StackRaw<T>::top() {
  throw std::logic_error("TODO StackRaw::top");
}

template<typename T>
const T &StackRaw<T>::top() const {
  throw std::logic_error("TODO StackRaw::top const");
}
