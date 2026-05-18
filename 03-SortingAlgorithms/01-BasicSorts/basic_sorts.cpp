// =============================================================================
//  SORTING ALGORITHMS / BASIC SORTS
//  Topic  : BasicSorts<T>
//  Author : Yeremy Acuña Chavez
//  Repo   : https://github.com/yeremyacuna
// =============================================================================
//
//  ROADMAP PROGRESS
//  ─────────────────────────────────────────────────────────────────────────
//  ✓ Fase 0  / punteros y memoria
//  ✓ Fase 1  / StaticArray, DynamicArray, LinkedList
//  ✓ Fase 2  / Stack, Queue
//  ✓ Fase 3  / DoublyLinkedList
//  ▶ SORTING / BasicSorts  ← aquí estamos
//    SORTING / IntermediateSorts
//    SORTING / AdvancedSorts
//    Fase 3  / CircularList, Deque
//    Fase 4  / BinaryTree, BST, BinaryHeap
//    Fase 5  / HashTable, HashSet
//    Fase 6  / Graphs
//    Fase 7  / AVL, Trie, SegmentTree, UnionFind
//  ─────────────────────────────────────────────────────────────────────────
//
//  INDEX / BasicSorts<T>
//  ─────────────────────────────────────────────────────────────────────────
//  All methods are STATIC / no instantiation needed:
//      BasicSorts<int>::bubbleSort(arr, n);
//      BasicSorts<int>::bubbleSort(arr, n, [](int a, int b){ return a > b; });
//
//  [1]  bubbleSort           O(n^2) avg/worst  |  O(n) best
//  [2]  bubbleSortOptimized  O(n^2) avg/worst  |  O(n) best  + early exit
//  [3]  bubbleSortCocktail   O(n^2) avg/worst  |  O(n) best  + bidirectional
//  [4]  selectionSort        O(n^2) always
//  [5]  insertionSort        O(n^2) worst       |  O(n) best
//  [6]  exchangeSort         O(n^2) always
//  [7]  fisherYatesShuffle   O(n)  / randomize, not sort
//
//  Every method has TWO overloads:
//      sort(T* arr, int n)              / default: ascending order
//      sort(T* arr, int n, Compare cmp) / lambda: any order/field
//  ─────────────────────────────────────────────────────────────────────────
//
//  HOW STATIC METHODS WORK HERE
//  ─────────────────────────────────────────────────────────────────────────
//  A static method belongs to the CLASS, not to an instance.
//  You call it directly on the type without creating an object:
//
//      BasicSorts<int>::bubbleSort(arr, 5);        // no object needed
//
//  This makes sense for sorting / there is no "state" to store,
//  the function just transforms the array you give it.
//
//  HOW LAMBDAS WORK HERE
//  ─────────────────────────────────────────────────────────────────────────
//  A comparator lambda tells the sort HOW to compare two elements.
//  It receives two values (a, b) and returns true if a should come BEFORE b.
//
//      ascending  (default) : [](int a, int b){ return a < b; }
//      descending           : [](int a, int b){ return a > b; }
//      by field             : [](Student a, Student b){ return a.grade > b.grade; }
//
//  The sort never knows the type / it just calls cmp(a, b) and decides.
//  Template<typename Compare> lets any callable (lambda, function ptr) work.
//
//  Compile: g++ -std=c++17 -Wall -Wextra -o basic_sorts basic_sorts.cpp
//  Run    : ./basic_sorts
// =============================================================================

#include <iostream>
#include <cstdlib>    // rand(), srand()
#include <ctime>      // time() / for random seed

using namespace std;


// =============================================================================
//  HELPER / print array
// =============================================================================
template <typename T>
void printArray(const char* label, T* arr, int n) {
    cout << label << ": [ ";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << " ]\n";
}

void section(const char* title) {
    cout << "\n============================================================\n";
    cout << "  " << title << "\n";
    cout << "============================================================\n";
}


