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
class Queue {

private:

    Node<T>* front_;
    Node<T>* back_;
    int      size_;

public:

    Queue() : front_(nullptr), back_(nullptr), size_(0) {}

    // deep copy constructor — copia todos los nodos del heap
    Queue(const Queue& other) : front_(nullptr), back_(nullptr), size_(0) {
        Node<T>* current = other.front_;
        while (current != nullptr) {
            enqueue(current->data);
            current = current->next;
        }
    }

    ~Queue() {
        Node<T>* current = front_;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    void enqueue(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (back_ == nullptr) {
            front_ = newNode;
            back_ = newNode;
        }
        else {
            back_->next = newNode;
            back_ = newNode;
        }
        size_++;
    }

    void dequeue() {
        if (isEmpty()) { cout << "[Queue] dequeue() — empty\n"; return; }
        Node<T>* toDelete = front_;
        front_ = front_->next;
        delete toDelete;
        if (front_ == nullptr) back_ = nullptr;
        size_--;
    }

    T front() const {
        if (isEmpty()) { cout << "[Queue] front() — empty\n"; return T{}; }
        return front_->data;
    }

    T back() const {
        if (isEmpty()) { cout << "[Queue] back() — empty\n"; return T{}; }
        return back_->data;
    }

    void clear() {
        Node<T>* current = front_;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        front_ = nullptr;
        back_ = nullptr;
        size_ = 0;
    }

    bool isEmpty()  const { return size_ == 0; }
    int  getSize()  const { return size_; }

    void print() const {
        if (isEmpty()) { cout << "[ empty ]\n"; return; }
        Node<T>* current = front_;
        cout << "front → [ ";
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) cout << " | ";
            current = current->next;
        }
        cout << " ] ← back\n";
    }

};