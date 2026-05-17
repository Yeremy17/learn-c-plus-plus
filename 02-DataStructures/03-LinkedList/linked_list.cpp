// =============================================================================
//  DATA STRUCTURES EN C++ / FASE 1
//  Topic  : Singly Linked List
//  Author : Yeremy Acuña Chavez
//  Repo   : https://github.com/yeremyacuna
// =============================================================================
//
//  INDEX
//  ─────────────────────────────────────────────────────────────────────────
//  [CLASS 1]  Node<T>
//             - data        : the stored value
//             - next        : pointer to the next node
//
//  [CLASS 2]  LinkedList<T>
//
//  [SECTION 1] Constructor & Destructor
//              - LinkedList()                         O(1)
//              - ~LinkedList()                        O(n)
//
//  [SECTION 2] Insertion
//              - pushFront(T value)                   O(1)
//              - pushBack(T value)                    O(1)   ← tail makes this O(1)
//              - insert(int index, T value)           O(n)
//
//  [SECTION 3] Deletion
//              - popFront()                           O(1)
//              - popBack()                            O(1)   ← tail makes this O(1)
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
//              - printInfo()                          O(1)
//  ─────────────────────────────────────────────────────────────────────────
//
//  MEMORY MODEL
//  ─────────────────────────────────────────────────────────────────────────
//
//  head                              tail
//   ↓                                 ↓
//  [10|→] → [20|→] → [30|→] → [40|∅]
//
//  Each node lives at a RANDOM address in the heap.
//  head  → always points to the first node  (nullptr if empty)
//  tail  → always points to the last node   (nullptr if empty)
//  tail->next is ALWAYS nullptr
//
//  KEY POINTER VARIABLES used during operations:
//  ─────────────────────────────────────────────────────────────────────────
//  current  → walks the list node by node  (current = current->next)
//  prev     → stays one step behind current (needed to reconnect on delete)
//  newNode  → freshly created node before being linked into the list
//
//  Compile: g++ -std=c++17 -Wall -Wextra -o fase_01_ll fase_01_linked_list.cpp
//  Run    : ./fase_01_ll
// =============================================================================

#include <iostream>

using namespace std;


// =============================================================================
//  CLASS 1 / Node<T>
//
//  Represents a single element in the list.
//  Does NOT know it belongs to a list / it just holds data and a next pointer.
// =============================================================================

template <typename T>
class Node {
public:

    T     data;   // the value stored in this node
    Node* next;   // pointer to the next node (nullptr if this is the last)

    // -------------------------------------------------------------------------
    //  Constructor
    //  Initializes data with 'value' and next with nullptr.
    //  Every new node starts disconnected / LinkedList decides where to link it.
    //  Complexity: O(1)
    // -------------------------------------------------------------------------
    Node(T value) {
        data = value;
        next = nullptr;
        //    └─ always nullptr at birth / the list will set this when linking
    }
};


// =============================================================================
//  CLASS 2 / LinkedList<T>
//
//  Manages the chain of nodes.
//  Owns head (first), tail (last), and size.
//  All operations go through this class / Node never modifies itself.
// =============================================================================

template <typename T>
class LinkedList {

private:

    Node<T>* head_;   // pointer to the first node  (nullptr = empty list)
    Node<T>* tail_;   // pointer to the last node   (nullptr = empty list)
    int      size_;   // number of nodes currently in the list

    // -------------------------------------------------------------------------
    //  isValidIndex / guards index-based operations               O(1)
    // -------------------------------------------------------------------------
    bool isValidIndex(int index) const {
        return (index >= 0 && index < size_);
    }


public:

    // =========================================================================
    //  [SECTION 1] CONSTRUCTOR & DESTRUCTOR
    // =========================================================================

    // -------------------------------------------------------------------------
    //  Constructor / empty list
    //  head_ and tail_ are nullptr because there are no nodes yet.
    //  Complexity: O(1)
    // -------------------------------------------------------------------------
    LinkedList() {
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }

    // -------------------------------------------------------------------------
    //  Destructor / walks the list and deletes every node          O(n)
    //
    //  WHY we need a loop and not just  delete head_:
    //  Each node is a SEPARATE heap allocation / they are not contiguous.
    //  Deleting head_ only frees the first node, the rest leak forever.
    //  We must visit and delete each one individually.
    //
    //  The trick: save next BEFORE deleting current,
    //  otherwise current->next is gone and we lose the chain.
    //
    //    current       next (saved)
    //       ↓              ↓
    //      [10] →        [20] → [30] → nullptr
    //    delete current        ← now safe, next is already saved
    //    current = next        ← advance to [20]
    // -------------------------------------------------------------------------
    ~LinkedList() {
        Node<T>* current = head_;

        while (current != nullptr) {
            Node<T>* next = current->next;   // save next BEFORE delete
            delete current;                   // free this node from heap
            current = next;                   // advance to the saved next
        }
        // head_ and tail_ become dangling after this / but the object is
        // being destroyed anyway so it doesn't matter
    }


    // =========================================================================
    //  [SECTION 2] INSERTION
    // =========================================================================

    // -------------------------------------------------------------------------
    //  pushFront / inserts a new node at the BEGINNING              O(1)
    //
    //  Before: head → [20] → [30] → nullptr
    //  After : head → [10] → [20] → [30] → nullptr
    //
    //  Steps:
    //    1. create newNode
    //    2. newNode->next = head_   (new node points to old first)
    //    3. head_ = newNode         (head now points to new node)
    //    4. if list was empty, tail_ also points to newNode
    // -------------------------------------------------------------------------
    void pushFront(T value) {
        Node<T>* newNode = new Node<T>(value);
        //                 └─ creates node on heap, next = nullptr

        newNode->next = head_;
        // └─ new node's next points to whoever was first before
        //    if list was empty, head_ was nullptr → newNode->next = nullptr ✓

        head_ = newNode;
        // └─ head now points to the new first node

        if (tail_ == nullptr) {
            tail_ = newNode;
            // └─ list was empty before this push
            //    now both head_ and tail_ point to the only node
        }

        size_++;
    }

    // -------------------------------------------------------------------------
    //  pushBack / inserts a new node at the END                     O(1)
    //
    //  Before: head → [10] → [20] → nullptr    tail → [20]
    //  After : head → [10] → [20] → [30] → nullptr   tail → [30]
    //
    //  WHY O(1): tail_ always points to the last node directly.
    //  Without tail we would need to walk the entire list to find the end.
    //
    //  Steps:
    //    1. create newNode
    //    2. tail_->next = newNode   (old last node now points to new node)
    //    3. tail_ = newNode         (tail moves to the new last node)
    //    4. if list was empty, head_ also points to newNode
    // -------------------------------------------------------------------------
    void pushBack(T value) {
        Node<T>* newNode = new Node<T>(value);

        if (tail_ == nullptr) {
            // list is empty / new node is both head and tail
            head_ = newNode;
            tail_ = newNode;
        }
        else {
            tail_->next = newNode;
            // └─ old last node's next now points to new node
            //    this is the link that chains them together

            tail_ = newNode;
            // └─ tail_ advances to the new last node
            //    newNode->next is already nullptr (set in Node constructor)
        }

        size_++;
    }

    // -------------------------------------------------------------------------
    //  insert / inserts value at position 'index'                   O(n)
    //
    //  insert(0, val)         → same as pushFront
    //  insert(size_, val)     → same as pushBack
    //  insert(1, 15):
    //    Before: [10] → [20] → [30]
    //    After : [10] → [15] → [20] → [30]
    //
    //  Steps:
    //    Walk to the node just BEFORE index (prev).
    //    newNode->next = prev->next   (new node points to what came after prev)
    //    prev->next    = newNode      (prev now points to new node)
    // -------------------------------------------------------------------------
    void insert(int index, T value) {
        if (index < 0 || index > size_) {
            cout << "[LinkedList] insert(" << index << ") out of range. "
                << "size=" << size_ << "\n";
            return;
        }

        // delegate edge cases to the O(1) operations
        if (index == 0) { pushFront(value); return; }
        if (index == size_) { pushBack(value);  return; }

        Node<T>* newNode = new Node<T>(value);

        // walk to the node just BEFORE position 'index'
        Node<T>* prev = head_;
        for (int i = 0; i < index - 1; i++) {
            prev = prev->next;
            // each step: prev advances one node forward
        }
        // now prev is at position index-1

        newNode->next = prev->next;
        // └─ new node's next = the node that was at 'index' before
        //    this preserves the rest of the chain

        prev->next = newNode;
        // └─ the node before 'index' now points to the new node
        //    chain is restored: prev → newNode → old[index] → ...

        size_++;
    }


