#pragma once
#ifndef SORT_HPP
#define SORT_HPP

#include <vector>
#include <stack>
#include <algorithm>
#include <stdexcept>

using namespace std;

class Sort {
private:
    template <typename T, typename Compare>

    // My Merge Sort, Left: L, Right: R -> Tiene merge
    static void merge(std::vector<T>& arr, int left, int mid, int right, Compare comp) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<T> L(arr.begin() + left, arr.begin() + mid + 1);
        vector<T> R(arr.begin() + mid + 1, arr.begin() + right + 1);

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (comp(L[i], R[j])) {
                arr[k++] = L[i++];
            }
            else {
                arr[k++] = R[j++];
            }
        }
        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];
    }

    template <typename T, typename Compare>
    static void mergeSortRecHelper(std::vector<T>& arr, int left, int right, Compare comp) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSortRecHelper(arr, left, mid, comp);
        mergeSortRecHelper(arr, mid + 1, right, comp);
        merge(arr, left, mid, right, comp);
    }

    // My Quick Sort, low , high -> Tiene partition
    template <typename T, typename Compare>
    static int partition(std::vector<T>& arr, int low, int high, Compare comp) {
        T pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (comp(arr[j], pivot)) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return (i + 1);
    }

    template <typename T, typename Compare>
    static void quickSortRecHelper(std::vector<T>& arr, int low, int high, Compare comp) {
        if (low < high) {
            int pi = partition(arr, low, high, comp);
            quickSortRecHelper(arr, low, pi - 1, comp);
            quickSortRecHelper(arr, pi + 1, high, comp);
        }
    }

    template <typename T, typename Compare>
    static T quickSelectRecHelper(std::vector<T>& arr, int low, int high, int k, Compare comp) {
        if (low == high) return arr[low];
        int pi = partition(arr, low, high, comp);

        if (k == pi) return arr[k];
        else if (k < pi) return quickSelectRecHelper(arr, low, pi - 1, k, comp);
        else return quickSelectRecHelper(arr, pi + 1, high, k, comp);
    }

public:
    // // My Merge Sort Recursive
    template <typename T, typename Compare>
    static void mergeSortRecursive(std::vector<T>& arr, Compare comp) {
        if (!arr.empty()) {
            mergeSortRecHelper(arr, 0, arr.size() - 1, comp);
        }
    }

    // // My Merge Sort Interative
    template <typename T, typename Compare>
    static void mergeSortIterative(std::vector<T>& arr, Compare comp) {
        int n = arr.size();
        for (int curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
            for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
                int mid = std::min(left_start + curr_size - 1, n - 1);
                int right_end = std::min(left_start + 2 * curr_size - 1, n - 1);
                merge(arr, left_start, mid, right_end, comp);
            }
        }
    }

    // // My Quick Sort Recursive
    template <typename T, typename Compare>
    static void quickSortRecursive(std::vector<T>& arr, Compare comp) {
        if (!arr.empty()) {
            quickSortRecHelper(arr, 0, arr.size() - 1, comp);
        }
    }

    template <typename T, typename Compare>
    static void quickSortIterative(std::vector<T>& arr, Compare comp) {
        if (arr.empty()) return;

        std::stack<std::pair<int, int>> stk;
        stk.push({ 0, arr.size() - 1 });

        while (!stk.empty()) {
            int low = stk.top().first;
            int high = stk.top().second;
            stk.pop();

            if (low < high) {
                int pi = partition(arr, low, high, comp);
                stk.push({ low, pi - 1 });
                stk.push({ pi + 1, high });
            }
        }
    }

    template <typename T, typename Compare>
    static T quickSelectRecursive(std::vector<T>& arr, int k, Compare comp) {
        if (k < 0 || k >= arr.size()) throw std::out_of_range("Índice k fuera de límites");
        return quickSelectRecHelper(arr, 0, arr.size() - 1, k, comp);
    }

    template <typename T, typename Compare>
    static T quickSelectIterative(std::vector<T>& arr, int k, Compare comp) {
        if (k < 0 || k >= arr.size()) throw std::out_of_range("Índice k fuera de límites");

        int low = 0, high = arr.size() - 1;
        while (low <= high) {
            if (low == high) return arr[low];

            int pi = partition(arr, low, high, comp);

            if (pi == k) return arr[k];
            else if (k < pi) high = pi - 1;
            else low = pi + 1;
        }
        return arr[k];
    }
};

#endif