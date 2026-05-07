// =============================================================================
//  DATA STRUCTURES EN C++ / FASE 1
//  Topic  : Dynamic Array
//  Author : Yeremy Acuña Chavez
//  Repo   : https://github.com/yeremyacuna
// =============================================================================
//
//  INDEX
//  ─────────────────────────────────────────────────────────────────────────
//  [CLASS]    DynamicArray<T>
//
//  [SECTION 1] Constructor & Destructor
//              - DynamicArray(int initialCapacity = 4)    O(1)
//              - ~DynamicArray()                          O(1)
//
//  [SECTION 2] Private / Core Engine
//              - resize(int newCapacity)                  O(n)
//
//  [SECTION 3] Core Access
//              - get(int index)                           O(1)
//              - set(int index, T value)                  O(1)
//              - front()                                  O(1)
//              - back()                                   O(1)
//
//  [SECTION 4] Insertion & Deletion
//              - pushBack(T value)                        O(1) amortized
//              - popBack()                                O(1)
//              - insert(int index, T value)               O(n)
//              - remove(int index)                        O(n)
//
//  [SECTION 5] Search
//              - search(T value)                          O(n)
//              - contains(T value)                        O(n)
//              - count(T value)                           O(n)
//
//  [SECTION 6] Sorting
//              - bubbleSort()                             O(n²)
//              - selectionSort()                          O(n²)
//              - insertionSort()                          O(n²)
//
//  [SECTION 7] Utility
//              - swap(int i, int j)                       O(1)
//              - reverse()                                O(n)
//              - fill(T value)                            O(n)
//              - clear()                                  O(1)
//              - shrinkToFit()                            O(n)
//              - min()                                    O(n)
//              - max()                                    O(n)
//
//  [SECTION 8] State Queries
//              - isEmpty()                                O(1)
//              - getSize()                                O(1)
//              - getCapacity()                            O(1)
//
//  [SECTION 9] Display
//              - print()                                  O(n)
//              - printInfo()                              O(n)
//  ─────────────────────────────────────────────────────────────────────────
//
//  KEY DIFFERENCE vs StaticArray
//  ─────────────────────────────────────────────────────────────────────────
//  StaticArray : capacity is FIXED at construction / isFull() blocks inserts
//  DynamicArray: capacity GROWS automatically / resize() doubles it when full
//
//  MEMORY MODEL during resize
//  ─────────────────────────────────────────────────────────────────────────
//  Before pushBack(50) / full:
//    data_ → [ 10 | 20 | 30 | 40 ]    capacity=4  size=4
//
//  resize(8) creates new block, copies, frees old:
//    data_ → [ 10 | 20 | 30 | 40 | -- | -- | -- | -- ]  capacity=8  size=4
//
//  pushBack(50) writes at data_[size_]:
//    data_ → [ 10 | 20 | 30 | 40 | 50 | -- | -- | -- ]  capacity=8  size=5
//
//  WHY DOUBLING and not +1 each time?
//  ─────────────────────────────────────────────────────────────────────────
//  +1 each time → resize runs on every single pushBack → O(n²) total
//  ×2 each time → resize runs only log₂(n) times → O(1) amortized per push
//
//  Compile: g++ -std=c++17 -Wall -Wextra -o fase_01_dynamic fase_01_dynamic_array.cpp
//  Run    : ./fase_01_dynamic
// =============================================================================

#include <iostream>

using namespace std;


// =============================================================================
//  CLASS / DynamicArray<T>
// =============================================================================

template <typename T>
class DynamicArray {

private:

    T* data_;        // pointer to the current heap block
    int size_;        // elements currently stored
    int capacity_;    // total slots in the current heap block

    // -------------------------------------------------------------------------
    //  isValidIndex / guards all index-based operations              O(1)
    // -------------------------------------------------------------------------
    bool isValidIndex(int index) const {
        return (index >= 0 && index < size_);
    }

    // =========================================================================
    //  [SECTION 2] PRIVATE / CORE ENGINE
    // =========================================================================

