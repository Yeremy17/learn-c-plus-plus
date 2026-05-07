// =============================================================================
//  DATA STRUCTURES EN C++ / FASE 1
//  Topic  : Static Array
//  Author : Yeremy Acuña Chavez
//  Repo   : https://github.com/yeremyacuna
// =============================================================================
//
//  INDEX
//  ─────────────────────────────────────────────────────────────────────────
//  [CLASS]    StaticArray<T>
//
//  [SECTION 1] Constructor & Destructor
//              - StaticArray(int capacity)       O(1)
//              - ~StaticArray()                  O(1)
//
//  [SECTION 2] Core Access
//              - get(int index)                  O(1)
//              - set(int index, T value)         O(1)
//              - front()                         O(1)
//              - back()                          O(1)
//
//  [SECTION 3] Insertion & Deletion
//              - pushBack(T value)               O(1)
//              - popBack()                       O(1)
//              - insert(int index, T value)      O(n)
//              - remove(int index)               O(n)
//
//  [SECTION 4] Search
//              - search(T value)                 O(n)
//              - contains(T value)               O(n)
//              - count(T value)                  O(n)
//
//  [SECTION 5] Sorting
//              - bubbleSort()                    O(n²)
//              - selectionSort()                 O(n²)
//              - insertionSort()                 O(n²)
//
//  [SECTION 6] Utility
//              - swap(int i, int j)              O(1)
//              - reverse()                       O(n)
//              - fill(T value)                   O(n)
//              - clear()                         O(n)
//              - min()                           O(n)
//              - max()                           O(n)
//
//  [SECTION 7] State Queries
//              - isEmpty()                       O(1)
//              - isFull()                        O(1)
//              - getSize()                       O(1)
//              - getCapacity()                   O(1)
//
//  [SECTION 8] Display
//              - print()                         O(n)
//              - printInfo()                     O(1)
//  ─────────────────────────────────────────────────────────────────────────
//
//  MEMORY MODEL
//  ─────────────────────────────────────────────────────────────────────────
//  capacity = 6  (total slots reserved in heap)
//  size     = 4  (slots currently holding data)
//
//  index  [0]  [1]  [2]  [3]  [4]  [5]
//  value  10   20   30   40    --   --
//          ↑                    ↑
//       data_[0]            data_[size] = next free slot
//
//  Compile: g++ -std=c++17 -Wall -Wextra -o fase_01 fase_01_static_array.cpp
//  Run    : ./fase_01
// =============================================================================

#include <iostream>

using namespace std;


// =============================================================================
//  CLASS / StaticArray<T>
// =============================================================================
//
//  T        : template parameter / works with int, double, char, etc.
//  data_    : raw pointer to the heap block (our internal array)
//  size_    : how many elements are currently stored
//  capacity_: how many slots were reserved at construction
//
//  Naming convention: trailing underscore (_) marks private member variables.
//  This avoids name collisions with parameters (e.g. size vs size_).
//
// =============================================================================

template <typename T>
class StaticArray {

private:

    T* data_;       // pointer to the heap-allocated block of T elements
    int size_;       // number of elements currently stored
    int capacity_;   // total slots available (fixed at construction)

    // -------------------------------------------------------------------------
    //  PRIVATE HELPER / isValidIndex
    //  Checks whether an index falls within the used range [0, size_-1].
    //  Used internally before any get / set / insert / remove operation.
    //  Complexity: O(1)
    // -------------------------------------------------------------------------
    bool isValidIndex(int index) const {
        return (index >= 0 && index < size_);
        // index >= 0      : no negative indices
        // index < size_   : no access beyond the last stored element
    }


public:

    // =========================================================================
    //  [SECTION 1] CONSTRUCTOR & DESTRUCTOR
    // =========================================================================

