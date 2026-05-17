#pragma once

// Librería para usar std::vector
#include <vector>

// =====================================================
// CLASE SORT
// Contendrá varios algoritmos de ordenamiento
// hechos manualmente usando templates.
// =====================================================
class Sort
{
public:

    // =====================================================
    // BUBBLE SORT
    // =====================================================
    // Template:
    // Permite que funcione con cualquier tipo de dato.
    // Ejemplo:
    // vector<int>
    // vector<float>
    // vector<Puntos>
    // =====================================================

    template<typename T, typename Compare>
    static void bubbleSort(std::vector<T>& arr, Compare comp)
    {
        // Tamaño del vector
        int n = arr.size();

        // Este for controla las pasadas completas.
        // Repite el proceso varias veces.
        for (int i = 0; i < n - 1; i++)
        {
            // Recorre comparando vecinos.
            for (int j = 0; j < n - 1 - i; j++)
            {
                // comp(a,b) es el comparador lambda.
                // Pregunta si el elemento siguiente
                // debe ir antes que el actual.
                if (comp(arr[j + 1], arr[j]))
                {
                    // Intercambiamos posiciones.
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    // =====================================================
    // SELECTION SORT
    // =====================================================

    template<typename T, typename Compare>
    static void selectionSort(std::vector<T>& arr, Compare comp)
    {
        int n = arr.size();

        // Recorremos cada posición.
        for (int i = 0; i < n - 1; i++)
        {
            // Asumimos que el menor es i.
            int minIndex = i;

            // Buscamos un menor real.
            for (int j = i + 1; j < n; j++)
            {
                // Si encontramos un elemento menor,
                // actualizamos minIndex.
                if (comp(arr[j], arr[minIndex]))
                {
                    minIndex = j;
                }
            }

            // Colocamos el menor adelante.
            swap(arr[i], arr[minIndex]);
        }
    }

    // =====================================================
    // INSERTION SORT
    // =====================================================

    template<typename T, typename Compare>
    static void insertionSort(std::vector<T>& arr, Compare comp)
    {
        int n = arr.size();

        // Empezamos desde el segundo elemento.
        for (int i = 1; i < n; i++)
        {
            // Guardamos el elemento actual.
            T key = arr[i];

            // Índice del elemento anterior.
            int j = i - 1;

            // Mientras los elementos anteriores
            // sean mayores que key.
            while (j >= 0 && comp(key, arr[j]))
            {
                // Movemos el elemento a la derecha.
                arr[j + 1] = arr[j];

                // Retrocedemos.
                j--;
            }

            // Insertamos key en su posición.
            arr[j + 1] = key;
        }
    }

    // =====================================================
    // MERGE SORT RECURSIVO
    // =====================================================

    template<typename T, typename Compare>
    static void mergeSortRecursive(std::vector<T>& arr, Compare comp)
    {
        // Verificamos que el vector no esté vacío.
        if (!arr.empty())
        {
            // Llamamos al helper.
            mergeSortHelper(arr, 0, arr.size() - 1, comp);
        }
    }

    // =====================================================
    // QUICK SORT RECURSIVO
    // =====================================================

    template<typename T, typename Compare>
    static void quickSortRecursive(std::vector<T>& arr, Compare comp)
    {
        if (!arr.empty())
        {
            quickSortHelper(arr, 0, arr.size() - 1, comp);
        }
    }

    // =====================================================
    // QUICK SELECT ITERATIVO
    // =====================================================
    // Busca el elemento k.
    // NO ordena todo el arreglo.
    // =====================================================

    template<typename T, typename Compare>
    static T quickSelectIterative(std::vector<T> arr, int k, Compare comp)
    {
        // Límites del arreglo.
        int left = 0;
        int right = arr.size() - 1;

        while (true)
        {
            // Particionamos.
            int pivotIndex = partition(arr, left, right, comp);

            // Si encontramos el índice.
            if (pivotIndex == k)
            {
                return arr[pivotIndex];
            }

            // Si k está a la izquierda.
            if (k < pivotIndex)
            {
                right = pivotIndex - 1;
            }
            else
            {
                // Si está a la derecha.
                left = pivotIndex + 1;
            }
        }
    }

private:

    // =====================================================
    // SWAP
    // =====================================================
    // Intercambia dos valores.
    // =====================================================

    template<typename T>
    static void swap(T& a, T& b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

    // =====================================================
    // MERGE
    // =====================================================
    // Mezcla dos subarreglos ordenados.
    // =====================================================

    template<typename T, typename Compare>
    static void merge(
        std::vector<T>& arr,
        int left,
        int mid,
        int right,
        Compare comp)
    {
        // Tamaño de la mitad izquierda.
        int n1 = mid - left + 1;

        // Tamaño de la mitad derecha.
        int n2 = right - mid;

        // Vectores temporales.
        std::vector<T> L(n1);
        std::vector<T> R(n2);

        // Copiamos izquierda.
        for (int i = 0; i < n1; i++)
        {
            L[i] = arr[left + i];
        }

        // Copiamos derecha.
        for (int j = 0; j < n2; j++)
        {
            R[j] = arr[mid + 1 + j];
        }

        // Índices.
        int i = 0;
        int j = 0;
        int k = left;

        // Mezclamos ordenadamente.
        while (i < n1 && j < n2)
        {
            if (comp(L[i], R[j]))
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
            }

            k++;
        }

        // Copiamos sobrantes izquierda.
        while (i < n1)
        {
            arr[k] = L[i];
            i++;
            k++;
        }

        // Copiamos sobrantes derecha.
        while (j < n2)
        {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    // =====================================================
    // MERGE SORT HELPER
    // =====================================================

    template<typename T, typename Compare>
    static void mergeSortHelper(
        std::vector<T>& arr,
        int left,
        int right,
        Compare comp)
    {
        // Caso base.
        if (left < right)
        {
            // Punto medio.
            int mid = (left + right) / 2;

            // Ordenamos izquierda.
            mergeSortHelper(arr, left, mid, comp);

            // Ordenamos derecha.
            mergeSortHelper(arr, mid + 1, right, comp);

            // Mezclamos.
            merge(arr, left, mid, right, comp);
        }
    }

    // =====================================================
    // PARTITION
    // =====================================================
    // Parte principal de QuickSort.
    // =====================================================

    template<typename T, typename Compare>
    static int partition(
        std::vector<T>& arr,
        int low,
        int high,
        Compare comp)
    {
        // Elegimos el pivote.
        T pivot = arr[high];

        // Índice de menores.
        int i = low - 1;

        // Recorremos.
        for (int j = low; j < high; j++)
        {
            // Si el elemento debe ir antes del pivote.
            if (comp(arr[j], pivot))
            {
                i++;

                // Intercambiamos.
                swap(arr[i], arr[j]);
            }
        }

        // Colocamos el pivote en su lugar.
        swap(arr[i + 1], arr[high]);

        // Retornamos posición final del pivote.
        return i + 1;
    }

    // =====================================================
    // QUICK SORT HELPER
    // =====================================================

    template<typename T, typename Compare>
    static void quickSortHelper(
        std::vector<T>& arr,
        int low,
        int high,
        Compare comp)
    {
        // Caso base.
        if (low < high)
        {
            // Particionamos.
            int pivotIndex = partition(arr, low, high, comp);

            // Ordenamos izquierda.
            quickSortHelper(arr, low, pivotIndex - 1, comp);

            // Ordenamos derecha.
            quickSortHelper(arr, pivotIndex + 1, high, comp);
        }
    }
};