    // -------------------------------------------------------------------------
    //  resize / replaces the internal heap block with a larger one   O(n)
    //
    //  This is the ONLY function that differs from StaticArray.
    //  Everything else (get, set, sort...) is identical / the array just
    //  never blocks an insert.
    //
    //  Steps:
    //    1. allocate a new block of 'newCapacity' slots
    //    2. copy all current elements into the new block
    //    3. free the old block
    //    4. point data_ to the new block
    //    5. update capacity_
    // -------------------------------------------------------------------------
    void resize(int newCapacity) {
        // step 1 / new block on the heap
        T* newBlock = new T[newCapacity];
        //            └─ new T[n] : reserves n contiguous slots, returns pointer to first

        // step 2 / copy every stored element into the new block
        for (int i = 0; i < size_; i++) {
            newBlock[i] = data_[i];
            // copies value by value / data_ and newBlock are two separate blocks
        }

        // step 3 / free the OLD block (it has been fully copied)
        delete[] data_;
        //        └─ without this line → memory leak (old block stays in heap forever)

        // step 4 / point data_ to the new (bigger) block
        data_ = newBlock;
        //       └─ newBlock was a local pointer / but the HEAP BLOCK it points to
        //          survives because we didn't delete it, we just moved the pointer

        // step 5 / update capacity
        capacity_ = newCapacity;

        cout << "[resize] capacity grew to " << capacity_ << "\n";
        // this line is here so you can SEE when resize fires while testing
        // remove it in production code
    }


public:

    // =========================================================================
    //  [SECTION 1] CONSTRUCTOR & DESTRUCTOR
    // =========================================================================

    // -------------------------------------------------------------------------
    //  Constructor
    //  initialCapacity has a DEFAULT VALUE of 4 / you can omit it:
    //      DynamicArray<int> arr;      → capacity starts at 4
    //      DynamicArray<int> arr(10);  → capacity starts at 10
    //  Complexity: O(1)
    // -------------------------------------------------------------------------
    explicit DynamicArray(int initialCapacity = 4)
        : data_(new T[initialCapacity]), size_(0), capacity_(initialCapacity) {
        // default of 4 is a common starting point / small enough to show
        // resize in action during tests, big enough to not resize on every push
    }

    // -------------------------------------------------------------------------
    //  Destructor / frees heap block when object goes out of scope   O(1)
    // -------------------------------------------------------------------------
    ~DynamicArray() {
        delete[] data_;
        data_ = nullptr;
    }


    // =========================================================================
    //  [SECTION 3] CORE ACCESS
    // =========================================================================

    // O(1) / direct address calculation, no loop needed
    T get(int index) const {
        if (!isValidIndex(index)) {
            cout << "[DynamicArray] get(" << index << ") out of range. "
                << "size=" << size_ << "\n";
            return T{};
        }
        return data_[index];
    }

    // O(1) / overwrites at index
    void set(int index, T value) {
        if (!isValidIndex(index)) {
            cout << "[DynamicArray] set(" << index << ") out of range. "
                << "size=" << size_ << "\n";
            return;
        }
        data_[index] = value;
    }

    // O(1) / first stored element
    T front() const {
        if (isEmpty()) { cout << "[DynamicArray] front() / empty\n"; return T{}; }
        return data_[0];
    }

    // O(1) / last stored element
    T back() const {
        if (isEmpty()) { cout << "[DynamicArray] back() / empty\n"; return T{}; }
        return data_[size_ - 1];
    }


    // =========================================================================
    //  [SECTION 4] INSERTION & DELETION
    // =========================================================================

    // -------------------------------------------------------------------------
    //  pushBack / appends value at the end
    //
    //  The key difference from StaticArray:
    //    StaticArray → blocks when full, prints error
    //    DynamicArray → calls resize(capacity_ * 2) and THEN inserts
    //
    //  Complexity: O(1) amortized
    //    / most pushBacks are O(1) (just write and increment)
    //    / occasional resize is O(n), but it happens so rarely (log₂n times
    //      total) that the average cost per push is still O(1)
    // -------------------------------------------------------------------------
    void pushBack(T value) {
        if (size_ == capacity_) {
            resize(capacity_ * 2);
            // capacity_ * 2 → doubling strategy
            // after resize, there is guaranteed room for at least one more element
        }
        data_[size_++] = value;
        // data_[size_] = value  followed by  size_++
        // post-increment: use size_ as index FIRST, then increment it
    }

