// =============================================================================
//  DATA STRUCTURES EN C++ — FASE 3
//  Topic  : Doubly Linked List
//  Author : Yeremy Acuña Chavez
//  Repo   : https://github.com/yeremyacuna
// =============================================================================
//
//  INDEX
//  ─────────────────────────────────────────────────────────────────────────
//  [CLASS 1]  DNode<T>          — node with prev + next
//  [CLASS 2]  DoublyLinkedList<T>
//
//  [SECTION 1] Constructor & Destructor
//              - DoublyLinkedList()                   O(1)
//              - ~DoublyLinkedList()                  O(n)
//
//  [SECTION 2] Insertion
//              - pushFront(T value)                   O(1)
//              - pushBack(T value)                    O(1)
//              - insert(int index, T value)           O(n)
//
//  [SECTION 3] Deletion
//              - popFront()                           O(1)
//              - popBack()                            O(1)  ← true O(1) now
//              - remove(int index)                    O(n)
//              - removeValue(T value)                 O(n)
//
//  [SECTION 4] Access
//              - get(int index)                       O(n)
//              - front()                              O(1)
//              - back()                               O(1)
//
//  [SECTION 5] Search
//              - search(T value)                      O(n)
//              - contains(T value)                    O(n)
//              - count(T value)                       O(n)
//
//  [SECTION 6] Utility
//              - reverse()                            O(n)
//              - clear()                              O(n)
//
//  [SECTION 7] State Queries
//              - isEmpty()                            O(1)
//              - getSize()                            O(1)
//
//  [SECTION 8] Display
//              - print()                              O(n)
//              - printReverse()                       O(n)  ← new: walks backward
//              - printInfo()                          O(1)
//  ─────────────────────────────────────────────────────────────────────────
//
//  MEMORY MODEL
//  ─────────────────────────────────────────────────────────────────────────
//
//  head                                           tail
//   ↓                                              ↓
//  [∅ | 10 | →] ↔ [← | 20 | →] ↔ [← | 30 | →] ↔ [← | 40 | ∅]
//
//  head->prev  = nullptr  (nothing before the first)
//  tail->next  = nullptr  (nothing after the last)
//  every other node: prev points back, next points forward
//
//  KEY DIFFERENCE vs Singly Linked List
//  ─────────────────────────────────────────────────────────────────────────
//  popBack() Singly → must walk to second-to-last  → O(n)
//  popBack() Doubly → tail->prev gives it directly  → O(1)
//
//  RULE: every operation that touches a node must maintain BOTH pointers.
//  Forgetting to update prev or next corrupts the entire list.
//
//  Compile: g++ -std=c++17 -Wall -Wextra -o fase_03_dll fase_03_doubly_linked_list.cpp
//  Run    : ./fase_03_dll
// =============================================================================

#include <iostream>

using namespace std;


// =============================================================================
//  CLASS 1 — DNode<T>
//  Doubly node: holds data, a pointer to the PREVIOUS node, and to the NEXT.
// =============================================================================

template <typename T>
class DNode {
public:
    T      data;
    DNode* prev;   // points to the node BEFORE this one (nullptr if head)
    DNode* next;   // points to the node AFTER  this one (nullptr if tail)

    DNode(T value) {
        data = value;
        prev = nullptr;
        next = nullptr;
        // both nullptr at birth — the list links them when inserting
    }
};