    // -------------------------------------------------------------------------
    //  Constructor
    //  Reserves a contiguous block of 'capacity' elements in the heap.
    //  size_ starts at 0 because no data has been stored yet.
    //  Complexity: O(1)
    // -------------------------------------------------------------------------
    StaticArray(int capacity) {
        capacity_ = capacity;           // store the fixed capacity
        size_ = 0;                  // array starts empty
        data_ = new T[capacity_];   // allocate block on heap
        //           └─ new T[n] : reserves n contiguous slots of type T
        //                         returns pointer to the first slot
    }

    // -------------------------------------------------------------------------
    //  Destructor
    //  Called automatically when the object goes out of scope.
    //  Releases the heap block to avoid memory leaks.
    //  Complexity: O(1)
    // -------------------------------------------------------------------------
    ~StaticArray() {
        delete[] data_;   // free the entire heap block
        data_ = nullptr;  // safety: nullify dangling pointer
    }


    // =========================================================================
    //  [SECTION 2] CORE ACCESS
    // =========================================================================

    // -------------------------------------------------------------------------
    //  get / returns the element at position 'index'
    //  Direct address calculation: data_[index] → base + index * sizeof(T)
    //  Complexity: O(1)
    // -------------------------------------------------------------------------
    T get(int index) const {
        if (!isValidIndex(index)) {
            // index out of range / report and return a zero-initialized T
            cout << "[ERROR] get(" << index << ") / index out of range. "
                << "Valid range: [0, " << size_ - 1 << "]\n";
            return T{};   // T{} : zero-initializes any type (0, 0.0, '\0', etc.)
        }
        return data_[index];
        // data_[index]  is identical to  *(data_ + index)
        // the CPU computes the address in one step / no loop needed
    }

    // -------------------------------------------------------------------------
    //  set / overwrites the element at position 'index' with 'value'
    //  Complexity: O(1)
    // -------------------------------------------------------------------------
    void set(int index, T value) {
        if (!isValidIndex(index)) {
            cout << "[ERROR] set(" << index << ") / index out of range. "
                << "Valid range: [0, " << size_ - 1 << "]\n";
            return;
        }
        data_[index] = value;   // direct overwrite at the computed address
    }

    // -------------------------------------------------------------------------
    //  front / returns the first stored element (index 0)
    //  Complexity: O(1)
    // -------------------------------------------------------------------------
    T front() const {
        if (size_ == 0) {
            cout << "[ERROR] front() / array is empty\n";
            return T{};
        }
        return data_[0];
    }

    // -------------------------------------------------------------------------
    //  back / returns the last stored element (index size_-1)
    //  Complexity: O(1)
    // -------------------------------------------------------------------------
    T back() const {
        if (size_ == 0) {
            cout << "[ERROR] back() / array is empty\n";
            return T{};
        }
        return data_[size_ - 1];
        // size_ - 1 is always the index of the last element
    }


    // =========================================================================
    //  [SECTION 3] INSERTION & DELETION
    // =========================================================================

    // -------------------------------------------------------------------------
    //  pushBack / appends 'value' at the end (next free slot)
    //
    //  Before:  [10, 20, 30, --]    size=3  capacity=4
    //  After :  [10, 20, 30, 40]    size=4  capacity=4
    //
    //  Complexity: O(1) / just write at data_[size_] and increment size_
    // -------------------------------------------------------------------------
    void pushBack(T value) {
        if (isFull()) {
            cout << "[ERROR] pushBack() / array is full (capacity=" << capacity_ << ")\n";
            return;
        }
        data_[size_] = value;   // write at the first free slot
        size_++;                // one more element is now stored
    }

    // -------------------------------------------------------------------------
    //  popBack / removes the last element
    //
    //  Before:  [10, 20, 30, 40]    size=4
    //  After :  [10, 20, 30, --]    size=3
    //
    //  We don't actually erase the data from memory / we just decrement size_
    //  so the slot is treated as "free" and will be overwritten next pushBack.
    //  Complexity: O(1)
    // -------------------------------------------------------------------------
    void popBack() {
        if (isEmpty()) {
            cout << "[ERROR] popBack() / array is empty\n";
            return;
        }
        size_--;   // logically removes the last element (data stays in memory but ignored)
    }

