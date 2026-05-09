// =============================================================================
//  DATA STRUCTURES EN C++ / FASE 2
//  Topic  : Queue (FIFO)
//  Author : Yeremy Acuña Chavez
//  Repo   : https://github.com/yeremyacuna
// =============================================================================
//
//  INDEX
//  ─────────────────────────────────────────────────────────────────────────
//  [CLASS 1]  Node<T>
//  [CLASS 2]  Queue<T>
//
//  [SECTION 1] Constructor & Destructor
//              - Queue()                    O(1)
//              - ~Queue()                   O(n)
//
//  [SECTION 2] Core Operations
//              - enqueue(T value)           O(1)
//              - dequeue()                  O(1)
//              - front()                    O(1)
//              - back()                     O(1)
//
//  [SECTION 3] Utility
//              - clear()                    O(n)
//
//  [SECTION 4] State Queries
//              - isEmpty()                  O(1)
//              - getSize()                  O(1)
//
//  [SECTION 5] Display
//              - print()                    O(n)
//  ─────────────────────────────────────────────────────────────────────────
//
//  WHAT IS A QUEUE?
//  ─────────────────────────────────────────────────────────────────────────
//  FIFO / First In, First Out.
//  The first element enqueued is the first one dequeued.
//  Operates on TWO ends: enqueue at back, dequeue at front.
//
//  MEMORY MODEL (built on top of a linked list)
//  ─────────────────────────────────────────────────────────────────────────
//  front                          back
//   ↓                              ↓
//  [10] → [20] → [30] → [40] → nullptr
//
//  front = head of the linked list   → dequeue = popFront   O(1)
//  back  = tail of the linked list   → enqueue = pushBack   O(1)
//
//  STACK vs QUEUE
//  ─────────────────────────────────────────────────────────────────────────
//  Stack → LIFO → one end (top)     → push/pop same side
//  Queue → FIFO → two ends          → enqueue back, dequeue front
//
//  REAL WORLD USES
//  ─────────────────────────────────────────────────────────────────────────
//  - Print queue      (jobs processed in arrival order)
//  - BFS traversal    (graphs / Phase 6)
//  - OS scheduling    (CPU processes waiting for execution)
//  - Network buffers  (packets processed in order)
//  - Support tickets  (first complaint, first served)
//
//  Compile: g++ -std=c++17 -Wall -Wextra -o fase_02_queue fase_02_queue.cpp
//  Run    : ./fase_02_queue
// =============================================================================

#include <iostream>

using namespace std;


// =============================================================================
//  CLASS 1 / Node<T>
// =============================================================================

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


// =============================================================================
//  CLASS 2 / Queue<T>
//
//  front_ : pointer to the first node  (where we dequeue from)
//  back_  : pointer to the last node   (where we enqueue to)
//  size_  : number of elements in the queue
// =============================================================================

template <typename T>
class Queue {

private:

    Node<T>* front_;
    Node<T>* back_;
    int      size_;


public:

    // =========================================================================
    //  [SECTION 1] CONSTRUCTOR & DESTRUCTOR
    // =========================================================================

    // -------------------------------------------------------------------------
    //  Constructor / empty queue                                     O(1)
    // -------------------------------------------------------------------------
    Queue() {
        front_ = nullptr;
        back_ = nullptr;
        size_ = 0;
    }

    // -------------------------------------------------------------------------
    //  Destructor / walks and deletes every node                     O(n)
    // -------------------------------------------------------------------------
    ~Queue() {
        Node<T>* current = front_;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }


    // =========================================================================
    //  [SECTION 2] CORE OPERATIONS
    // =========================================================================

    // -------------------------------------------------------------------------
    //  enqueue / adds a new element at the BACK                      O(1)
    //
    //  Before: front → [10] → [20] → nullptr   back → [20]
    //  enqueue(30)
    //  After : front → [10] → [20] → [30] → nullptr   back → [30]
    //
    //  Exactly pushBack() from LinkedList:
    //    1. create newNode
    //    2. back_->next = newNode   (old last node points to new node)
    //    3. back_ = newNode         (back moves to the new last node)
    //    4. if queue was empty, front_ also points to newNode
    // -------------------------------------------------------------------------
    void enqueue(T value) {
        Node<T>* newNode = new Node<T>(value);

        if (back_ == nullptr) {
            // queue is empty / new node is both front and back
            front_ = newNode;
            back_ = newNode;
        }
        else {
            back_->next = newNode;
            // └─ old last node now points to the new node

            back_ = newNode;
            // └─ back_ advances to the new last node
            //    newNode->next is already nullptr (set in Node constructor)
        }

        size_++;
    }