    // O(1) / decrements size, logically removes last element
    void popBack() {
        if (isEmpty()) { cout << "[DynamicArray] popBack() / empty\n"; return; }
        size_--;
        // data still sits in memory but size_ guards access / it's unreachable
    }

    // -------------------------------------------------------------------------
    //  insert / inserts value at index, shifts right                 O(n)
    //  Resizes first if needed / never blocked by capacity
    // -------------------------------------------------------------------------
    void insert(int index, T value) {
        if (index < 0 || index > size_) {
            cout << "[DynamicArray] insert(" << index << ") out of range. "
                << "size=" << size_ << "\n";
            return;
        }
        if (size_ == capacity_) {
            resize(capacity_ * 2);   // grow before shifting
        }
        // shift elements right from the end down to index
        for (int i = size_; i > index; i--)
            data_[i] = data_[i - 1];
        data_[index] = value;
        size_++;
    }

    // -------------------------------------------------------------------------
    //  remove / removes element at index, shifts left                O(n)
    // -------------------------------------------------------------------------
    void remove(int index) {
        if (!isValidIndex(index)) {
            cout << "[DynamicArray] remove(" << index << ") out of range. "
                << "size=" << size_ << "\n";
            return;
        }
        for (int i = index; i < size_ - 1; i++)
            data_[i] = data_[i + 1];
        size_--;
    }


    // =========================================================================
    //  [SECTION 5] SEARCH
    // =========================================================================

    // O(n) / first index of value, -1 if not found
    int search(T value) const {
        for (int i = 0; i < size_; i++)
            if (data_[i] == value) return i;
        return -1;
    }

    // O(n) / true if value exists
    bool contains(T value) const {
        return search(value) != -1;
    }

    // O(n) / number of times value appears
    int count(T value) const {
        int n = 0;
        for (int i = 0; i < size_; i++)
            if (data_[i] == value) n++;
        return n;
    }


    // =========================================================================
    //  [SECTION 6] SORTING
    // =========================================================================

    // O(n²) avg/worst / O(n) best (early exit)
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

    // O(n²) always / minimum swaps
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

    // O(n²) worst / O(n) best / great for nearly-sorted data
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


    // =========================================================================
    //  [SECTION 7] UTILITY
    // =========================================================================

    // O(1) / classic 3-step swap between positions i and j
    void swap(int i, int j) {
        if (!isValidIndex(i) || !isValidIndex(j)) {
            cout << "[DynamicArray] swap() / index out of range\n"; return;
        }
        T tmp = data_[i]; data_[i] = data_[j]; data_[j] = tmp;
    }

    // O(n) / reverses all elements in-place using two pointers
    void reverse() {
        int left = 0, right = size_ - 1;
        while (left < right) {
            T tmp = data_[left]; data_[left] = data_[right]; data_[right] = tmp;
            left++; right--;
        }
    }

    // O(n) / sets all stored elements to value
    void fill(T value) {
        for (int i = 0; i < size_; i++)
            data_[i] = value;
    }

    // O(1) / resets size to 0, keeps heap block allocated
    void clear() { size_ = 0; }

    // -------------------------------------------------------------------------
    //  shrinkToFit / reduces capacity to exactly size_               O(n)
    //
    //  After many pushBacks + removes, capacity can be much larger than size.
    //  shrinkToFit reclaims that wasted memory.
    //
    //  Example:
    //    arr has size=3, capacity=64 (after many resizes + removes)
    //    shrinkToFit() → resize(3) → capacity=3, no wasted slots
    // -------------------------------------------------------------------------
    void shrinkToFit() {
        if (size_ == capacity_) return;    // already tight, nothing to do
        if (size_ == 0) {
            // edge case: array is empty / keep a minimum capacity of 1
            // so data_ always points to a valid (if tiny) heap block
            resize(1);
            return;
        }
        resize(size_);
        // resize to exactly size_ / no wasted slots remain
    }