// =============================================================================
//  CLASS 2 — DoublyLinkedList<T>
// =============================================================================

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

    // =========================================================================
    //  [SECTION 1] CONSTRUCTOR & DESTRUCTOR
    // =========================================================================

    DoublyLinkedList() {
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }

    ~DoublyLinkedList() {
        DNode<T>* current = head_;
        while (current != nullptr) {
            DNode<T>* next = current->next;
            delete current;
            current = next;
        }
    }


    // =========================================================================
    //  [SECTION 2] INSERTION
    // =========================================================================

    // -------------------------------------------------------------------------
    //  pushFront — inserts at the BEGINNING                         O(1)
    //
    //  Before: head → [10 ↔ 20 ↔ 30]
    //  pushFront(5)
    //  After : head → [5 ↔ 10 ↔ 20 ↔ 30]
    //
    //  Extra step vs singly: we must also set head_->prev = newNode
    //  so the old head can look back at the new node.
    // -------------------------------------------------------------------------
    void pushFront(T value) {
        DNode<T>* newNode = new DNode<T>(value);

        if (head_ == nullptr) {
            // empty list — new node is both head and tail
            head_ = newNode;
            tail_ = newNode;
        }
        else {
            newNode->next = head_;
            // └─ new node's next points to the old head

            head_->prev = newNode;
            // └─ OLD head's prev now points BACK to the new node
            //    THIS is the extra step that doesn't exist in singly list

            head_ = newNode;
            // └─ head moves to the new first node
            //    newNode->prev stays nullptr (it's the new head)
        }

        size_++;
    }

    // -------------------------------------------------------------------------
    //  pushBack — inserts at the END                                O(1)
    //
    //  Before: [10 ↔ 20 ↔ 30] ← tail
    //  pushBack(40)
    //  After : [10 ↔ 20 ↔ 30 ↔ 40] ← tail
    //
    //  Extra step vs singly: we must also set newNode->prev = tail_
    //  so the new node can look back at the old last node.
    // -------------------------------------------------------------------------
    void pushBack(T value) {
        DNode<T>* newNode = new DNode<T>(value);

        if (tail_ == nullptr) {
            head_ = newNode;
            tail_ = newNode;
        }
        else {
            newNode->prev = tail_;
            // └─ new node's prev points BACK to the old tail
            //    THIS is the extra step — singly never had this

            tail_->next = newNode;
            // └─ old tail's next now points forward to new node

            tail_ = newNode;
            // └─ tail advances to the new last node
            //    newNode->next stays nullptr (it's the new tail)
        }

        size_++;
    }

    // -------------------------------------------------------------------------
    //  insert — inserts at position index                           O(n)
    //
    //  After finding prev node, we must update FOUR pointers:
    //    newNode->prev  = prev
    //    newNode->next  = prev->next
    //    prev->next->prev = newNode    (old next looks back at newNode)
    //    prev->next     = newNode
    // -------------------------------------------------------------------------
    void insert(int index, T value) {
        if (index < 0 || index > size_) {
            cout << "[DoublyLinkedList] insert(" << index << ") out of range. "
                << "size=" << size_ << "\n";
            return;
        }

        if (index == 0) { pushFront(value); return; }
        if (index == size_) { pushBack(value);  return; }

        DNode<T>* newNode = new DNode<T>(value);

        // walk to the node just BEFORE index
        DNode<T>* prev = head_;
        for (int i = 0; i < index - 1; i++)
            prev = prev->next;

        DNode<T>* afterNew = prev->next;
        // └─ save the node that will come AFTER the new node

        // link new node between prev and afterNew
        newNode->prev = prev;         // new node looks back at prev
        newNode->next = afterNew;     // new node looks forward at afterNew

        prev->next = newNode;     // prev now points forward to new node
        afterNew->prev = newNode;     // afterNew now looks back at new node

        size_++;
    }


    // =========================================================================
    //  [SECTION 3] DELETION
    // =========================================================================

    // -------------------------------------------------------------------------
    //  popFront — removes the first node                            O(1)
    //
    //  Extra step vs singly: after moving head_, set head_->prev = nullptr
    //  so the new head doesn't look back at freed memory.
    // -------------------------------------------------------------------------
    void popFront() {
        if (isEmpty()) {
            cout << "[DoublyLinkedList] popFront() — empty\n"; return;
        }

        DNode<T>* toDelete = head_;
        head_ = head_->next;
        delete toDelete;

        if (head_ == nullptr) {
            tail_ = nullptr;   // list became empty
        }
        else {
            head_->prev = nullptr;
            // └─ new head has nothing before it — set prev to nullptr
            //    without this, head_->prev points to freed memory
        }

        size_--;
    }

    // -------------------------------------------------------------------------
    //  popBack — removes the last node                              O(1)
    //
    //  THIS IS THE KEY IMPROVEMENT over singly linked list.
    //  Singly needed to walk the entire list to find second-to-last → O(n)
    //  Doubly: tail_->prev gives us the second-to-last directly    → O(1)
    //
    //  Before: [...↔ 30 ↔ 40]  tail → [40]
    //  After : [...↔ 30]        tail → [30],  30->next = nullptr
    // -------------------------------------------------------------------------
    void popBack() {
        if (isEmpty()) {
            cout << "[DoublyLinkedList] popBack() — empty\n"; return;
        }

        if (head_ == tail_) {
            // only one node
            delete head_;
            head_ = nullptr;
            tail_ = nullptr;
            size_--;
            return;
        }

        DNode<T>* toDelete = tail_;

        tail_ = tail_->prev;
        // └─ tail moves BACK to the second-to-last node
        //    this is the O(1) magic — prev pointer gives it directly

        tail_->next = nullptr;
        // └─ new tail has nothing after it — cut the forward link

        delete toDelete;
        // └─ free the old tail node

        size_--;
    }

    // -------------------------------------------------------------------------
    //  remove — removes node at index                               O(n)
    //
    //  After finding the node to remove (current), update 4 pointers:
    //    current->prev->next = current->next
    //    current->next->prev = current->prev
    //  Then delete current.
    // -------------------------------------------------------------------------
    void remove(int index) {
        if (!isValidIndex(index)) {
            cout << "[DoublyLinkedList] remove(" << index << ") out of range. "
                << "size=" << size_ << "\n";
            return;
        }

        if (index == 0) { popFront(); return; }
        if (index == size_ - 1) { popBack();  return; }

        // walk to the node at index
        DNode<T>* current = head_;
        for (int i = 0; i < index; i++)
            current = current->next;

        // bypass current from both directions
        current->prev->next = current->next;
        // └─ node before current skips over it (forward direction)

        current->next->prev = current->prev;
        // └─ node after current skips over it (backward direction)
        //    this line is IMPOSSIBLE in a singly list

        delete current;
        size_--;
    }

    // -------------------------------------------------------------------------
    //  removeValue — removes first node with matching value         O(n)
    // -------------------------------------------------------------------------
    void removeValue(T value) {
        if (isEmpty()) {
            cout << "[DoublyLinkedList] removeValue() — empty\n"; return;
        }

        DNode<T>* current = head_;
        while (current != nullptr) {
            if (current->data == value) {
                // disconnect current from both neighbors
                if (current->prev != nullptr)
                    current->prev->next = current->next;
                else
                    head_ = current->next;   // removing head

                if (current->next != nullptr)
                    current->next->prev = current->prev;
                else
                    tail_ = current->prev;   // removing tail

                delete current;
                size_--;
                return;
            }
            current = current->next;
        }
        cout << "[DoublyLinkedList] removeValue() — not found\n";
    }


    // =========================================================================
    //  [SECTION 4] ACCESS
    // =========================================================================

    // O(n) — walks from head (or tail if index is closer to the end)
    T get(int index) const {
        if (!isValidIndex(index)) {
            cout << "[DoublyLinkedList] get(" << index << ") out of range. "
                << "size=" << size_ << "\n";
            return T{};
        }

        DNode<T>* current;

        // optimization: start from the closer end
        if (index <= size_ / 2) {
            // index is in the first half — walk forward from head
            current = head_;
            for (int i = 0; i < index; i++)
                current = current->next;
        }
        else {
            // index is in the second half — walk backward from tail
            current = tail_;
            for (int i = size_ - 1; i > index; i--)
                current = current->prev;
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


    // =========================================================================
    //  [SECTION 5] SEARCH
    // =========================================================================

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


    // =========================================================================
    //  [SECTION 6] UTILITY
    // =========================================================================

    // -------------------------------------------------------------------------
    //  reverse — reverses the list in-place                         O(n)
    //
    //  For each node: swap its prev and next pointers.
    //  Then swap head_ and tail_.
    //
    //  Before: head → [10 ↔ 20 ↔ 30] ← tail
    //  After : head → [30 ↔ 20 ↔ 10] ← tail
    // -------------------------------------------------------------------------
    void reverse() {
        if (size_ <= 1) return;

        DNode<T>* current = head_;

        while (current != nullptr) {
            // swap prev and next for this node
            DNode<T>* tmp = current->prev;
            current->prev = current->next;
            current->next = tmp;

            // move to the next node (which is now stored in current->prev
            // because we just swapped)
            current = current->prev;
        }

        // swap head and tail
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


    // =========================================================================
    //  [SECTION 7] STATE QUERIES
    // =========================================================================

    bool isEmpty()  const { return size_ == 0; }
    int  getSize()  const { return size_; }


    // =========================================================================
    //  [SECTION 8] DISPLAY
    // =========================================================================

    // O(n) — walks forward: head → tail
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

    // -------------------------------------------------------------------------
    //  printReverse — walks BACKWARD using prev pointers            O(n)
    //  This operation is IMPOSSIBLE in a singly linked list.
    //  Starts at tail_ and follows prev until nullptr.
    // -------------------------------------------------------------------------
    void printReverse() const {
        if (isEmpty()) { cout << "[ empty ]\n"; return; }

        DNode<T>* current = tail_;
        // └─ start at the last node — only possible because we have tail_

        cout << "nullptr ↔ [ ";
        while (current != nullptr) {
            cout << current->data;
            if (current->prev != nullptr) cout << " ↔ ";
            current = current->prev;
            // └─ move BACKWARD using the prev pointer
        }
        cout << " ] ↔ nullptr\n";
    }

    void printInfo() const {
        cout << "size=" << size_;
        if (!isEmpty())
            cout << " | head=" << head_->data
            << " | tail=" << tail_->data;
        cout << "\n";
    }

};


// =============================================================================
//  MAIN
// =============================================================================

void section(const char* title) {
    cout << "\n============================================================\n";
    cout << "  " << title << "\n";
    cout << "============================================================\n";
}

int main() {

    // =========================================================================
    //  Build
    // =========================================================================
    section("Creating DoublyLinkedList<int>");

    DoublyLinkedList<int> list;
    list.printInfo();


    // =========================================================================
    //  pushBack / pushFront
    // =========================================================================
    section("pushBack: 10, 20, 30, 40");

    list.pushBack(10);
    list.pushBack(20);
    list.pushBack(30);
    list.pushBack(40);
    list.print();
    list.printInfo();

    section("pushFront: 5");

    list.pushFront(5);
    list.print();
    list.printInfo();   // head=5, tail=40


    // =========================================================================
    //  print / printReverse
    // =========================================================================
    section("print() forward vs printReverse() backward");

    cout << "forward  : "; list.print();
    cout << "backward : "; list.printReverse();


    // =========================================================================
    //  get — optimized: starts from closer end
    // =========================================================================
    section("get() — starts from closer end");

    cout << "get(0) from head : " << list.get(0) << "\n";   // 5
    cout << "get(4) from tail : " << list.get(4) << "\n";   // 40
    cout << "get(2) middle    : " << list.get(2) << "\n";   // 20
    cout << "front()          : " << list.front() << "\n";  // 5
    cout << "back()           : " << list.back() << "\n";  // 40


    // =========================================================================
    //  insert
    // =========================================================================
    section("insert(2, 15)");

    list.insert(2, 15);
    list.print();   // nullptr ↔ [ 5 ↔ 10 ↔ 15 ↔ 20 ↔ 30 ↔ 40 ] ↔ nullptr


    // =========================================================================
    //  popFront / popBack — both O(1)
    // =========================================================================
    section("popFront() — O(1)");

    list.popFront();
    list.print();

    section("popBack() — O(1) thanks to prev pointer");

    list.popBack();
    list.print();
    list.printInfo();


    // =========================================================================
    //  remove / removeValue
    // =========================================================================
    section("remove(1)");

    list.remove(1);
    list.print();

    section("removeValue(30)");

    list.removeValue(30);
    list.print();


    // =========================================================================
    //  search / contains / count
    // =========================================================================
    section("search / contains / count");

    list.pushBack(20);
    list.pushBack(20);

    cout << "search(20)   : index " << list.search(20) << "\n";
    cout << "contains(20) : " << list.contains(20) << "\n";
    cout << "count(20)    : " << list.count(20) << "\n";


    // =========================================================================
    //  reverse
    // =========================================================================
    section("reverse()");

    DoublyLinkedList<int> rev;
    rev.pushBack(1); rev.pushBack(2);
    rev.pushBack(3); rev.pushBack(4);
    rev.pushBack(5);

    cout << "before   : "; rev.print();
    rev.reverse();
    cout << "after    : "; rev.print();
    cout << "backward : "; rev.printReverse();
    rev.printInfo();


    // =========================================================================
    //  clear
    // =========================================================================
    section("clear()");

    list.clear();
    list.printInfo();


    // =========================================================================
    //  Works with double
    // =========================================================================
    section("DoublyLinkedList<double>");

    DoublyLinkedList<double> d;
    d.pushBack(1.1); d.pushBack(2.2); d.pushBack(3.3);
    cout << "forward  : "; d.print();
    cout << "backward : "; d.printReverse();


    // =========================================================================
    //  Error handling
    // =========================================================================
    section("Error handling");

    DoublyLinkedList<int> e;
    e.popFront();    // [ERROR] empty
    e.popBack();     // [ERROR] empty
    e.get(5);        // [ERROR] out of range


    // =========================================================================
    //  END
    // =========================================================================
    cout << "\n============================================================\n";
    cout << "  Phase 3 — DoublyLinkedList<T> complete\n";
    cout << "============================================================\n\n";

    return 0;
}


// =============================================================================
//  CHEAT SHEET — DoublyLinkedList<T> quick reference
// =============================================================================
//
//  CONSTRUCTION
//  DoublyLinkedList<T> list;        empty list
//  ~DoublyLinkedList()              auto-called, frees all nodes
//
//  INSERTION            Complexity
//  list.pushFront(val)  O(1)
//  list.pushBack(val)   O(1)
//  list.insert(i, val)  O(n)
//
//  DELETION
//  list.popFront()      O(1)
//  list.popBack()       O(1)   ← true O(1) thanks to prev pointer
//  list.remove(i)       O(n)
//  list.removeValue(v)  O(n)
//
//  ACCESS
//  list.get(i)          O(n)   optimized: starts from closer end
//  list.front()         O(1)
//  list.back()          O(1)
//
//  SEARCH
//  list.search(val)     O(n)   first index or -1
//  list.contains(val)   O(n)   true / false
//  list.count(val)      O(n)   occurrences
//
//  UTILITY
//  list.reverse()       O(n)   swap prev/next of every node
//  list.clear()         O(n)   delete all nodes
//
//  STATE
//  list.isEmpty()       O(1)
//  list.getSize()       O(1)
//
//  DISPLAY
//  list.print()         O(n)   nullptr ↔ [ 10 ↔ 20 ↔ 30 ] ↔ nullptr
//  list.printReverse()  O(n)   walks backward using prev — impossible in singly
//  list.printInfo()     O(1)   size | head | tail
//
//  KEY RULE:
//  Every insert/delete must maintain FOUR pointers, not two:
//  newNode->prev, newNode->next, neighbor->next, neighbor->prev
// =============================================================================