    // -------------------------------------------------------------------------
    //  insert / inserts 'value' at position 'index', shifting right
    //
    //  insert(1, 99):
    //  Before:  [10, 20, 30, 40, --]    size=4
    //           shift right from index 1:
    //           [10, 20, 20, 30, 40]    (copies propagate right)
    //           write at index 1:
    //  After :  [10, 99, 20, 30, 40]    size=5
    //
    //  Complexity: O(n) / up to n elements must shift right
    // -------------------------------------------------------------------------
    void insert(int index, T value) {
        if (isFull()) {
            cout << "[ERROR] insert() / array is full\n";
            return;
        }
        if (index < 0 || index > size_) {
            // index == size_ is valid: same as pushBack
            cout << "[ERROR] insert(" << index << ") / index out of range. "
                << "Valid range: [0, " << size_ << "]\n";
            return;
        }

        // Shift every element from the last down to 'index' one position to the right
        // We iterate BACKWARDS to avoid overwriting data we still need
        for (int i = size_; i > index; i--) {
            data_[i] = data_[i - 1];
            // i starts at size_ (first free slot) and moves left
            // each element copies itself one position forward
        }

        data_[index] = value;   // place the new value in the freed slot
        size_++;
    }

    // -------------------------------------------------------------------------
    //  remove / removes the element at 'index', shifting left
    //
    //  remove(1):
    //  Before:  [10, 20, 30, 40]    size=4
    //           shift left from index 2:
    //  After :  [10, 30, 40, --]    size=3
    //
    //  Complexity: O(n) / up to n elements must shift left
    // -------------------------------------------------------------------------
    void remove(int index) {
        if (!isValidIndex(index)) {
            cout << "[ERROR] remove(" << index << ") / index out of range. "
                << "Valid range: [0, " << size_ - 1 << "]\n";
            return;
        }

        // Shift every element from index+1 to the end one position to the left
        for (int i = index; i < size_ - 1; i++) {
            data_[i] = data_[i + 1];
            // each element overwrites the one before it
        }

        size_--;   // one less element stored
    }


    // =========================================================================
    //  [SECTION 4] SEARCH
    // =========================================================================

    // -------------------------------------------------------------------------
    //  search / linear search, returns the index of the first match
    //  Returns -1 if the value is not found.
    //  Complexity: O(n)
    // -------------------------------------------------------------------------
    int search(T value) const {
        for (int i = 0; i < size_; i++) {
            if (data_[i] == value) {
                return i;   // found / return position immediately
            }
        }
        return -1;   // not found
    }

    // -------------------------------------------------------------------------
    //  contains / returns true if 'value' exists in the array
    //  Internally calls search() and checks if result != -1
    //  Complexity: O(n)
    // -------------------------------------------------------------------------
    bool contains(T value) const {
        return search(value) != -1;
    }

    // -------------------------------------------------------------------------
    //  count / counts how many times 'value' appears in the array
    //  Complexity: O(n)
    // -------------------------------------------------------------------------
    int count(T value) const {
        int occurrences = 0;
        for (int i = 0; i < size_; i++) {
            if (data_[i] == value) {
                occurrences++;
            }
        }
        return occurrences;
    }


    // =========================================================================
    //  [SECTION 5] SORTING
    // =========================================================================

