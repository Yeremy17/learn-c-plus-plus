#pragma once
#include <iostream>
#include <vector>
#include <string>

using std::cout; using std::cin; using std::vector; using std::string;


template <typename T>
static void swap(T& n1, T& n2) {
    T temp = n1;
    n1 = n2;
    n2 = temp;
}

template <typename T>
static void printVector(vector<T>& vect)
{
    cout << "Vector = { ";

    for (const auto& valor : vect)
    {
        cout << valor << ", ";
    }

    cout << "}\n";
}

template <typename T, typename Compare>
static void bubbleSort(vector<T>& arre, Compare comp)
{
    int n = arre.size();

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n-1; j++)
        {
            // comp(a,b) es el comparador lambda.
            // Pregunta si el elemento siguiente
            // debe ir antes que el actual.
            if (comp(arre[j + 1], arre[j]))
            {
                swap(arre[j], arre[j + 1]);
            }
        }
}

static void principal()
{
    std::vector<int> numeritos = {
        1,2,5,9,7,8,1,5,6,4,5,9,7,8,9,1,6,4,8,2,0,1,15,12,13,1,451,584,159,15,17,5126,1651,21,1
    };

    // Antes del bubble sort
    cout << "\t\tAntes del bubble sort: \n";
    printVector(numeritos);

    bubbleSort(numeritos, [](const int& n1, const int& n2) {
        return n1 > n2;
        });

    // Despues del bubble sort
    cout << "\n\n\t\tDespues del bubble sort: \n";
    printVector(numeritos);

    system("pause>0");
}