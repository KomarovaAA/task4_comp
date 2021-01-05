#ifndef VECTOR_HW4_HPP
#define VECTOR_HW4_HPP

#include <memory>
#include <utility>
#include <initializer_list>
#include <iostream>

const std::size_t AMOUNT = 1u;

template<class T>
class Vector {
public:
  using reference = T&;
  using iterator = T*;

  Vector():
    countElement(0u),
    capacityInVector(5u),
    array(new T[capacityInVector])
  {}

  Vector(const Vector& other):
    capacityInVector(other.capacityInVector),
    countElement(other.countElement),
    array(new T[capacityInVector]) {
    std::copy(other.begin(), other.end(), array);
  }

  Vector(Vector&& other):
    Vector() {
    this->swap(other);
  }

  Vector(std::initializer_list<T> init):
    countElement(init.size()),
    capacityInVector(init.size() * 2),
    array(new T[capacityInVector]) {
    std::copy(init.begin(), init.end(), array);
  }

  ~Vector() {
    delete [] array;
  }

  void push_back(const T& value) {
    reallocate();
    countElement++;
    array[countElement - 1] = value;
  }

  void push_back(T&& value) {
    reallocate();
    countElement++;
    array[countElement - 1] = std::move(value);
  }

  void pop_back() {
    if (countElement == 0) {
      throw std::out_of_range("Vector is empty");
    }
    (end() - 1)-> ~T();
    countElement--;
  }

  reference at(std::size_t index) const {
    if (index >= countElement) {
      throw std::out_of_range("Index out of range");
    }
    return array[index];
  }

  reference front() const {
    return *begin();
  }
  reference back() const {
    return *(end() - 1);
  }

  void erase(std::size_t index) {
    if (index >= countElement) {
      throw std::out_of_range("Index out of range");
    }
    auto newArray = new T[capacityInVector];
    int j = 0;
    for (int i = 0; i < countElement; i++) {
      if (i == index) {
        continue;
      }
      newArray[j] = array[i];
      j++;
    }

    delete [] array;
    array = newArray;
    countElement--;
  }

  void erase(iterator elem) {
    std::move(elem + 1, end(), elem);
    (std::prev(end()))->~T();
    countElement--;
  }

  void erase(iterator first, iterator last) {
    if (first > last || first < begin() || first > end() || last < begin() || last > end())
      throw std::out_of_range("Vector::erase(first, last) -- out of range");

    std::size_t countInDis = std::distance(first, last);
    std::move(last, end(), first);
    countElement -= countInDis;
  }

  iterator begin() const {
    return array;
  }

  iterator end() const {
    return begin() + countElement;
  }

  std::size_t size() const {
    return countElement;
  }

  void swap(Vector& other) {
    std::swap(capacityInVector, other.capacityInVector);
    std::swap(countElement, other.countElement);
    std::swap(array, other.array);
  }


  Vector& operator=(const Vector& other) {
    auto temp = Vector(other);
    swap(temp);
    return *this;
  }

  Vector& operator=(Vector&& other) {
    auto temp = std::move(other);
    swap(temp);
    return *this;
  }

private:
  std::size_t countElement;
  std::size_t capacityInVector;
  iterator array;

  //Увеличиваем количества допустимого пространства в векторе, перегоняем в новый массив все данные, стираем старый вкидываем в него новый.
  void reallocate() {
    if (capacityInVector - countElement >= AMOUNT) {
      return;
    }
    std::size_t newCapacity = (capacityInVector + AMOUNT) * 2;
    auto newArray = new T[newCapacity];
    std::move(begin(), end(), newArray);
    delete[] array;
    array = newArray;
    capacityInVector = newCapacity;
  }
};


template <class T>
void swap(Vector<T>& a, Vector<T>& b) {
  a.swap(b);
}

template<class T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
  if (lhs.size() != rhs.size()) return false;
  for (auto i = size_t{0}; i != lhs.size(); ++i)
    if (lhs.at(i) != rhs.at(i)) return false;
  return true;
}

#endif //VECTOR_HW4_HPP