    // -------------------------------------------------------------------------
    //  bubbleSort / repeatedly swaps adjacent elements that are out of order
    //
    //  Each full pass "bubbles" the largest unsorted element to the end.
    //  After k passes, the last k elements are in their final position.
    //
    //  Pass 1: [30,10,20,50,40] → [10,20,30,40,50]  (50 bubbled to end)
    //  Pass 2: [10,20,30,40,50] → already sorted
    //
    //  Best case : O(n)   / already sorted (optimized with 'swapped' flag)
    //  Average   : O(n²)
    //  Worst case: O(n²)
    // -------------------------------------------------------------------------
    void bubbleSort() {
        bool swapped;

        for (int i = 0; i < size_ - 1; i++) {
            // After each pass, the element at position (size_-1-i) is final
            swapped = false;

            for (int j = 0; j < size_ - 1 - i; j++) {
                if (data_[j] > data_[j + 1]) {
                    // adjacent elements are out of order / swap them
                    T temp = data_[j];
                    data_[j] = data_[j + 1];
                    data_[j + 1] = temp;
                    swapped = true;
                }
            }

            if (!swapped) break;
            // if no swap happened in this pass, array is already sorted / early exit
        }
    }

    // -------------------------------------------------------------------------
    //  selectionSort / finds the minimum of the unsorted portion and places it
    //
    //  Divides array into: [sorted | unsorted]
    //  Each pass selects the minimum from the unsorted portion and swaps it
    //  to the boundary position.
    //
    //  Pass 1: [30,10,20,50,40] → min=10 at index 1 → swap(0,1) → [10,30,20,50,40]
    //  Pass 2: [10,|30,20,50,40] → min=20 at index 2 → swap(1,2) → [10,20,30,50,40]
    //
    //  Always O(n²) / no early exit possible (must always find the minimum)
    // -------------------------------------------------------------------------
    void selectionSort() {
        for (int i = 0; i < size_ - 1; i++) {
            int minIndex = i;   // assume current position holds the minimum

            // search the rest of the array for a smaller element
            for (int j = i + 1; j < size_; j++) {
                if (data_[j] < data_[minIndex]) {
                    minIndex = j;   // found a new minimum
                }
            }

            // place the minimum at position i (only swap if needed)
            if (minIndex != i) {
                T temp = data_[i];
                data_[i] = data_[minIndex];
                data_[minIndex] = temp;
            }
        }
    }

    // -------------------------------------------------------------------------
    //  insertionSort / builds sorted portion one element at a time
    //
    //  Takes each element from the unsorted portion and inserts it at the
    //  correct position within the already-sorted portion (by shifting right).
    //
    //  Step 1: [30,|10,20,50,40] → insert 10 → [10,30,|20,50,40]
    //  Step 2: [10,30,|20,50,40] → insert 20 → [10,20,30,|50,40]
    //
    //  Best case : O(n)  / already sorted (no shifts needed)
    //  Worst case: O(n²) / reverse sorted (max shifts every step)
    // -------------------------------------------------------------------------
    void insertionSort() {
        for (int i = 1; i < size_; i++) {
            T   key = data_[i];   // element to be inserted into sorted portion
            int j = i - 1;      // last index of sorted portion

            // shift sorted elements right until we find the correct slot for key
            while (j >= 0 && data_[j] > key) {
                data_[j + 1] = data_[j];   // shift right
                j--;
            }

            data_[j + 1] = key;   // insert key in its correct position
        }
    }


    // =========================================================================
    //  [SECTION 6] UTILITY
    // =========================================================================

    // -------------------------------------------------------------------------
    //  swap / exchanges the elements at positions i and j
    //  Uses a temporary variable (the classic 3-step swap)
    //  Complexity: O(1)
    // -------------------------------------------------------------------------
    void swap(int i, int j) {
        if (!isValidIndex(i) || !isValidIndex(j)) {
            cout << "[ERROR] swap() / one or both indices are out of range\n";
            return;
        }
        T temp = data_[i];
        data_[i] = data_[j];
        data_[j] = temp;
        // classic 3-step swap: save i → overwrite i with j → restore j from temp
    }

