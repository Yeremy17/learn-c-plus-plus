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
class Stack {

private:

    Node<T>* top_;
    int      size_;

public:

    Stack() {
        top_ = nullptr;
        size_ = 0;
    }

    ~Stack() {
        Node<T>* current = top_;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    void push(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = top_;
        top_ = newNode;
        size_++;
    }

    void pop() {
        if (isEmpty()) { cout << "[Stack] pop() — empty\n"; return; }
        Node<T>* toDelete = top_;
        top_ = top_->next;
        delete toDelete;
        size_--;
    }

    T peek() const {
        if (isEmpty()) { cout << "[Stack] peek() — empty\n"; return T{}; }
        return top_->data;
    }

    void clear() {
        Node<T>* current = top_;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        top_ = nullptr;
        size_ = 0;
    }

    bool isEmpty()  const { return size_ == 0; }
    int  getSize()  const { return size_; }

    void print() const {
        if (isEmpty()) { cout << "[ empty ]\n"; return; }
        Node<T>* current = top_;
        cout << "top → [ ";
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) cout << " | ";
            current = current->next;
        }
        cout << " ] ← bottom\n";
    }

};