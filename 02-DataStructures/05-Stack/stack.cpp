// =============================================================================
//  DATA STRUCTURES EN C++ / FASE 2
//  Topic  : Stack (LIFO)
//  Author : Yeremy Acuña Chavez
//  Repo   : https://github.com/yeremyacuna
// =============================================================================
//
//  INDEX
//  ─────────────────────────────────────────────────────────────────────────
//  [CLASS 1]  Node<T>         / same node as LinkedList
//  [CLASS 2]  Stack<T>
//
//  [SECTION 1] Constructor & Destructor
//              - Stack()                    O(1)
//              - ~Stack()                   O(n)
//
//  [SECTION 2] Core Operations
//              - push(T value)              O(1)
//              - pop()                      O(1)
//              - peek()                     O(1)
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
//  WHAT IS A STACK?
//  ─────────────────────────────────────────────────────────────────────────
//  LIFO / Last In, First Out.
//  The last element pushed is the first one popped.
//  Only the TOP is ever accessible / no middle, no bottom.
//
//  MEMORY MODEL (built on top of a linked list)
//  ─────────────────────────────────────────────────────────────────────────
//  top
//   ↓
//  [30] >>> [20] >>> [10] >>> nullptr
//
//  top   = head of the internal linked list
//  push  = pushFront  (new node becomes the new head)
//  pop   = popFront   (head node is removed)
//  peek  = head->data (just read, don't remove)
//
//  WHY linked list and not array?
//  ─────────────────────────────────────────────────────────────────────────
//  Linked list grows on demand / no fixed capacity, no resize needed.
//  push and pop are always O(1) with no exceptions.
//
//  REAL WORLD USES
//  ─────────────────────────────────────────────────────────────────────────
//  - Undo / Redo  in any editor
//  - Browser back button  (stack of visited URLs)
//  - Function call stack  (the CPU uses this literally)
//  - Balanced brackets checker  ({ [ ( ) ] })
//  - Expression evaluation  (compilers)
//
//  Compile: g++ -std=c++17 -Wall -Wextra -o fase_02_stack fase_02_stack.cpp
//  Run    : ./fase_02_stack
// =============================================================================

#include <iostream>

using namespace std;


// =============================================================================
//  CLASS 1 / Node<T>
//  Exact same node as LinkedList / data + next pointer.
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
//  CLASS 2 / Stack<T>
//
//  top_   : pointer to the top node (head of the internal linked list)
//  size_  : number of elements currently in the stack
//
//  The Stack does NOT expose insert/remove by index, search, or sort.
//  It intentionally restricts access to TOP only / that is the entire point.
// =============================================================================

template <typename T>
class Stack {

private:

    Node<T>* top_;
    int      size_;


public:

    // =========================================================================
    //  [SECTION 1] CONSTRUCTOR & DESTRUCTOR
    // =========================================================================

    // -------------------------------------------------------------------------
    //  Constructor / empty stack                                     O(1)
    // -------------------------------------------------------------------------
    Stack() {
        top_ = nullptr;
        size_ = 0;
    }

    // -------------------------------------------------------------------------
    //  Destructor / walks and deletes every node                     O(n)
    //  Identical logic to LinkedList destructor / save next, delete current.
    // -------------------------------------------------------------------------
    ~Stack() {
        Node<T>* current = top_;
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
    //  push / adds a new element on top                              O(1)
    //
    //  Before: top >>> [20] >>> [10] >>> nullptr
    //  push(30)
    //  After : top >>> [30] >>> [20] >>> [10] >>> nullptr
    //
    //  Exactly the same as pushFront() in LinkedList:
    //    1. create newNode
    //    2. newNode->next = top_   (new node points to old top)
    //    3. top_ = newNode         (top moves to new node)
    // -------------------------------------------------------------------------
    void push(T value) {
        Node<T>* newNode = new Node<T>(value);
        //                 └─ creates node on heap, next = nullptr

        newNode->next = top_;
        // └─ new node points to whoever was on top before
        //    if stack was empty, top_ was nullptr / newNode->next = nullptr ✓

        top_ = newNode;
        // └─ top now points to the new node

        size_++;
    }

    // -------------------------------------------------------------------------
    //  pop / removes the top element                                 O(1)
    //
    //  Before: top >>> [30] >>> [20] >>> [10] >>> nullptr
    //  pop()
    //  After : top >>> [20] >>> [10] >>> nullptr
    //
    //  Steps:
    //    1. save top_ in toDelete
    //    2. advance top_ to top_->next
    //    3. delete toDelete
    // -------------------------------------------------------------------------
    void pop() {
        if (isEmpty()) {
            cout << "[Stack] pop() / stack is empty\n";
            return;
        }

        Node<T>* toDelete = top_;
        // └─ save current top before moving the pointer
        //    if we moved top_ first, we'd lose the reference to delete

        top_ = top_->next;
        // └─ top now points to the node that was second from the top

        delete toDelete;
        // └─ free the old top node from heap

        size_--;
    }

    // -------------------------------------------------------------------------
    //  peek / returns the top value WITHOUT removing it              O(1)
    //
    //  This is the "look but don't touch" operation.
    //  top_ pointer does NOT move / we just read top_->data.
    // -------------------------------------------------------------------------
    T peek() const {
        if (isEmpty()) {
            cout << "[Stack] peek() / stack is empty\n";
            return T{};
        }
        return top_->data;
        // └─ just read the value / top_ stays pointing to the same node
    }


    // =========================================================================
    //  [SECTION 3] UTILITY
    // =========================================================================

    // -------------------------------------------------------------------------
    //  clear / removes all nodes                                     O(n)
    // -------------------------------------------------------------------------
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


    // =========================================================================
    //  [SECTION 4] STATE QUERIES
    // =========================================================================

    bool isEmpty()  const { return size_ == 0; }
    int  getSize()  const { return size_; }


    // =========================================================================
    //  [SECTION 5] DISPLAY
    // =========================================================================

    // O(n) / prints from top to bottom
    void print() const {
        if (isEmpty()) { cout << "[ empty ]\n"; return; }

        Node<T>* current = top_;
        cout << "top >>> [ ";
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) cout << " | ";
            current = current->next;
        }
        cout << " ] ← bottom\n";
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
    section("Creating Stack<int>");

