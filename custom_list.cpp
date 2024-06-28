#include <algorithm>
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T> class List {
private:
  size_t length = 0;
  const int DEFAULT_INCR = 2;
  int DEF_SIZE = 5;
  T *ptr;
  void manage_mem() throw(runtime_error) {
    T *n_ptr = new T[this->DEF_SIZE * this->DEFAULT_INCR];
    if (n_ptr == nullptr) {
      throw runtime_error("Out of memory!");
    }
    std::copy(this->ptr, this->ptr + this->length, n_ptr);
  }
  int binary_search(int s, int e, T k) {
    if (s > e) {
      return -1;
    }
    int mid = (e - s + 1) / 2;
    if (this->ptr[mid] == k) {
      return mid;
    } else if (k > this->ptr[mid]) {
      return binary_search(mid + 1, e, k);
    } else {
      return binary_search(s, mid - 1, k);
    }
  }

public:
  List<T>(size_t size) : DEF_SIZE(size) { this->ptr = new T[size]; }

public:
  int getLength() const { return this->length; }
  void print() const {
    if (this->length == 0) {
      cout << "[]\n";
      return;
    }
    for (int i = 0; i < this->length; i++) {
      cout << this->ptr[i] << " ";
    }
    cout << '\n';
  }

public:
  void append(T item) throw() {
    if (this->length >= this->DEF_SIZE) {
      manage_mem();
    }
    this->ptr[this->length++] = item;
  }
  void remove(int i) throw(runtime_error) {
    if (this->length >= this->DEF_SIZE || i < 0 || i >= this->length) {
      throw runtime_error("Invalid index!");
    }
    i++;
    while (i < this->length) {
      this->ptr[i - 1] = this->ptr[i];
      i++;
    }
    this->length--;
  }
  T pop() throw(runtime_error) {
    if (this->length == 0) {
      throw runtime_error("Empty []!");
    }
    T rm = this->ptr[this->length - 1];
    this->length--;
    return rm;
  }
  int binaryIndex(T n, int s = 0) {
    if (this->length == 0) {
      return -1;
    }
    return binary_search(s, this->length - 1, n);
  }
  int linearIndex(T n) {
    if (this->length == 0) {
      return -1;
    }
    for (int i = 0; i < this->length; i++) {
      if (this->ptr[i] == n) {
        return i;
      }
    }
    return -1;
  }
  void insert(int i, T n) throw(runtime_error) {
    if (i < 0 || i > this->length) {
      throw runtime_error("Invalid index!");
    }
    if (this->length >= this->def_size) {
      manage_mem();
    }
    for (int j = this->length; j > i; j--) {
      this->ptr[j] = this->ptr[j - 1];
    }
    this->ptr[i] = n;
    this->length++;
  }

  void reverse() {
    if (this->length == 0) {
      return;
    }
    std::reverse(this->ptr, this->ptr + this->length);
  }
  void sort() {
    if (this->length == 0) {
      return;
    }
    std::sort(this->ptr, this->ptr + this->length);
  }

  ~List<T>() {
    delete[] this->ptr;
    this->length = 0;
  }
};

int main(void) {
  List<float> k = List<float>(5);
  for (float i = 1.5; i <= 5.0; i++) {
    k.append(i);
  }
  k.print();
  return 0;
}