    // -------------------------------------------------------------------------
    //  dequeue / removes the element at the FRONT                    O(1)
    //
    //  Before: front → [10] → [20] → [30] → nullptr
    //  dequeue()
    //  After : front → [20] → [30] → nullptr
    //
    //  Exactly popFront() from LinkedList:
    //    1. save front_ in toDelete
    //    2. advance front_ to front_->next
    //    3. delete toDelete
    //    4. if queue becomes empty, reset back_ to nullptr
    // -------------------------------------------------------------------------
    void dequeue() {
        if (isEmpty()) {
            cout << "[Queue] dequeue() / queue is empty\n";
            return;
        }

        Node<T>* toDelete = front_;
        // └─ save current front before moving the pointer

        front_ = front_->next;
        // └─ front moves to the second node (or nullptr if only one existed)

        delete toDelete;
        // └─ free the old front node from heap

        if (front_ == nullptr) {
            back_ = nullptr;
            // └─ queue is now empty / back must also be nullptr
        }

        size_--;
    }

    // -------------------------------------------------------------------------
    //  front / returns the FRONT value without removing it           O(1)
    //  "Who is next in line?" / look without serving.
    // -------------------------------------------------------------------------
    T front() const {
        if (isEmpty()) {
            cout << "[Queue] front() / queue is empty\n";
            return T{};
        }
        return front_->data;
    }

    // -------------------------------------------------------------------------
    //  back / returns the BACK value without removing it             O(1)
    //  "Who is last in line?" / look without changing anything.
    // -------------------------------------------------------------------------
    T back() const {
        if (isEmpty()) {
            cout << "[Queue] back() / queue is empty\n";
            return T{};
        }
        return back_->data;
    }


    // =========================================================================
    //  [SECTION 3] UTILITY
    // =========================================================================

    // -------------------------------------------------------------------------
    //  clear / removes all nodes, resets to empty queue              O(n)
    // -------------------------------------------------------------------------
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


    // =========================================================================
    //  [SECTION 4] STATE QUERIES
    // =========================================================================

    bool isEmpty()  const { return size_ == 0; }
    int  getSize()  const { return size_; }


    // =========================================================================
    //  [SECTION 5] DISPLAY
    // =========================================================================

