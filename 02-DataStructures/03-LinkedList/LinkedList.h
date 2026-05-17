#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Node {
public:
    T     data;
    Node* next;

    Node(T value) {
        data = value;
        next = nullptr;
    }
};

template <typename T>
class LinkedList {

private:

    Node<T>* head_;
    Node<T>* tail_;
    int      size_;

    bool isValidIndex(int index) const {
        return (index >= 0 && index < size_);
    }

public:

    LinkedList() {
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }

    ~LinkedList() {
        Node<T>* current = head_;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    void pushFront(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head_;
        head_ = newNode;
        if (tail_ == nullptr) tail_ = newNode;
        size_++;
    }

    void pushBack(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (tail_ == nullptr) {
            head_ = newNode;
            tail_ = newNode;
        }
        else {
            tail_->next = newNode;
            tail_ = newNode;
        }
        size_++;
    }

    void insert(int index, T value) {
        if (index < 0 || index > size_) {
            cout << "[LinkedList] insert(" << index << ") out of range. size=" << size_ << "\n";
            return;
        }
        if (index == 0) { pushFront(value); return; }
        if (index == size_) { pushBack(value);  return; }

        Node<T>* newNode = new Node<T>(value);
        Node<T>* prev = head_;
        for (int i = 0; i < index - 1; i++) prev = prev->next;
        newNode->next = prev->next;
        prev->next = newNode;
        size_++;
    }

    void popFront() {
        if (isEmpty()) { cout << "[LinkedList] popFront() — empty\n"; return; }
        Node<T>* toDelete = head_;
        head_ = head_->next;
        delete toDelete;
        if (head_ == nullptr) tail_ = nullptr;
        size_--;
    }

    void popBack() {
        if (isEmpty()) { cout << "[LinkedList] popBack() — empty\n"; return; }
        if (head_ == tail_) {
            delete head_;
            head_ = nullptr;
            tail_ = nullptr;
            size_--;
            return;
        }
        Node<T>* prev = head_;
        while (prev->next != tail_) prev = prev->next;
        delete tail_;
        tail_ = prev;
        tail_->next = nullptr;
        size_--;
    }

    void remove(int index) {
        if (!isValidIndex(index)) {
            cout << "[LinkedList] remove(" << index << ") out of range. size=" << size_ << "\n";
            return;
        }
        if (index == 0) { popFront(); return; }
        if (index == size_ - 1) { popBack();  return; }

        Node<T>* prev = head_;
        Node<T>* current = head_->next;
        for (int i = 1; i < index; i++) {
            prev = prev->next;
            current = current->next;
        }
        prev->next = current->next;
        delete current;
        size_--;
    }

     

    T get(int index) const {
        if (!isValidIndex(index)) {
            cout << "[LinkedList] get(" << index << ") out of range. size=" << size_ << "\n";
            return T{};
        }
        Node<T>* current = head_;
        for (int i = 0; i < index; i++) current = current->next;
        return current->data;
    }

    T front() const {
        if (isEmpty()) { cout << "[LinkedList] front() — empty\n"; return T{}; }
        return head_->data;
    }

    T back() const {
        if (isEmpty()) { cout << "[LinkedList] back() — empty\n"; return T{}; }
        return tail_->data;
    }

    int search(T value) const {
        Node<T>* current = head_;
        int index = 0;
        while (current != nullptr) {
            if (current->data == value) return index;
            current = current->next;
            index++;
        }
        return -1;
    }

    bool contains(T value) const { return search(value) != -1; }

    int count(T value) const {
        Node<T>* current = head_;
        int n = 0;
        while (current != nullptr) {
            if (current->data == value) n++;
            current = current->next;
        }
        return n;
    }

    void reverse() {
        if (size_ <= 1) return;
        Node<T>* prev = nullptr;
        Node<T>* current = head_;
        tail_ = head_;
        while (current != nullptr) {
            Node<T>* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head_ = prev;
    }

    void clear() {
        Node<T>* current = head_;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }

    bool isEmpty()  const { return size_ == 0; }
    int  getSize()  const { return size_; }

    void print() const {
        if (isEmpty()) { cout << "[ empty ]\n"; return; }
        Node<T>* current = head_;
        cout << "[ ";
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) cout << " -> ";
            current = current->next;
        }
        cout << " -> nullptr ]\n";
    }

    void printInfo() const {
        cout << "size=" << size_;
        if (!isEmpty())
            cout << " | head=" << head_->data << " | tail=" << tail_->data;
        cout << "\n";
    }

};