    // -------------------------------------------------------------------------
    //  reverse / reverses the order of all stored elements in-place
    //
    //  [10, 20, 30, 40, 50]  →  [50, 40, 30, 20, 10]
    //
    //  Uses two pointers: left starts at 0, right at size_-1
    //  They walk toward each other, swapping pairs until they meet.
    //  Complexity: O(n)
    // -------------------------------------------------------------------------
    void reverse() {
        int left = 0;
        int right = size_ - 1;

        while (left < right) {
            T temp = data_[left];
            data_[left] = data_[right];
            data_[right] = temp;
            left++;
            right--;
        }
    }

    // -------------------------------------------------------------------------
    //  fill / sets every stored element to 'value'
    //  Does not change size_ or capacity_, only overwrites current elements.
    //  Complexity: O(n)
    // -------------------------------------------------------------------------
    void fill(T value) {
        for (int i = 0; i < size_; i++) {
            data_[i] = value;
        }
    }

    // -------------------------------------------------------------------------
    //  clear / logically empties the array by resetting size_ to 0
    //  The heap block is NOT freed / capacity_ remains unchanged.
    //  Data is still in memory but treated as non-existent (size_=0 guards it).
    //  Complexity: O(1)  (O(n) if you want to zero-out the data too)
    // -------------------------------------------------------------------------
    void clear() {
        size_ = 0;
        // we do NOT delete[] data_ here / the array stays allocated and reusable
    }

    // -------------------------------------------------------------------------
    //  min / returns the smallest element in the array
    //  Complexity: O(n)
    // -------------------------------------------------------------------------
    T min() const {
        if (isEmpty()) {
            cout << "[ERROR] min() / array is empty\n";
            return T{};
        }
        T minimum = data_[0];
        for (int i = 1; i < size_; i++) {
            if (data_[i] < minimum) {
                minimum = data_[i];
            }
        }
        return minimum;
    }

    // -------------------------------------------------------------------------
    //  max / returns the largest element in the array
    //  Complexity: O(n)
    // -------------------------------------------------------------------------
    T max() const {
        if (isEmpty()) {
            cout << "[ERROR] max() / array is empty\n";
            return T{};
        }
        T maximum = data_[0];
        for (int i = 1; i < size_; i++) {
            if (data_[i] > maximum) {
                maximum = data_[i];
            }
        }
        return maximum;
    }


    // =========================================================================
    //  [SECTION 7] STATE QUERIES
    // =========================================================================

    // -------------------------------------------------------------------------
    //  isEmpty / true if no elements are stored (size_ == 0)
    //  Complexity: O(1)
    // -------------------------------------------------------------------------
    bool isEmpty() const {
        return size_ == 0;
    }

    // -------------------------------------------------------------------------
    //  isFull / true if all slots are used (size_ == capacity_)
    //  Complexity: O(1)
    // -------------------------------------------------------------------------
    bool isFull() const {
        return size_ == capacity_;
    }

    // -------------------------------------------------------------------------
    //  getSize / returns number of stored elements
    //  Complexity: O(1)
    // -------------------------------------------------------------------------
    int getSize() const {
        return size_;
    }

    // -------------------------------------------------------------------------
    //  getCapacity / returns total reserved slots
    //  Complexity: O(1)
    // -------------------------------------------------------------------------
    int getCapacity() const {
        return capacity_;
    }


    // =========================================================================
    //  [SECTION 8] DISPLAY
    // =========================================================================

    // -------------------------------------------------------------------------
    //  print / prints all stored elements in order
    //  Complexity: O(n)
    // -------------------------------------------------------------------------
    void print() const {
        if (isEmpty()) {
            cout << "[ empty ]\n";
            return;
        }
        cout << "[ ";
        for (int i = 0; i < size_; i++) {
            cout << data_[i];
            if (i < size_ - 1) cout << ", ";
        }
        cout << " ]\n";
    }

    // -------------------------------------------------------------------------
    //  printInfo / prints size, capacity, and content in one line
    //  Complexity: O(n)
    // -------------------------------------------------------------------------
    void printInfo() const {
        cout << "size=" << size_ << " | capacity=" << capacity_ << " | data=";
        print();
    }

};