// =============================================================================
//  CLASS / BasicSorts<T>
// =============================================================================

template <typename T>
class BasicSorts {

public:

    // =========================================================================
    //  [1] BUBBLE SORT
    //  ─────────────────────────────────────────────────────────────────────
    //  IDEA: repeatedly walk the array comparing adjacent pairs.
    //        if left > right → swap them.
    //        after each full pass, the LARGEST unsorted element has
    //        "bubbled up" to its final position at the end.
    //
    //  VISUAL:
    //    pass 1: [5,3,1,4,2] → [3,1,4,2,5]   5 is final
    //    pass 2: [3,1,4,2,5] → [1,3,2,4,5]   4 is final
    //    pass 3: [1,3,2,4,5] → [1,2,3,4,5]   3 is final
    //
    //  TIME  : O(n^2) avg/worst / two nested loops each up to n
    //  SPACE : O(1)  / only a temp variable for swapping
    //  STABLE: yes   / equal elements never swap (only swap on strict >)
    // =========================================================================

    // --- default: ascending ---
    static void bubbleSort(T* arr, int n) {
        for (int i = 0; i < n - 1; i++) {
            // after pass i, the last i elements are already in final position
            // so the inner loop only needs to go up to n-1-i
            for (int j = 0; j < n - 1 - i; j++) {
                if (arr[j] > arr[j + 1]) {
                    // adjacent pair out of order / swap them
                    T tmp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = tmp;
                }
            }
        }
    }

