#include "Sorts.h"
#include <iostream>
#include <vector>

/*
using namespace std;

// =====================================================
// CLASE PUNTOS
// =====================================================
// Será el objeto que ordenaremos.
// =====================================================

class Puntos
{
public:

    // Variable de puntuación.
    int puntuaciones;
};

// =====================================================
// FUNCIÓN PRINT
// =====================================================
// Imprime el vector.
// =====================================================

void printPuntos(const vector<Puntos>& p)
{
    cout << "{ ";

    // Recorremos el vector.
    for (const auto& x : p)
    {
        // Imprimimos puntuación.
        cout << x.puntuaciones << " ";
    }

    cout << "}\n";
}

int main()
{
    // =====================================================
    // VECTOR ORIGINAL
    // =====================================================

    vector<Puntos> puntos =
    {
        {50},
        {10},
        {80},
        {25},
        {99},
        {1}
    };

    cout << "Vector original:\n";

    printPuntos(puntos);

    // =====================================================
    // BUBBLE SORT
    // =====================================================

    Sort::bubbleSort(
        puntos,

        // Lambda comparador.
        // Orden ascendente.
        [](const Puntos& a, const Puntos& b)
        {
            return a.puntuaciones < b.puntuaciones;
        }
    );

    cout << "\nBubble Sort:\n";

    printPuntos(puntos);

    // =====================================================
    // QUICK SORT
    // =====================================================

    Sort::quickSortRecursive(
        puntos,

        // Lambda.
        [](const Puntos& a, const Puntos& b)
        {
            return a.puntuaciones < b.puntuaciones;
        }
    );

    cout << "\nQuick Sort:\n";

    printPuntos(puntos);

    // =====================================================
    // MERGE SORT
    // =====================================================

    Sort::mergeSortRecursive(
        puntos,

        [](const Puntos& a, const Puntos& b)
        {
            return a.puntuaciones < b.puntuaciones;
        }
    );

    cout << "\nMerge Sort:\n";

    printPuntos(puntos);

    // =====================================================
    // QUICK SELECT
    // =====================================================
    // Busca el elemento en índice k.
    // =====================================================

    Puntos elemento =
        Sort::quickSelectIterative(
            puntos,
            2,

            [](const Puntos& a, const Puntos& b)
            {
                return a.puntuaciones < b.puntuaciones;
            }
        );

    cout << "\nElemento k=2:\n";

    cout << elemento.puntuaciones;

    return 0;
}*/