// =============================================================================
//  MAIN / runs all operations with clear section labels
// =============================================================================

void section(const char* title) {
    cout << "\n============================================================\n";
    cout << "  " << title << "\n";
    cout << "============================================================\n";
}

int main() {

    // =========================================================================
    //  Build the array / capacity 8, stores ints
    // =========================================================================
    section("Creating StaticArray<int> with capacity 8");

    StaticArray<int> arr(8);
    arr.printInfo();   // size=0, capacity=8, empty


    // =========================================================================
    //  pushBack / insert at end
    // =========================================================================
    section("pushBack: 10, 20, 30, 40, 50");

    arr.pushBack(10);
    arr.pushBack(20);
    arr.pushBack(30);
    arr.pushBack(40);
    arr.pushBack(50);
    arr.printInfo();   // [10, 20, 30, 40, 50]


    // =========================================================================
    //  get / set / front / back
    // =========================================================================
    section("get / set / front / back");

    cout << "get(2)   : " << arr.get(2) << "\n";   // 30
    cout << "front()  : " << arr.front() << "\n";   // 10
    cout << "back()   : " << arr.back() << "\n";   // 50

    arr.set(2, 99);
    cout << "after set(2, 99): ";
    arr.print();   // [10, 20, 99, 40, 50]

    arr.set(2, 30);   // restore


    // =========================================================================
    //  insert / remove
    // =========================================================================
    section("insert(1, 15) / shifts right");

    arr.insert(1, 15);
    arr.printInfo();   // [10, 15, 20, 30, 40, 50]

    section("remove(1) / shifts left");

    arr.remove(1);
    arr.printInfo();   // [10, 20, 30, 40, 50]

    section("popBack()");

    arr.popBack();
    arr.printInfo();   // [10, 20, 30, 40]


    // =========================================================================
    //  search / contains / count
    // =========================================================================
    section("search / contains / count");

    arr.pushBack(20);   // [10, 20, 30, 40, 20]

    cout << "search(20)   : index " << arr.search(20) << "\n";   // 1
    cout << "search(99)   : index " << arr.search(99) << "\n";   // -1
    cout << "contains(30) : " << arr.contains(30) << "\n";          // 1
    cout << "contains(99) : " << arr.contains(99) << "\n";          // 0
    cout << "count(20)    : " << arr.count(20) << "\n";           // 2


    // =========================================================================
    //  min / max
    // =========================================================================
    section("min / max");

    cout << "min() : " << arr.min() << "\n";   // 10
    cout << "max() : " << arr.max() << "\n";   // 40


    // =========================================================================
    //  swap / reverse
    // =========================================================================
    section("swap(0, 3)");

    arr.swap(0, 3);
    arr.print();   // [40, 20, 30, 10, 20]

    section("reverse()");

    arr.reverse();
    arr.print();   // [20, 10, 30, 20, 40]


    // =========================================================================
    //  Sorting
    // =========================================================================
    section("bubbleSort()");

    StaticArray<int> b(6);
    b.pushBack(50); b.pushBack(10); b.pushBack(40);
    b.pushBack(20); b.pushBack(30); b.pushBack(60);
    cout << "before: "; b.print();
    b.bubbleSort();
    cout << "after : "; b.print();   // [10, 20, 30, 40, 50, 60]

    section("selectionSort()");

    StaticArray<int> s(6);
    s.pushBack(50); s.pushBack(10); s.pushBack(40);
    s.pushBack(20); s.pushBack(30); s.pushBack(60);
    cout << "before: "; s.print();
    s.selectionSort();
    cout << "after : "; s.print();   // [10, 20, 30, 40, 50, 60]

    section("insertionSort()");

    StaticArray<int> ins(6);
    ins.pushBack(50); ins.pushBack(10); ins.pushBack(40);
    ins.pushBack(20); ins.pushBack(30); ins.pushBack(60);
    cout << "before: "; ins.print();
    ins.insertionSort();
    cout << "after : "; ins.print();   // [10, 20, 30, 40, 50, 60]


    // =========================================================================
    //  fill / clear
    // =========================================================================
    section("fill(7)");

    StaticArray<int> f(4);
    f.pushBack(1); f.pushBack(2); f.pushBack(3); f.pushBack(4);
    cout << "before: "; f.print();
    f.fill(7);
    cout << "after : "; f.print();   // [7, 7, 7, 7]

    section("clear()");

    f.clear();
    f.printInfo();   // size=0, capacity=4, empty


    // =========================================================================
    //  Error handling / out of range
    // =========================================================================
    section("Error handling");

    StaticArray<int> e(2);
    e.pushBack(1);
    e.pushBack(2);
    e.get(5);        // [ERROR] out of range
    e.pushBack(99);  // [ERROR] full
    e.remove(10);    // [ERROR] out of range


    // =========================================================================
    //  Works with other types / double
    // =========================================================================
    section("StaticArray<double>");

    StaticArray<double> d(4);
    d.pushBack(1.1);
    d.pushBack(2.2);
    d.pushBack(3.3);
    d.print();   // [1.1, 2.2, 3.3]
    cout << "min: " << d.min() << " | max: " << d.max() << "\n";


    // =========================================================================
    //  Works with char
    // =========================================================================
    section("StaticArray<char>");

    StaticArray<char> c(5);
    c.pushBack('h');
    c.pushBack('e');
    c.pushBack('l');
    c.pushBack('l');
    c.pushBack('o');
    c.print();   // [h, e, l, l, o]


    // =========================================================================
    //  END
    // =========================================================================
    cout << "\n============================================================\n";
    cout << "  Phase 1 complete / StaticArray<T> ready\n";
    cout << "============================================================\n\n";

    // All StaticArray destructors run here automatically:
    // each ~StaticArray() calls delete[] data_ / no memory leaks.

    return 0;
}