    // =========================================================================
    //  [SECTION 3] DELETION
    // =========================================================================

    // -------------------------------------------------------------------------
    //  popFront / removes the first node                            O(1)
    //
    //  Before: head → [10] → [20] → [30]
    //  After : head → [20] → [30]
    //
    //  Steps:
    //    1. save head_->next as the new head
    //    2. delete old head
    //    3. if list becomes empty, reset tail_ to nullptr
    // -------------------------------------------------------------------------
    void popFront() {
        if (isEmpty()) {
            cout << "[LinkedList] popFront() / empty\n"; return;
        }

        Node<T>* toDelete = head_;
        // └─ save pointer to first node so we can delete it after moving head_

        head_ = head_->next;
        // └─ head now points to the second node (or nullptr if only one existed)

        delete toDelete;
        // └─ free the old first node from heap

        if (head_ == nullptr) {
            tail_ = nullptr;
            // └─ list is now empty / tail must also be nullptr
        }

        size_--;
    }

    // -------------------------------------------------------------------------
    //  popBack / removes the last node                              O(1)
    //
    //  Before: head → [10] → [20] → [30]    tail → [30]
    //  After : head → [10] → [20] → nullptr  tail → [20]
    //
    //  PROBLEM: to update tail_ we need to know the node BEFORE the last one.
    //  We must walk the list to find it / this makes it O(n) in practice
    //  unless we use a Doubly Linked List (which has a prev pointer).
    //  For a singly linked list this is the accepted tradeoff.
    // -------------------------------------------------------------------------
    void popBack() {
        if (isEmpty()) {
            cout << "[LinkedList] popBack() / empty\n"; return;
        }

        // special case: only one node
        if (head_ == tail_) {
            delete head_;
            head_ = nullptr;
            tail_ = nullptr;
            size_--;
            return;
        }

        // walk to the node just BEFORE tail_
        Node<T>* prev = head_;
        while (prev->next != tail_) {
            prev = prev->next;
            // stop when prev->next is the last node (tail_)
        }

        // prev is now the second-to-last node
        delete tail_;         // free the last node
        tail_ = prev;   // second-to-last becomes new tail
        tail_->next = nullptr;// new tail has no next

        size_--;
    }

    // -------------------------------------------------------------------------
    //  remove / removes the node at position 'index'                O(n)
    //
    //  Uses the prev + current pattern:
    //  prev follows one step behind current.
    //  When current reaches index, prev->next = current->next skips it.
    //
    //    prev        current
    //     ↓              ↓
    //    [10]  →      [20]  →  [30]
    //    prev->next = current->next   →  [10] → [30]
    //    delete current
    // -------------------------------------------------------------------------
    void remove(int index) {
        if (!isValidIndex(index)) {
            cout << "[LinkedList] remove(" << index << ") out of range. "
                << "size=" << size_ << "\n";
            return;
        }

        if (index == 0) { popFront(); return; }
        if (index == size_ - 1) { popBack();  return; }

        Node<T>* prev = head_;
        Node<T>* current = head_->next;

        for (int i = 1; i < index; i++) {
            prev = prev->next;
            current = current->next;
            // both pointers advance together / prev always one step behind
        }

        prev->next = current->next;
        // └─ prev skips over current / current is now unreachable from the list

        delete current;
        // └─ current has been unlinked / safe to free from heap

        size_--;
    }

    // -------------------------------------------------------------------------
    //  removeValue / removes the FIRST node whose data matches value O(n)
    // -------------------------------------------------------------------------
    void removeValue(T value) {
        if (isEmpty()) {
            cout << "[LinkedList] removeValue() / empty\n"; return;
        }

        // special case: first node matches
        if (head_->data == value) { popFront(); return; }

        Node<T>* prev = head_;
        Node<T>* current = head_->next;

        while (current != nullptr) {
            if (current->data == value) {
                prev->next = current->next;   // unlink current

                if (current == tail_) {
                    tail_ = prev;             // update tail if we removed the last
                }

                delete current;
                size_--;
                return;
            }
            prev = current;
            current = current->next;
        }

        cout << "[LinkedList] removeValue() / value not found\n";
    }


