#pragma once
#include <iostream>
using namespace std;

template <typename T>
class StaticArray {

private:

    T* data_;
    int size_;
    int capacity_;

    bool isValidIndex(int index) const {
        return (index >= 0 && index < size_);
    }

public:

    explicit StaticArray(int capacity)
        : data_(new T[capacity]), size_(0), capacity_(capacity) {
    }

    ~StaticArray() {
        delete[] data_;
        data_ = nullptr;
    }

    T get(int index) const {
        if (!isValidIndex(index)) {
            cout << "[StaticArray] get(" << index << ") out of range. size=" << size_ << "\n";
            return T{};
        }
        return data_[index];
    }

    void set(int index, T value) {
        if (!isValidIndex(index)) {
            cout << "[StaticArray] set(" << index << ") out of range. size=" << size_ << "\n";
            return;
        }
        data_[index] = value;
    }

    T front() const {
        if (isEmpty()) { cout << "[StaticArray] front() — empty\n"; return T{}; }
        return data_[0];
    }

    T back() const {
        if (isEmpty()) { cout << "[StaticArray] back() — empty\n"; return T{}; }
        return data_[size_ - 1];
    }

    void pushBack(T value) {
        if (isFull()) {
            cout << "[StaticArray] pushBack() — full (capacity=" << capacity_ << ")\n";
            return;
        }
        data_[size_++] = value;
    }

    void popBack() {
        if (isEmpty()) { cout << "[StaticArray] popBack() — empty\n"; return; }
        size_--;
    }

    void insert(int index, T value) {
        if (isFull()) { cout << "[StaticArray] insert() — full\n"; return; }
        if (index < 0 || index > size_) {
            cout << "[StaticArray] insert(" << index << ") out of range. size=" << size_ << "\n";
            return;
        }
        for (int i = size_; i > index; i--)
            data_[i] = data_[i - 1];
        data_[index] = value;
        size_++;
    }

    void remove(int index) {
        if (!isValidIndex(index)) {
            cout << "[StaticArray] remove(" << index << ") out of range. size=" << size_ << "\n";
            return;
        }
        for (int i = index; i < size_ - 1; i++)
            data_[i] = data_[i + 1];
        size_--;
    }

    int search(T value) const {
        for (int i = 0; i < size_; i++)
            if (data_[i] == value) return i;
        return -1;
    }

    bool contains(T value) const {
        return search(value) != -1;
    }

    int count(T value) const {
        int n = 0;
        for (int i = 0; i < size_; i++)
            if (data_[i] == value) n++;
        return n;
    }

    void bubbleSort() {
        for (int i = 0; i < size_ - 1; i++) {
            bool swapped = false;
            for (int j = 0; j < size_ - 1 - i; j++) {
                if (data_[j] > data_[j + 1]) {
                    T tmp = data_[j]; data_[j] = data_[j + 1]; data_[j + 1] = tmp;
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }

    void selectionSort() {
        for (int i = 0; i < size_ - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < size_; j++)
                if (data_[j] < data_[minIdx]) minIdx = j;
            if (minIdx != i) {
                T tmp = data_[i]; data_[i] = data_[minIdx]; data_[minIdx] = tmp;
            }
        }
    }

    void insertionSort() {
        for (int i = 1; i < size_; i++) {
            T   key = data_[i];
            int j = i - 1;
            while (j >= 0 && data_[j] > key) {
                data_[j + 1] = data_[j];
                j--;
            }
            data_[j + 1] = key;
        }
    }

    void swap(int i, int j) {
        if (!isValidIndex(i) || !isValidIndex(j)) {
            cout << "[StaticArray] swap() — index out of range\n"; return;
        }
        T tmp = data_[i]; data_[i] = data_[j]; data_[j] = tmp;
    }

    void reverse() {
        int left = 0, right = size_ - 1;
        while (left < right) {
            T tmp = data_[left]; data_[left] = data_[right]; data_[right] = tmp;
            left++; right--;
        }
    }

    void fill(T value) {
        for (int i = 0; i < size_; i++)
            data_[i] = value;
    }

    void clear() { size_ = 0; }

    T min() const {
        if (isEmpty()) { cout << "[StaticArray] min() — empty\n"; return T{}; }
        T m = data_[0];
        for (int i = 1; i < size_; i++)
            if (data_[i] < m) m = data_[i];
        return m;
    }

    T max() const {
        if (isEmpty()) { cout << "[StaticArray] max() — empty\n"; return T{}; }
        T m = data_[0];
        for (int i = 1; i < size_; i++)
            if (data_[i] > m) m = data_[i];
        return m;
    }

    bool isEmpty()     const { return size_ == 0; }
    bool isFull()      const { return size_ == capacity_; }
    int  getSize()     const { return size_; }
    int  getCapacity() const { return capacity_; }

    void print() const {
        if (isEmpty()) { cout << "[ empty ]\n"; return; }
        cout << "[ ";
        for (int i = 0; i < size_; i++) {
            cout << data_[i];
            if (i < size_ - 1) cout << ", ";
        }
        cout << " ]\n";
    }

    void printInfo() const {
        cout << "size=" << size_ << " | capacity=" << capacity_ << " | data=";
        print();
    }

};