// =============================================================================
//  CHEAT SHEET / StaticArray<T> quick reference
// =============================================================================
//
//  CONSTRUCTION
//  StaticArray<int> arr(capacity);     build with fixed capacity
//  ~StaticArray()                      auto-called, frees heap block
//
//  CORE ACCESS          Complexity
//  arr.get(i)           O(1)   value at index i
//  arr.set(i, val)      O(1)   overwrite at index i
//  arr.front()          O(1)   first element
//  arr.back()           O(1)   last element
//
//  INSERT / DELETE
//  arr.pushBack(val)    O(1)   append at end
//  arr.popBack()        O(1)   remove last
//  arr.insert(i, val)  O(n)   insert at i, shift right
//  arr.remove(i)        O(n)   remove at i, shift left
//
//  SEARCH
//  arr.search(val)      O(n)   first index of val, or -1
//  arr.contains(val)    O(n)   true / false
//  arr.count(val)       O(n)   number of occurrences
//
//  SORTING
//  arr.bubbleSort()     O(n²)  stable, early exit
//  arr.selectionSort()  O(n²)  always n² comparisons
//  arr.insertionSort()  O(n²)  best O(n) if nearly sorted
//
//  UTILITY
//  arr.swap(i, j)       O(1)   exchange two elements
//  arr.reverse()        O(n)   in-place reversal
//  arr.fill(val)        O(n)   set all elements to val
//  arr.clear()          O(1)   reset size to 0
//  arr.min()            O(n)   smallest element
//  arr.max()            O(n)   largest element
//
//  STATE
//  arr.isEmpty()        O(1)   true if size == 0
//  arr.isFull()         O(1)   true if size == capacity
//  arr.getSize()        O(1)   current element count
//  arr.getCapacity()    O(1)   total reserved slots
//
//  DISPLAY
//  arr.print()          O(n)   prints [ e0, e1, ... ]
//  arr.printInfo()      O(n)   prints size, capacity, data
//
// =============================================================================