    // O(n) / smallest element
    T min() const {
        if (isEmpty()) { cout << "[DynamicArray] min() / empty\n"; return T{}; }
        T m = data_[0];
        for (int i = 1; i < size_; i++)
            if (data_[i] < m) m = data_[i];
        return m;
    }

    // O(n) / largest element
    T max() const {
        if (isEmpty()) { cout << "[DynamicArray] max() / empty\n"; return T{}; }
        T m = data_[0];
        for (int i = 1; i < size_; i++)
            if (data_[i] > m) m = data_[i];
        return m;
    }


    // =========================================================================
    //  [SECTION 8] STATE QUERIES
    // =========================================================================

    // NOTE: no isFull() / a dynamic array is never permanently full
    bool isEmpty()     const { return size_ == 0; }
    int  getSize()     const { return size_; }
    int  getCapacity() const { return capacity_; }


    // =========================================================================
    //  [SECTION 9] DISPLAY
    // =========================================================================

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
        cout << "size=" << size_
            << " | capacity=" << capacity_
            << " | data=";
        print();
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
    //  Build / capacity starts at 4 (default)
    // =========================================================================
    section("Creating DynamicArray<int> / default capacity 4");

    DynamicArray<int> arr;
    // DynamicArray<int> arr(4);  / same thing, 4 is the default
    arr.printInfo();


    // =========================================================================
    //  pushBack / watch resize fire automatically
    // =========================================================================
    section("pushBack 1..8 / resize fires at 4 and 8");

    for (int i = 1; i <= 8; i++) {
        arr.pushBack(i * 10);
        arr.printInfo();
    }
    // resize fires at size=4  (4 → 8)
    // resize fires at size=8  (8 → 16)
    // every other push is pure O(1)


    // =========================================================================
    //  get / set / front / back
    // =========================================================================
    section("get / set / front / back");

    cout << "get(2)  : " << arr.get(2) << "\n";   // 30
    cout << "front() : " << arr.front() << "\n";   // 10
    cout << "back()  : " << arr.back() << "\n";   // 80

    arr.set(0, 99);
    cout << "after set(0, 99): ";
    arr.print();
    arr.set(0, 10);   // restore


    // =========================================================================
    //  insert / remove / popBack
    // =========================================================================
    section("insert(2, 25) / shifts right");

    arr.insert(2, 25);
    arr.print();   // [10, 20, 25, 30, 40, 50, 60, 70, 80]

    section("remove(2) / shifts left");

    arr.remove(2);
    arr.print();   // [10, 20, 30, 40, 50, 60, 70, 80]

    section("popBack()");

    arr.popBack();
    arr.printInfo();   // [10, 20, 30, 40, 50, 60, 70]


    // =========================================================================
    //  search / contains / count
    // =========================================================================
    section("search / contains / count");

    arr.pushBack(30);   // [10, 20, 30, 40, 50, 60, 70, 30]

    cout << "search(30)   : index " << arr.search(30) << "\n";   // 2
    cout << "search(99)   : index " << arr.search(99) << "\n";   // -1
    cout << "contains(50) : " << arr.contains(50) << "\n";          // 1
    cout << "count(30)    : " << arr.count(30) << "\n";           // 2


    // =========================================================================
    //  min / max
    // =========================================================================
    section("min / max");

    cout << "min() : " << arr.min() << "\n";   // 10
    cout << "max() : " << arr.max() << "\n";   // 70


    // =========================================================================
    //  swap / reverse
    // =========================================================================
    section("swap(0, 3)");

    arr.swap(0, 3);
    arr.print();

    section("reverse()");

    arr.reverse();
    arr.print();


    // =========================================================================
    //  Sorting
    // =========================================================================
    section("bubbleSort()");

    DynamicArray<int> b;
    b.pushBack(50); b.pushBack(10); b.pushBack(40);
    b.pushBack(20); b.pushBack(30);
    cout << "before: "; b.print();
    b.bubbleSort();
    cout << "after : "; b.print();

    section("selectionSort()");