    // O(n) / prints from front to back
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


// =============================================================================
//  MAIN / runs all operations + real world demos
// =============================================================================

void section(const char* title) {
    cout << "\n============================================================\n";
    cout << "  " << title << "\n";
    cout << "============================================================\n";
}

int main() {

    // =========================================================================
    //  Basic operations
    // =========================================================================
    section("Creating Queue<int>");

    Queue<int> q;
    cout << "isEmpty: " << q.isEmpty() << "\n";   // 1


    section("enqueue: 10, 20, 30, 40");

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.print();                                       // front → [ 10 | 20 | 30 | 40 ] ← back
    cout << "size  : " << q.getSize() << "\n";      // 4
    cout << "front : " << q.front() << "\n";      // 10
    cout << "back  : " << q.back() << "\n";      // 40


    section("dequeue x2 / FIFO order");

    cout << "serving: " << q.front() << "\n";   // 10 / first in, first out
    q.dequeue();
    q.print();

    cout << "serving: " << q.front() << "\n";   // 20
    q.dequeue();
    q.print();


    section("enqueue more / queue keeps growing");

    q.enqueue(50);
    q.enqueue(60);
    q.print();   // front → [ 30 | 40 | 50 | 60 ] ← back


    section("clear()");

    q.clear();
    cout << "isEmpty after clear: " << q.isEmpty() << "\n";


    section("Error handling");

    Queue<int> empty;
    empty.dequeue();   // [ERROR] empty
    empty.front();     // [ERROR] empty
    empty.back();      // [ERROR] empty


    // =========================================================================
    //  REAL WORLD DEMO 1 / Print Queue
    //  Documents arrive and are printed in order of arrival.
    //  New documents go to the back.
    //  The printer always takes from the front.
    // =========================================================================
    section("Real World Demo 1 / Print Queue");

    Queue<const char*> printer;

    // documents arrive
    cout << "Documents arriving:\n";
    printer.enqueue("report.pdf");
    cout << "  + report.pdf\n";
    printer.enqueue("invoice.pdf");
    cout << "  + invoice.pdf\n";
    printer.enqueue("photo.png");
    cout << "  + photo.png\n";
    printer.enqueue("contract.pdf");
    cout << "  + contract.pdf\n";

    cout << "\nQueue: "; printer.print();

    // printer processes one by one
    cout << "\nPrinting:\n";
    while (!printer.isEmpty()) {
        cout << "  printing: " << printer.front() << "\n";
        printer.dequeue();
    }
    cout << "All documents printed.\n";


    // =========================================================================
    //  REAL WORLD DEMO 2 / OS Process Scheduler (Round Robin simplified)
    //  Each process gets a time slice.
    //  If not finished, it goes back to the end of the queue.
    //  Simulates a basic CPU round-robin scheduler.
    // =========================================================================
    section("Real World Demo 2 / CPU Process Scheduler");

    struct Process {
        const char* name;
        int         burstTime;   // how many time units it needs

        bool operator==(const Process& other) const {
            return name == other.name;
        }
    };

    Queue<Process> scheduler;
    scheduler.enqueue({ "P1", 4 });
    scheduler.enqueue({ "P2", 2 });
    scheduler.enqueue({ "P3", 5 });
    scheduler.enqueue({ "P4", 1 });

    int timeSlice = 2;   // each process gets 2 units per turn
    int clock = 0;

    cout << "Time slice = " << timeSlice << "\n\n";

    while (!scheduler.isEmpty()) {
        Process p = scheduler.front();
        scheduler.dequeue();

        int executed = (p.burstTime > timeSlice) ? timeSlice : p.burstTime;
        p.burstTime -= executed;
        clock += executed;

        cout << "t=" << clock << "  ran " << p.name
            << "  remaining=" << p.burstTime << "\n";

        if (p.burstTime > 0) {
            scheduler.enqueue(p);   // not finished / back to queue
            cout << "        " << p.name << " re-queued\n";
        }
        else {
            cout << "        " << p.name << " FINISHED\n";
        }
    }


    // =========================================================================
    //  Works with other types
    // =========================================================================
    section("Queue<double>");

    Queue<double> qd;
    qd.enqueue(1.1); qd.enqueue(2.2); qd.enqueue(3.3);
    qd.print();
    cout << "front=" << qd.front() << " | back=" << qd.back() << "\n";


    // =========================================================================
    //  END
    // =========================================================================
    cout << "\n============================================================\n";
    cout << "  Phase 2 / Queue<T> complete\n";
    cout << "============================================================\n\n";

    return 0;
}


// =============================================================================
//  CHEAT SHEET / Queue<T> quick reference
// =============================================================================
//
//  CONSTRUCTION
//  Queue<T> q;              empty queue, front=null, back=null
//  ~Queue()                 auto-called, frees all nodes
//
//  CORE              Complexity
//  q.enqueue(val)    O(1)   add at back    (pushBack on linked list)
//  q.dequeue()       O(1)   remove front   (popFront on linked list)
//  q.front()         O(1)   read front without removing
//  q.back()          O(1)   read back without removing
//
//  UTILITY
//  q.clear()         O(n)   remove all nodes
//
//  STATE
//  q.isEmpty()       O(1)
//  q.getSize()       O(1)
//
//  DISPLAY
//  q.print()         O(n)   front → [ 10 | 20 | 30 ] ← back
//
//  INTERNAL MAPPING
//  enqueue  →  pushBack  on linked list   (back_  = tail)
//  dequeue  →  popFront  on linked list   (front_ = head)
//  front()  →  front_->data
//  back()   →  back_->data
//
//  STACK vs QUEUE
//  Stack   LIFO   push/pop same end (top)
//  Queue   FIFO   enqueue back, dequeue front
// =============================================================================