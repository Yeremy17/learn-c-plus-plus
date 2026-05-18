#pragma once
#include <iostream>
#include <vector>
#include <string>

using std::cout; using std::cin; using std::vector; using std::string;
/*Bubble Sort*/

template <typename T>
static void swap(T& n1, T&n2)
{
    T temp = n1;
    n1 = n2;
    n2 = temp;
}

template <typename T>
static void print(vector<T>& vect)
{
    
    for (auto v : vect)
    {
        cout << v << " ";
    }
    cout << " }\n\n";
}

template <typename T, typename Compare>
static void bubbleSort(vector<T>& value, Compare comp)
{
    int n = value.size();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (comp(value[j], value[j+1]))
            {
                swap(value[j + 1], value[j]);
            }
        }
    }
}

/*
Problema 1 — Ordenar edades
Enunciado

Una escuela necesita ordenar las edades de sus estudiantes de menor a mayor usando Bubble Sort.

Input
5
17 14 18 15 16
Primera línea → cantidad de estudiantes
Segunda línea → edades
Output
14 15 16 17 18
*/

static void problemOne() {
    vector<int> edades = {};
    int cantidad = 0;
    cout << "Inserta cantidad de estudiantes: " ; cin >> cantidad;

    for (int i = 0; i < cantidad; i++)
    {
        int insert = 0;
        cout << "Edad[" << i << "]= "; cin >> insert;
        edades.push_back(insert);
    }

    cout << "\n\nInput: { ";
    print(edades);

    bubbleSort(edades,[](const int&n1, const int& n2){
        return n1 > n2; 
        });

    cout << "\nOutput: { ";
    print(edades);

    system("pause>0");
}


/*
Problema 2 — Ordenar temperaturas
Enunciado

Un laboratorio registró temperaturas y necesita ordenarlas ascendentemente usando Bubble Sort.

Input
6
30 25 28 20 27 24
Output
20 24 25 27 28 30
*/

static void problemTwo() {
    vector<int> temperaturas = {};
    int cantidad = 0;
    cout << "Inserta cantidad de temperaturas registradas: "; cin >> cantidad;

    for (int i = 0; i < cantidad; i++)
    {
        int insert = 0;
        cout << "Temperatura[N°" << i+1 << "]= "; cin >> insert;
        temperaturas.push_back(insert);
    }

    cout << "\n\nInput: { ";
    print(temperaturas);

    bubbleSort(temperaturas, [](const int& n1, const int& n2) {
        return n1 > n2;
        });

    cout << "\nOutput: { ";
    print(temperaturas);

    system("pause>0");
}


/*
Selection Sort
Problema 1 — Ranking de puntajes
Enunciado

Un videojuego quiere ordenar los puntajes de mayor a menor usando Selection Sort.

Input
5
120 450 300 700 200
Output
700 450 300 200 120
Problema 2 — Ordenar precios
Enunciado

Una tienda necesita ordenar precios de productos de menor a mayor usando Selection Sort.

Input
4
80 25 60 40
Output
25 40 60 80
Insertion Sort
Problema 1 — Cartas numeradas
Enunciado

Un jugador tiene cartas desordenadas y quiere ordenarlas ascendentemente usando Insertion Sort.

Input
7
9 3 7 1 8 2 5
Output
1 2 3 5 7 8 9
Problema 2 — Ordenar tiempos
Enunciado

Un corredor registró sus tiempos y quiere ordenarlos de menor a mayor.

Input
5
55 42 60 38 49
Output
38 42 49 55 60
Merge Sort
Problema 1 — Ordenar ventas
Enunciado

Una empresa necesita ordenar ventas mensuales usando Merge Sort.

Input
8
500 1200 300 750 950 100 400 850
Output
100 300 400 500 750 850 950 1200
Problema 2 — Ordenar notas
Enunciado

Una universidad desea ordenar notas finales de menor a mayor usando Merge Sort.

Input
6
14 18 11 20 16 13
Output
11 13 14 16 18 20
Quick Sort
Problema 1 — Ordenar IDs
Enunciado

Un sistema necesita ordenar IDs numéricos rápidamente usando Quick Sort.

Input
7
105 12 87 43 9 300 56
Output
9 12 43 56 87 105 300
Problema 2 — Ordenar salarios
Enunciado

Una empresa necesita ordenar salarios de mayor a menor usando Quick Sort.

Input
5
1200 3000 2500 1800 5000
Output
5000 3000 2500 1800 1200
Quick Select
Problema 1 — Encontrar el tercer mayor
Enunciado

Encuentra el tercer número más grande usando Quick Select.

Input
6
80 20 100 50 70 90
3
Primera línea → cantidad
Segunda línea → números
Tercera línea → k
Output
80
Problema 2 — Encontrar el segundo menor
Enunciado

Encuentra el segundo número más pequeño usando Quick Select.

Input
7
15 3 9 20 1 12 7
2
Output
3
Extra — Problema usando objetos
Problema — Ordenar estudiantes por promedio
Enunciado

Dado un conjunto de estudiantes con nombre y promedio, ordénalos de mayor a menor promedio usando cualquier algoritmo de ordenamiento.

Input
4
Ana 18
Luis 15
Carlos 20
Maria 17
Output
Carlos 20
Ana 18
Maria 17
Luis 15
*/