    // --- lambda comparator: cmp(a,b) returns true if a should come before b ---
    template <typename Compare>
    static void bubbleSort(T* arr, int n, Compare cmp) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - 1 - i; j++) {
                if (!cmp(arr[j], arr[j + 1])) {
                    // arr[j] should NOT come before arr[j+1] → swap
                    T tmp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = tmp;
                }
            }
        }
    }


    // =========================================================================
    //  [2] BUBBLE SORT OPTIMIZED
    //  ─────────────────────────────────────────────────────────────────────
    //  SAME as bubble sort but adds a 'swapped' flag.
    //  If an entire pass completes with zero swaps → array is already sorted.
    //  We exit immediately instead of running useless passes.
    //
    //  This makes BEST CASE O(n) / one pass to confirm already sorted.
    //  Avg/worst remain O(n^2).
    //
    //  TIME  : O(n^2) avg/worst  |  O(n) best
    //  SPACE : O(1)
    //  STABLE: yes
    // =========================================================================

    static void bubbleSortOptimized(T* arr, int n) {
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;   // reset flag each pass

            for (int j = 0; j < n - 1 - i; j++) {
                if (arr[j] > arr[j + 1]) {
                    T tmp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = tmp;
                    swapped = true;   // at least one swap happened
                }
            }

            if (!swapped) break;
            // no swap in this entire pass → every pair is in order → done
        }
    }

    template <typename Compare>
    static void bubbleSortOptimized(T* arr, int n, Compare cmp) {
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            for (int j = 0; j < n - 1 - i; j++) {
                if (!cmp(arr[j], arr[j + 1])) {
                    T tmp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = tmp;
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }


    // =========================================================================
    //  [3] BUBBLE SORT COCKTAIL (bidirectional bubble sort)
    //  ─────────────────────────────────────────────────────────────────────
    //  IDEA: standard bubble sort only moves large elements RIGHT (forward).
    //        cocktail sort alternates direction each pass:
    //          → forward pass  : bubbles largest to the right end
    //          ← backward pass : bubbles smallest to the left end
    //
    //  This handles "turtles" (small elements near the end) faster.
    //  A turtle in standard bubble sort takes O(n) passes to reach position 0.
    //  Cocktail sort pushes it left in the very next backward pass.
    //
    //  VISUAL:
    //    [3,1,5,2,4]
    //    → fwd : [1,3,2,4,5]   5 placed at right
    //    ← bwd : [1,2,3,4,5]   1 placed at left
    //    done  (both pointers crossed)
    //
    //  TIME  : O(n^2) avg/worst  |  O(n) best
    //  SPACE : O(1)
    //  STABLE: yes
    // =========================================================================

    static void bubbleSortCocktail(T* arr, int n) {
        int left = 0;
        int right = n - 1;
        bool swapped = true;

        while (swapped) {
            swapped = false;

            // --- forward pass: push largest to right ---
            for (int i = left; i < right; i++) {
                if (arr[i] > arr[i + 1]) {
                    T tmp = arr[i];
                    arr[i] = arr[i + 1];
                    arr[i + 1] = tmp;
                    swapped = true;
                }
            }
            right--;
            // right boundary shrinks / rightmost element is now final

            if (!swapped) break;
            swapped = false;

            // --- backward pass: push smallest to left ---
            for (int i = right; i > left; i--) {
                if (arr[i - 1] > arr[i]) {
                    T tmp = arr[i - 1];
                    arr[i - 1] = arr[i];
                    arr[i] = tmp;
                    swapped = true;
                }
            }
            left++;
            // left boundary grows / leftmost element is now final
        }
    }

    template <typename Compare>
    static void bubbleSortCocktail(T* arr, int n, Compare cmp) {
        int left = 0, right = n - 1;
        bool swapped = true;
        while (swapped) {
            swapped = false;
            for (int i = left; i < right; i++) {
                if (!cmp(arr[i], arr[i + 1])) {
                    T tmp = arr[i]; arr[i] = arr[i + 1]; arr[i + 1] = tmp;
                    swapped = true;
                }
            }
            right--;
            if (!swapped) break;
            swapped = false;
            for (int i = right; i > left; i--) {
                if (!cmp(arr[i - 1], arr[i])) {
                    T tmp = arr[i - 1]; arr[i - 1] = arr[i]; arr[i] = tmp;
                    swapped = true;
                }
            }
            left++;
        }
    }


    // =========================================================================
    //  [4] SELECTION SORT
    //  ─────────────────────────────────────────────────────────────────────
    //  IDEA: divide array into [sorted | unsorted].
    //        each pass: scan the unsorted part, find the MINIMUM,
    //        swap it to the boundary position.
    //        boundary moves right by 1 each pass.
    //
    //  VISUAL:
    //    [5,3,1,4,2]
    //    pass 0: min=1 at idx 2 → swap(0,2) → [1,3,5,4,2]
    //    pass 1: min=2 at idx 4 → swap(1,4) → [1,2,5,4,3]
    //    pass 2: min=3 at idx 4 → swap(2,4) → [1,2,3,4,5]
    //    pass 3: min=4 at idx 3 → swap(3,3) → no change
    //
    //  KEY PROPERTY: exactly n-1 swaps total / regardless of input.
    //  Useful when swapping is expensive (large objects, disk writes).
    //
    //  TIME  : O(n^2) ALWAYS / no early exit possible (must always find min)
    //  SPACE : O(1)
    //  STABLE: NO / swapping can change relative order of equal elements
    // =========================================================================

    static void selectionSort(T* arr, int n) {
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;   // assume current position holds the minimum

            // scan the unsorted portion [i+1 .. n-1] for a smaller element
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[minIdx]) {
                    minIdx = j;   // found a new minimum
                }
            }

            // place the minimum at position i (only if it's not already there)
            if (minIdx != i) {
                T tmp = arr[i];
                arr[i] = arr[minIdx];
                arr[minIdx] = tmp;
            }
        }
    }

    template <typename Compare>
    static void selectionSort(T* arr, int n, Compare cmp) {
        for (int i = 0; i < n - 1; i++) {
            int bestIdx = i;
            for (int j = i + 1; j < n; j++) {
                if (cmp(arr[j], arr[bestIdx])) bestIdx = j;
                // cmp(arr[j], arr[bestIdx]) = true means arr[j] should come first
            }
            if (bestIdx != i) {
                T tmp = arr[i]; arr[i] = arr[bestIdx]; arr[bestIdx] = tmp;
            }
        }
    }


    // =========================================================================
    //  [5] INSERTION SORT
    //  ─────────────────────────────────────────────────────────────────────
    //  IDEA: build a sorted portion one element at a time.
    //        take the next unsorted element (key) and INSERT it into
    //        its correct position within the already-sorted portion
    //        by shifting larger elements one step to the right.
    //
    //  VISUAL (| marks sorted boundary):
    //    [5,|3,1,4,2]  key=3 → shift 5 right → [3,5,|1,4,2]
    //    [3,5,|1,4,2]  key=1 → shift 5,3 right → [1,3,5,|4,2]
    //    [1,3,5,|4,2]  key=4 → shift 5 right → [1,3,4,5,|2]
    //    [1,3,4,5,|2]  key=2 → shift 5,4,3 right → [1,2,3,4,5]
    //
    //  BEST CASE: nearly sorted data / almost no shifts needed → O(n)
    //  Insertion sort is the standard choice for small arrays (n < 32).
    //  TimSort (advanced) uses insertion sort internally for small runs.
    //
    //  TIME  : O(n^2) worst  |  O(n) best
    //  SPACE : O(1)
    //  STABLE: yes / equal elements never shift past each other
    // =========================================================================

    static void insertionSort(T* arr, int n) {
        for (int i = 1; i < n; i++) {
            T   key = arr[i];   // element to insert into sorted portion
            int j = i - 1;   // last index of sorted portion

            // shift elements right until we find where key belongs
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];   // shift right
                j--;
            }
            // j+1 is the correct position for key
            arr[j + 1] = key;
        }
    }

    template <typename Compare>
    static void insertionSort(T* arr, int n, Compare cmp) {
        for (int i = 1; i < n; i++) {
            T   key = arr[i];
            int j = i - 1;
            while (j >= 0 && !cmp(arr[j], key)) {
                // arr[j] should NOT come before key → shift it right
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }


    // =========================================================================
    //  [6] EXCHANGE SORT
    //  ─────────────────────────────────────────────────────────────────────
    //  IDEA: for each element at position i, compare it with EVERY element
    //        at positions i+1 to n-1. if arr[i] > arr[j] → swap immediately.
    //        after all comparisons for position i, arr[i] holds its final value.
    //
    //  DIFFERENCE vs bubble sort:
    //    Bubble sort  → compares adjacent pairs (j, j+1) → "bubbles" max up
    //    Exchange sort → compares position i with ALL positions j>i → places min
    //
    //  VISUAL:
    //    [5,3,1,4,2]
    //    i=0: compare 5 with 3→swap[3,5,1,4,2], with 1→swap[1,5,3,4,2],
    //         with 4→no, with 2→no   → arr[0]=1 final
    //    i=1: compare 5 with 3→swap[1,3,5,4,2], with 4→no, with 2→swap[1,2,5,4,3]
    //    ...
    //
    //  TIME  : O(n^2) always / nested loops, no early exit
    //  SPACE : O(1)
    //  STABLE: NO / long-range swaps can disrupt relative order
    // =========================================================================

    static void exchangeSort(T* arr, int n) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (arr[i] > arr[j]) {
                    // arr[i] is larger than a later element / swap immediately
                    T tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }

    template <typename Compare>
    static void exchangeSort(T* arr, int n, Compare cmp) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (!cmp(arr[i], arr[j])) {
                    T tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
    }


    // =========================================================================
    //  [7] FISHER-YATES SHUFFLE  (not a sort / a randomizer)
    //  ─────────────────────────────────────────────────────────────────────
    //  IDEA: produce a uniformly random permutation of the array.
    //        walk from the last element to the first.
    //        for each position i, pick a random index j in [0, i]
    //        and swap arr[i] with arr[j].
    //
    //  WHY it's fair: each element has exactly 1/n probability of ending up
    //  in any position. No permutation is more likely than another.
    //
    //  COMMON USE: shuffle a deck of cards, randomize a playlist,
    //  generate random test cases for sorting benchmarks.
    //
    //  TIME  : O(n) / single pass
    //  SPACE : O(1)
    //  NOTE  : call srand(time(nullptr)) once before using this
    // =========================================================================

    static void fisherYatesShuffle(T* arr, int n) {
        for (int i = n - 1; i > 0; i--) {
            // pick a random index j in [0, i] (inclusive)
            int j = rand() % (i + 1);
            // rand() % (i+1) gives a number in [0, i]

            // swap arr[i] with arr[j]
            T tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }

};


// =============================================================================
//  MAIN / runs all sorts with demos
// =============================================================================

int main() {

    srand(static_cast<unsigned>(time(nullptr)));
    // seed the random number generator once / used by fisherYatesShuffle

    // =========================================================================
    //  [1] Bubble Sort
    // =========================================================================
    section("[1] Bubble Sort / O(n^2)");

    int a1[] = { 5, 3, 8, 1, 9, 2, 7, 4, 6 };
    int n1 = 9;
    printArray("before", a1, n1);
    BasicSorts<int>::bubbleSort(a1, n1);
    printArray("after ", a1, n1);

    // descending with lambda
    int a1d[] = { 5, 3, 8, 1, 9, 2, 7, 4, 6 };
    BasicSorts<int>::bubbleSort(a1d, n1, [](int a, int b) { return a > b; });
    printArray("desc  ", a1d, n1);


    // =========================================================================
    //  [2] Bubble Sort Optimized
    // =========================================================================
    section("[2] Bubble Sort Optimized / O(n^2) avg | O(n) best");

    int a2[] = { 1, 2, 3, 4, 5 };   // already sorted / exits after 1 pass
    printArray("before (sorted)", a2, 5);
    BasicSorts<int>::bubbleSortOptimized(a2, 5);
    printArray("after           ", a2, 5);

    int a2b[] = { 5, 4, 3, 2, 1 };
    printArray("before (reversed)", a2b, 5);
    BasicSorts<int>::bubbleSortOptimized(a2b, 5);
    printArray("after             ", a2b, 5);


    // =========================================================================
    //  [3] Cocktail Sort
    // =========================================================================
    section("[3] Bubble Sort Cocktail (bidirectional) / O(n^2)");

    int a3[] = { 2, 3, 4, 5, 1 };   // 1 is a "turtle" (small at the end)
    printArray("before", a3, 5);
    BasicSorts<int>::bubbleSortCocktail(a3, 5);
    printArray("after ", a3, 5);


    // =========================================================================
    //  [4] Selection Sort
    // =========================================================================
    section("[4] Selection Sort / O(n^2) always, minimum swaps");

    int a4[] = { 64, 25, 12, 22, 11 };
    int n4 = 5;
    printArray("before", a4, n4);
    BasicSorts<int>::selectionSort(a4, n4);
    printArray("after ", a4, n4);

    // sort doubles descending
    double a4d[] = { 3.14, 1.41, 2.71, 1.73, 0.57 };
    BasicSorts<double>::selectionSort(a4d, 5, [](double a, double b) { return a > b; });
    printArray("double desc", a4d, 5);


    // =========================================================================
    //  [5] Insertion Sort
    // =========================================================================
    section("[5] Insertion Sort / O(n^2) worst | O(n) best (nearly sorted)");

    int a5[] = { 12, 11, 13, 5, 6 };
    int n5 = 5;
    printArray("before", a5, n5);
    BasicSorts<int>::insertionSort(a5, n5);
    printArray("after ", a5, n5);

    // nearly sorted / best case behavior
    int a5b[] = { 1, 2, 3, 5, 4 };
    printArray("nearly sorted before", a5b, 5);
    BasicSorts<int>::insertionSort(a5b, 5);
    printArray("nearly sorted after ", a5b, 5);


    // =========================================================================
    //  [6] Exchange Sort
    // =========================================================================
    section("[6] Exchange Sort / O(n^2) always");

    int a6[] = { 8, 3, 7, 1, 5 };
    int n6 = 5;
    printArray("before", a6, n6);
    BasicSorts<int>::exchangeSort(a6, n6);
    printArray("after ", a6, n6);


    // =========================================================================
    //  [7] Fisher-Yates Shuffle
    // =========================================================================
    section("[7] Fisher-Yates Shuffle / O(n) uniform random permutation");

    int a7[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int n7 = 10;
    printArray("original", a7, n7);
    BasicSorts<int>::fisherYatesShuffle(a7, n7);
    printArray("shuffle1", a7, n7);
    BasicSorts<int>::fisherYatesShuffle(a7, n7);
    printArray("shuffle2", a7, n7);   // different each time


    // =========================================================================
    //  LAMBDA DEMOS / sort by custom field
    // =========================================================================
    section("Lambda demo / sort struct by field");

    struct Student {
        const char* name;
        int         grade;
    };

    Student students[] = {
        {"Ana",    85},
        {"Carlos", 92},
        {"Maria",  78},
        {"Luis",   95},
        {"Sofia",  88}
    };
    int ns = 5;

    // sort by grade descending using insertion sort + lambda
    BasicSorts<Student>::insertionSort(students, ns,
        [](Student a, Student b) { return a.grade > b.grade; });

    cout << "\nStudents sorted by grade (highest first):\n";
    for (int i = 0; i < ns; i++)
        cout << "  [" << i + 1 << "] " << students[i].name
        << " / " << students[i].grade << "\n";

    // sort by name ascending
    BasicSorts<Student>::insertionSort(students, ns,
        [](Student a, Student b) { return string(a.name) < string(b.name); });

    cout << "\nStudents sorted by name (A-Z):\n";
    for (int i = 0; i < ns; i++)
        cout << "  [" << i + 1 << "] " << students[i].name
        << " / " << students[i].grade << "\n";


    // =========================================================================
    //  END
    // =========================================================================
    cout << "\n============================================================\n";
    cout << "  BasicSorts<T> complete\n";
    cout << "============================================================\n\n";

    return 0;
}


// =============================================================================
//  CHEAT SHEET / BasicSorts<T> quick reference
// =============================================================================
//
//  USAGE (no object needed / all static):
//  BasicSorts<T>::method(arr, n);
//  BasicSorts<T>::method(arr, n, [](T a, T b){ return a < b; });
//
//  METHOD                  BIG O              NOTES
//  ─────────────────────────────────────────────────────────────────────────
//  bubbleSort              O(n^2) avg/worst    stable
//                          O(n)  best
//
//  bubbleSortOptimized     O(n^2) avg/worst    stable + early exit if sorted
//                          O(n)  best
//
//  bubbleSortCocktail      O(n^2) avg/worst    stable + bidirectional
//                          O(n)  best         good for "turtles"
//
//  selectionSort           O(n^2) ALWAYS       NOT stable, min swaps (n-1)
//
//  insertionSort           O(n^2) worst        stable, O(n) if nearly sorted
//                          O(n)  best         best for small/nearly-sorted
//
//  exchangeSort            O(n^2) always       NOT stable
//
//  fisherYatesShuffle      O(n)               uniform random permutation
//                                             call srand() first
//
//  LAMBDA COMPARATOR:
//  ascending  (default) : [](T a, T b){ return a < b; }
//  descending           : [](T a, T b){ return a > b; }
//  by field             : [](MyClass a, MyClass b){ return a.field < b.field; }
// =============================================================================