    Stack<int> stack;
    cout << "isEmpty: " << stack.isEmpty() << "\n";   // 1


    section("push: 10, 20, 30, 40");

    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.push(40);
    stack.print();                                      // top >>> [ 40 | 30 | 20 | 10 ] ← bottom
    cout << "size : " << stack.getSize() << "\n";      // 4
    cout << "peek : " << stack.peek() << "\n";      // 40  / top not removed


    section("pop x2");

    stack.pop();
    stack.print();   // top >>> [ 30 | 20 | 10 ]
    stack.pop();
    stack.print();   // top >>> [ 20 | 10 ]


    section("clear()");

    stack.clear();
    cout << "isEmpty after clear: " << stack.isEmpty() << "\n";


    section("Error handling");

    Stack<int> empty;
    empty.pop();    // [ERROR] empty
    empty.peek();   // [ERROR] empty


    // =========================================================================
    //  REAL WORLD DEMO 1 / Balanced brackets checker
    //  { [ ( ) ] }  >>> valid
    //  { [ )       >>> invalid
    //
    //  Logic:
    //  - opening bracket ( { [  >>> push it
    //  - closing bracket ) } ]  >>> pop and check if it matches
    //  - if at the end the stack is empty >>> all brackets closed correctly
    // =========================================================================
    section("Real World Demo 1 / Balanced Brackets Checker");

    auto checkBrackets = [](const char* expr) {
        Stack<char> s;
        bool valid = true;

        for (int i = 0; expr[i] != '\0'; i++) {
            char c = expr[i];

            if (c == '(' || c == '{' || c == '[') {
                s.push(c);
                // opening bracket / push onto stack

            }
            else if (c == ')' || c == '}' || c == ']') {

                if (s.isEmpty()) { valid = false; break; }
                // closing bracket but nothing was opened / invalid

                char top = s.peek();
                s.pop();

                // check if the closing matches the last opened
                if ((c == ')' && top != '(') ||
                    (c == '}' && top != '{') ||
                    (c == ']' && top != '[')) {
                    valid = false;
                    break;
                }
            }
        }

        if (!s.isEmpty()) valid = false;
        // if stack still has items, some brackets were never closed

        cout << "\"" << expr << "\" >>> " << (valid ? "VALID" : "INVALID") << "\n";
        };

    checkBrackets("{ [ ( ) ] }");    // VALID
    checkBrackets("( ( ) )");        // VALID
    checkBrackets("{ [ )");          // INVALID / ) does not match [
    checkBrackets("( ( ( )");        // INVALID / two unclosed (
    checkBrackets("");               // VALID   / empty is valid


    // =========================================================================
    //  REAL WORLD DEMO 2 / Undo / Redo system
    //  Every action pushed to undoStack.
    //  Undo >>> pop from undoStack, push to redoStack.
    //  Redo >>> pop from redoStack, push back to undoStack.
    // =========================================================================
    section("Real World Demo 2 / Undo / Redo");

    Stack<const char*> undoStack;
    Stack<const char*> redoStack;

    // perform actions
    undoStack.push("typed 'H'");
    undoStack.push("typed 'e'");
    undoStack.push("typed 'l'");
    undoStack.push("typed 'l'");
    undoStack.push("typed 'o'");

    cout << "Current state  : "; undoStack.print();

    // undo twice
    cout << "\nUndo x2:\n";
    for (int i = 0; i < 2; i++) {
        cout << "  undone: " << undoStack.peek() << "\n";
        redoStack.push(undoStack.peek());
        undoStack.pop();
    }
    cout << "After undo     : "; undoStack.print();
    cout << "Redo available : "; redoStack.print();

    // redo once
    cout << "\nRedo x1:\n";
    cout << "  redone: " << redoStack.peek() << "\n";
    undoStack.push(redoStack.peek());
    redoStack.pop();
    cout << "After redo     : "; undoStack.print();


    // =========================================================================
    //  Works with other types
    // =========================================================================
    section("Stack<double>");

    Stack<double> sd;
    sd.push(1.1); sd.push(2.2); sd.push(3.3);
    sd.print();
    cout << "peek: " << sd.peek() << "\n";


    // =========================================================================
    //  END
    // =========================================================================
    cout << "\n============================================================\n";
    cout << "  Phase 2 / Stack<T> complete\n";
    cout << "============================================================\n\n";

    return 0;
}


// =============================================================================
//  CHEAT SHEET / Stack<T> quick reference
// =============================================================================
//
//  CONSTRUCTION
//  Stack<T> s;              empty stack
//  ~Stack()                 auto-called, frees all nodes
//
//  CORE              Complexity
//  s.push(val)       O(1)   add on top
//  s.pop()           O(1)   remove top
//  s.peek()          O(1)   read top without removing
//
//  UTILITY
//  s.clear()         O(n)   remove all nodes
//
//  STATE
//  s.isEmpty()       O(1)
//  s.getSize()       O(1)
//
//  DISPLAY
//  s.print()         O(n)   top >>> [ 30 | 20 | 10 ] ← bottom
//
//  INTERNAL MAPPING
//  push  >>>  pushFront on linked list
//  pop   >>>  popFront  on linked list
//  peek  >>>  head->data
// =============================================================================