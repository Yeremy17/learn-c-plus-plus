#pragma once
#include <iostream>
using namespace std;

template <typename T>
class DNode {
public:
    T      data;
    DNode* prev;
    DNode* next;

    DNode(T value) {
        data = value;
        prev = nullptr;
        next = nullptr;
    }
};

template <typename T>
class DoublyLinkedList {

private:

    DNode<T>* head_;
    DNode<T>* tail_;
    int       size_;

    bool isValidIndex(int index) const {
        return (index >= 0 && index < size_);
    }

public:

    DoublyLinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

    ~DoublyLinkedList() {
        DNode<T>* current = head_;
        while (current != nullptr) {
            DNode<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    void pushFront(T value) {
        DNode<T>* newNode = new DNode<T>(value);
        if (head_ == nullptr) {
            head_ = newNode;
            tail_ = newNode;
        }
        else {
            newNode->next = head_;
            head_->prev = newNode;
            head_ = newNode;
        }
        size_++;
    }

    void pushBack(T value) {
        DNode<T>* newNode = new DNode<T>(value);
        if (tail_ == nullptr) {
            head_ = newNode;
            tail_ = newNode;
        }
        else {
            newNode->prev = tail_;
            tail_->next = newNode;
            tail_ = newNode;
        }
        size_++;
    }

    void insert(int index, T value) {
        if (index < 0 || index > size_) {
            cout << "[DoublyLinkedList] insert(" << index << ") out of range. size=" << size_ << "\n";
            return;
        }
        if (index == 0) { pushFront(value); return; }
        if (index == size_) { pushBack(value);  return; }

        DNode<T>* newNode = new DNode<T>(value);
        DNode<T>* prev = head_;
        for (int i = 0; i < index - 1; i++) prev = prev->next;
        DNode<T>* afterNew = prev->next;

        newNode->prev = prev;
        newNode->next = afterNew;
        prev->next = newNode;
        afterNew->prev = newNode;
        size_++;
    }

    void popFront() {
        if (isEmpty()) { cout << "[DoublyLinkedList] popFront() — empty\n"; return; }
        DNode<T>* toDelete = head_;
        head_ = head_->next;
        delete toDelete;
        if (head_ == nullptr) tail_ = nullptr;
        else head_->prev = nullptr;
        size_--;
    }

    void popBack() {
        if (isEmpty()) { cout << "[DoublyLinkedList] popBack() — empty\n"; return; }
        if (head_ == tail_) {
            delete head_;
            head_ = nullptr;
            tail_ = nullptr;
            size_--;
            return;
        }
        DNode<T>* toDelete = tail_;
        tail_ = tail_->prev;
        tail_->next = nullptr;
        delete toDelete;
        size_--;
    }

    void remove(int index) {
        if (!isValidIndex(index)) {
            cout << "[DoublyLinkedList] remove(" << index << ") out of range. size=" << size_ << "\n";
            return;
        }
        if (index == 0) { popFront(); return; }
        if (index == size_ - 1) { popBack();  return; }

        DNode<T>* current = head_;
        for (int i = 0; i < index; i++) current = current->next;
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        size_--;
    }

    void removeValue(T value) {
        if (isEmpty()) { cout << "[DoublyLinkedList] removeValue() — empty\n"; return; }
        DNode<T>* current = head_;
        while (current != nullptr) {
            if (current->data == value) {
                if (current->prev != nullptr) current->prev->next = current->next;
                else head_ = current->next;
                if (current->next != nullptr) current->next->prev = current->prev;
                else tail_ = current->prev;
                delete current;
                size_--;
                return;
            }
            current = current->next;
        }
        cout << "[DoublyLinkedList] removeValue() — not found\n";
    }

    T get(int index) const {
        if (!isValidIndex(index)) {
            cout << "[DoublyLinkedList] get(" << index << ") out of range. size=" << size_ << "\n";
            return T{};
        }
        DNode<T>* current;
        if (index <= size_ / 2) {
            current = head_;
            for (int i = 0; i < index; i++) current = current->next;
        }
        else {
            current = tail_;
            for (int i = size_ - 1; i > index; i--) current = current->prev;
        }
        return current->data;
    }

    T front() const {
        if (isEmpty()) { cout << "[DoublyLinkedList] front() — empty\n"; return T{}; }
        return head_->data;
    }

    T back() const {
        if (isEmpty()) { cout << "[DoublyLinkedList] back() — empty\n"; return T{}; }
        return tail_->data;
    }

    int search(T value) const {
        DNode<T>* current = head_;
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
        DNode<T>* current = head_;
        int n = 0;
        while (current != nullptr) {
            if (current->data == value) n++;
            current = current->next;
        }
        return n;
    }

    void reverse() {
        if (size_ <= 1) return;
        DNode<T>* current = head_;
        while (current != nullptr) {
            DNode<T>* tmp = current->prev;
            current->prev = current->next;
            current->next = tmp;
            current = current->prev;
        }
        DNode<T>* tmp = head_;
        head_ = tail_;
        tail_ = tmp;
    }

    void clear() {
        DNode<T>* current = head_;
        while (current != nullptr) {
            DNode<T>* next = current->next;
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
        DNode<T>* current = head_;
        cout << "nullptr ↔ [ ";
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) cout << " ↔ ";
            current = current->next;
        }
        cout << " ] ↔ nullptr\n";
    }

    void printReverse() const {
        if (isEmpty()) { cout << "[ empty ]\n"; return; }
        DNode<T>* current = tail_;
        cout << "nullptr ↔ [ ";
        while (current != nullptr) {
            cout << current->data;
            if (current->prev != nullptr) cout << " ↔ ";
            current = current->prev;
        }
        cout << " ] ↔ nullptr\n";
    }

    void printInfo() const {
        cout << "size=" << size_;
        if (!isEmpty())
            cout << " | head=" << head_->data << " | tail=" << tail_->data;
        cout << "\n";
    }

};