    // =========================================================================
    //  [SECTION 4] ACCESS
    // =========================================================================

    // -------------------------------------------------------------------------
    //  get / returns the value at position 'index'                  O(n)
    //  Must walk from head / no direct address calculation like arrays.
    // -------------------------------------------------------------------------
    T get(int index) const {
        if (!isValidIndex(index)) {
            cout << "[LinkedList] get(" << index << ") out of range. "
                << "size=" << size_ << "\n";
            return T{};
        }

        Node<T>* current = head_;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    // O(1) / head_ always points directly to the first node
    T front() const {
        if (isEmpty()) { cout << "[LinkedList] front() / empty\n"; return T{}; }
        return head_->data;
    }

    // O(1) / tail_ always points directly to the last node
    T back() const {
        if (isEmpty()) { cout << "[LinkedList] back() / empty\n"; return T{}; }
        return tail_->data;
    }


    // =========================================================================
    //  [SECTION 5] SEARCH
    // =========================================================================

    // O(n) / first index of value, -1 if not found
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

    // O(n) / true if value exists anywhere in the list
    bool contains(T value) const {
        return search(value) != -1;
    }

    // O(n) / number of nodes whose data matches value
    int count(T value) const {
        Node<T>* current = head_;
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
    //  reverse / reverses the list in-place                         O(n)
    //
    //  Uses three pointers: prev, current, next
    //
    //  Start:   nullptr  [10] → [20] → [30] → nullptr
    //  Step 1:  prev=null, current=[10], save next=[20]
    //           current->next = prev (nullptr)  →  [10] → nullptr
    //           prev=[10], current=[20]
    //  Step 2:  save next=[30]
    //           current->next = prev ([10])     →  [20] → [10] → nullptr
    //           prev=[20], current=[30]
    //  Step 3:  save next=nullptr
    //           current->next = prev ([20])     →  [30] → [20] → [10] → nullptr
    //           prev=[30], current=nullptr → stop
    //  Result:  head=[30], tail=[10]
    // -------------------------------------------------------------------------
    void reverse() {
        if (size_ <= 1) return;   // nothing to reverse

        Node<T>* prev = nullptr;
        Node<T>* current = head_;
        tail_ = head_;            // old head becomes new tail

        while (current != nullptr) {
            Node<T>* next = current->next;   // save next before overwriting
            current->next = prev;             // reverse the pointer
            prev = current;          // prev advances
            current = next;             // current advances
        }

        head_ = prev;
        // └─ prev ended at the last node (which is the new first)
    }

    // -------------------------------------------------------------------------
    //  clear / deletes all nodes, resets to empty list              O(n)
    // -------------------------------------------------------------------------
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


    // =========================================================================
    //  [SECTION 7] STATE QUERIES
    // =========================================================================

    bool isEmpty()  const { return size_ == 0; }
    int  getSize()  const { return size_; }


    // =========================================================================
    //  [SECTION 8] DISPLAY
    // =========================================================================

    // O(n) / prints all nodes as: [ 10 -> 20 -> 30 -> nullptr ]
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

    // O(1) / prints size, head value, tail value
    void printInfo() const {
        cout << "size=" << size_;
        if (!isEmpty()) {
            cout << " | head=" << head_->data
                << " | tail=" << tail_->data;
        }
        cout << "\n";
    }

};


// =============================================================================
//  MAIN / runs all operations
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
    section("Creating LinkedList<int>");

    LinkedList<int> list;
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
    //  get / front / back
    // =========================================================================
    section("get / front / back");

    cout << "get(0)  : " << list.get(0) << "\n";   // 5
    cout << "get(2)  : " << list.get(2) << "\n";   // 20
    cout << "front() : " << list.front() << "\n";   // 5
    cout << "back()  : " << list.back() << "\n";   // 40


    // =========================================================================
    //  insert
    // =========================================================================
    section("insert(2, 15) / between index 1 and 2");

    list.insert(2, 15);
    list.print();   // [ 5 -> 10 -> 15 -> 20 -> 30 -> 40 -> nullptr ]


    // =========================================================================
    //  popFront / popBack / remove / removeValue
    // =========================================================================
    section("popFront()");

    list.popFront();
    list.print();   // [ 10 -> 15 -> 20 -> 30 -> 40 -> nullptr ]

    section("popBack()");

    list.popBack();
    list.print();   // [ 10 -> 15 -> 20 -> 30 -> nullptr ]

    section("remove(1) / removes index 1");

    list.remove(1);
    list.print();   // [ 10 -> 20 -> 30 -> nullptr ]

    section("removeValue(20)");

    list.removeValue(20);
    list.print();   // [ 10 -> 30 -> nullptr ]


    // =========================================================================
    //  search / contains / count
    // =========================================================================
    section("search / contains / count");

    list.pushBack(10);   // [ 10 -> 30 -> 10 ]
    list.pushBack(10);   // [ 10 -> 30 -> 10 -> 10 ]

    cout << "search(30)   : index " << list.search(30) << "\n";   // 1
    cout << "search(99)   : index " << list.search(99) << "\n";   // -1
    cout << "contains(10) : " << list.contains(10) << "\n";          // 1
    cout << "count(10)    : " << list.count(10) << "\n";           // 3


    // =========================================================================
    //  reverse
    // =========================================================================
    section("reverse()");

    LinkedList<int> rev;
    rev.pushBack(1);
    rev.pushBack(2);
    rev.pushBack(3);
    rev.pushBack(4);
    rev.pushBack(5);
    cout << "before: "; rev.print();
    rev.reverse();
    cout << "after : "; rev.print();
    rev.printInfo();   // head=5, tail=1


    // =========================================================================
    //  clear
    // =========================================================================
    section("clear()");

    list.clear();
    list.printInfo();   // size=0, empty


    // =========================================================================
    //  Works with double
    // =========================================================================
    section("LinkedList<double>");

    LinkedList<double> d;
    d.pushBack(1.1);
    d.pushBack(2.2);
    d.pushBack(3.3);
    d.print();
    cout << "front=" << d.front() << " | back=" << d.back() << "\n";


    // =========================================================================
    //  Works with char
    // =========================================================================
    section("LinkedList<char>");

    LinkedList<char> c;
    c.pushBack('a');
    c.pushBack('b');
    c.pushBack('c');
    c.print();


    // =========================================================================
    //  Error handling
    // =========================================================================
    section("Error handling");

    LinkedList<int> e;
    e.popFront();       // [ERROR] empty
    e.get(5);           // [ERROR] out of range
    e.remove(0);        // [ERROR] out of range


    // =========================================================================
    //  END
    // =========================================================================
    cout << "\n============================================================\n";
    cout << "  Phase 1 / LinkedList<T> complete\n";
    cout << "============================================================\n\n";

    return 0;
}


// =============================================================================
//  CHEAT SHEET / LinkedList<T> quick reference
// =============================================================================
//
//  CONSTRUCTION
//  LinkedList<T> list;              empty list, head=null, tail=null
//  ~LinkedList()                    auto-called, walks and deletes all nodes
//
//  INSERTION            Complexity
//  list.pushFront(val)  O(1)        insert at beginning
//  list.pushBack(val)   O(1)        insert at end  (tail makes this O(1))
//  list.insert(i, val)  O(n)        insert at index i
//
//  DELETION
//  list.popFront()      O(1)        remove first node
//  list.popBack()       O(n)        remove last node (singly: must walk to prev)
//  list.remove(i)       O(n)        remove at index i
//  list.removeValue(v)  O(n)        remove first node with matching value
//
//  ACCESS
//  list.get(i)          O(n)        value at index i  (must walk from head)
//  list.front()         O(1)        first value
//  list.back()          O(1)        last value
//
//  SEARCH
//  list.search(val)     O(n)        first index or -1
//  list.contains(val)   O(n)        true / false
//  list.count(val)      O(n)        occurrences
//
//  UTILITY
//  list.reverse()       O(n)        reverse in-place with 3-pointer technique
//  list.clear()         O(n)        delete all nodes, reset to empty
//
//  STATE
//  list.isEmpty()       O(1)
//  list.getSize()       O(1)
//
//  DISPLAY
//  list.print()         O(n)        [ 10 -> 20 -> 30 -> nullptr ]
//  list.printInfo()     O(1)        size | head | tail
//
//  KEY VARIABLES inside operations:
//  current  / walks the list:  current = current->next
//  prev     / one step behind: needed to reconnect chain on delete
//  newNode  / freshly created node before being linked into the list
//  next     / saved before overwriting current->next (used in reverse/destructor)
// =============================================================================