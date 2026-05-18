#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// =============================================================================
//  BasicSorts<T>
//  All methods are static — no instantiation needed:
//      BasicSorts<int>::bubbleSort(arr, n);
//      BasicSorts<int>::bubbleSort(arr, n, [](int a, int b){ return a > b; });
//
//  METHOD                  BIG O              NOTES
//  bubbleSort              O(n²) / O(n) best  stable
//  bubbleSortOptimized     O(n²) / O(n) best  stable + early exit
//  bubbleSortCocktail      O(n²) / O(n) best  stable + bidirectional
//  selectionSort           O(n²) always       NOT stable, min swaps
//  insertionSort           O(n²) / O(n) best  stable, best for small arrays
//  exchangeSort            O(n²) always       NOT stable
//  fisherYatesShuffle      O(n)               uniform random — call srand() first
// =============================================================================

template <typename T>
class BasicSorts {

private:

    static void swap(T& a, T& b) {
        T tmp = a; 
        a = b; 
        b = tmp;
    }

public:

    // ── Bubble Sort ──────────────────────────────────────────── O(n²) / O(n)
    static void bubbleSort(T* arr, int n) {
        for (int i = 0; i < n - 1; i++)
            for (int j = 0; j < n - 1 - i; j++)
                if (arr[j] > arr[j + 1])
                    swap(arr[j], arr[j + 1]);
    }

    template <typename Compare>
    static void bubbleSort(T* arr, int n, Compare cmp) {
        for (int i = 0; i < n - 1; i++)
            for (int j = 0; j < n - 1 - i; j++)
                if (!cmp(arr[j], arr[j + 1]))
                    swap(arr[j], arr[j + 1]);
    }

    // ── Bubble Sort Optimized ─────────────────────────── O(n²) / O(n) best
    static void bubbleSortOptimized(T* arr, int n) {
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            for (int j = 0; j < n - 1 - i; j++)
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            if (!swapped) break;
        }
    }

    template <typename Compare>
    static void bubbleSortOptimized(T* arr, int n, Compare cmp) {
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            for (int j = 0; j < n - 1 - i; j++)
                if (!cmp(arr[j], arr[j + 1])) {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            if (!swapped) break;
        }
    }

    // ── Bubble Sort Cocktail (bidirectional) ─────────── O(n²) / O(n) best
    static void bubbleSortCocktail(T* arr, int n) {
        int left = 0, right = n - 1;
        bool swapped = true;
        while (swapped) {
            swapped = false;
            for (int i = left; i < right; i++)
                if (arr[i] > arr[i + 1]) { swap(arr[i], arr[i + 1]); swapped = true; }
            right--;
            if (!swapped) break;
            swapped = false;
            for (int i = right; i > left; i--)
                if (arr[i - 1] > arr[i]) { swap(arr[i - 1], arr[i]); swapped = true; }
            left++;
        }
    }

    template <typename Compare>
    static void bubbleSortCocktail(T* arr, int n, Compare cmp) {
        int left = 0, right = n - 1;
        bool swapped = true;
        while (swapped) {
            swapped = false;
            for (int i = left; i < right; i++)
                if (!cmp(arr[i], arr[i + 1])) { swap(arr[i], arr[i + 1]); swapped = true; }
            right--;
            if (!swapped) break;
            swapped = false;
            for (int i = right; i > left; i--)
                if (!cmp(arr[i - 1], arr[i])) { swap(arr[i - 1], arr[i]); swapped = true; }
            left++;
        }
    }

    // ── Selection Sort ───────────────────────────────────────── O(n²) always
    static void selectionSort(T* arr, int n) {
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++)
                if (arr[j] < arr[minIdx]) minIdx = j;
            if (minIdx != i) swap(arr[i], arr[minIdx]);
        }
    }

    template <typename Compare>
    static void selectionSort(T* arr, int n, Compare cmp) {
        for (int i = 0; i < n - 1; i++) {
            int bestIdx = i;
            for (int j = i + 1; j < n; j++)
                if (cmp(arr[j], arr[bestIdx])) bestIdx = j;
            if (bestIdx != i) swap(arr[i], arr[bestIdx]);
        }
    }

    // ── Insertion Sort ───────────────────────────────── O(n²) / O(n) best
    static void insertionSort(T* arr, int n) {
        for (int i = 1; i < n; i++) {
            T key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) { arr[j + 1] = arr[j]; j--; }
            arr[j + 1] = key;
        }
    }

    template <typename Compare>
    static void insertionSort(T* arr, int n, Compare cmp) {
        for (int i = 1; i < n; i++) {
            T key = arr[i];
            int j = i - 1;
            while (j >= 0 && !cmp(arr[j], key)) { arr[j + 1] = arr[j]; j--; }
            arr[j + 1] = key;
        }
    }

    // ── Exchange Sort ────────────────────────────────────────── O(n²) always
    static void exchangeSort(T* arr, int n) {
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++)
                if (arr[i] > arr[j]) swap(arr[i], arr[j]);
    }

    template <typename Compare>
    static void exchangeSort(T* arr, int n, Compare cmp) {
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++)
                if (!cmp(arr[i], arr[j])) swap(arr[i], arr[j]);
    }

    // ── Fisher-Yates Shuffle ──────────────────────────────────────── O(n)
    // call srand(time(nullptr)) once before using this
    static void fisherYatesShuffle(T* arr, int n) {
        for (int i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(arr[i], arr[j]);
        }
    }

};