    DynamicArray<int> s;
    s.pushBack(50); s.pushBack(10); s.pushBack(40);
    s.pushBack(20); s.pushBack(30);
    cout << "before: "; s.print();
    s.selectionSort();
    cout << "after : "; s.print();

    section("insertionSort()");

    DynamicArray<int> ins;
    ins.pushBack(50); ins.pushBack(10); ins.pushBack(40);
    ins.pushBack(20); ins.pushBack(30);
    cout << "before: "; ins.print();
    ins.insertionSort();
    cout << "after : "; ins.print();


    // =========================================================================
    //  shrinkToFit
    // =========================================================================
    section("shrinkToFit()");

    DynamicArray<int> sf;
    for (int i = 0; i < 9; i++) sf.pushBack(i);
    // after 9 pushBacks: size=9, capacity=16
    cout << "before shrink: "; sf.printInfo();
    sf.shrinkToFit();
    cout << "after  shrink: "; sf.printInfo();
    // capacity is now exactly 9


    // =========================================================================
    //  fill / clear
    // =========================================================================
    section("fill(0) then clear()");

    DynamicArray<int> fc;
    fc.pushBack(1); fc.pushBack(2); fc.pushBack(3);
    cout << "before fill : "; fc.print();
    fc.fill(0);
    cout << "after  fill : "; fc.print();
    fc.clear();
    fc.printInfo();


    // =========================================================================
    //  Works with double
    // =========================================================================
    section("DynamicArray<double>");

    DynamicArray<double> d;
    d.pushBack(3.14); d.pushBack(1.41); d.pushBack(2.71); d.pushBack(1.73);
    cout << "before: "; d.print();
    d.insertionSort();
    cout << "after : "; d.print();
    cout << "min=" << d.min() << " | max=" << d.max() << "\n";


    // =========================================================================
    //  Error handling
    // =========================================================================
    section("Error handling");

    DynamicArray<int> e;
    e.get(0);       // [ERROR] empty → out of range
    e.remove(5);    // [ERROR] out of range


    // =========================================================================
    //  END
    // =========================================================================
    cout << "\n============================================================\n";
    cout << "  Phase 1 / DynamicArray<T> complete\n";
    cout << "============================================================\n\n";

    return 0;
}


// =============================================================================
//  CHEAT SHEET / DynamicArray<T> quick reference
// =============================================================================
//
//  CONSTRUCTION
//  DynamicArray<T> arr;            default capacity = 4
//  DynamicArray<T> arr(N);         custom initial capacity
//
//  CORE ACCESS          Complexity
//  arr.get(i)           O(1)
//  arr.set(i, val)      O(1)
//  arr.front()          O(1)
//  arr.back()           O(1)
//
//  INSERT / DELETE
//  arr.pushBack(val)    O(1) amortized   auto-resizes if full
//  arr.popBack()        O(1)
//  arr.insert(i, val)   O(n)             auto-resizes if full
//  arr.remove(i)        O(n)
//
//  SEARCH
//  arr.search(val)      O(n)   first index or -1
//  arr.contains(val)    O(n)   true / false
//  arr.count(val)       O(n)   occurrences
//
//  SORTING
//  arr.bubbleSort()     O(n²)
//  arr.selectionSort()  O(n²)
//  arr.insertionSort()  O(n²)  best O(n) if nearly sorted
//
//  UTILITY
//  arr.swap(i, j)       O(1)
//  arr.reverse()        O(n)
//  arr.fill(val)        O(n)
//  arr.clear()          O(1)   resets size, keeps block
//  arr.shrinkToFit()    O(n)   capacity → size (reclaims memory)
//  arr.min()            O(n)
//  arr.max()            O(n)
//
//  STATE
//  arr.isEmpty()        O(1)
//  arr.getSize()        O(1)
//  arr.getCapacity()    O(1)
//  / no isFull() / dynamic array is never permanently full /
//
//  DISPLAY
//  arr.print()          O(n)
//  arr.printInfo()      O(n)
//
//  PRIVATE (fires automatically)
//  resize(newCap)       O(n)   doubles capacity when full
// =============================================================================