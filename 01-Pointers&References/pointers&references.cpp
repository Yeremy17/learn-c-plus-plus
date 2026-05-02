// =============================================================================
//  DATA STRUCTURES EN C++ / FASE 0
//  Tema   : Punteros, Referencias y Memoria Dinamica
//  Autor  : (tu nombre)
//  Repo   : github.com/(tu usuario)/data-structures-cpp
// =============================================================================
//
//  ÍNDICE
//  ──────────────────────────────────────────────────────────────────────────
//  [1] Variables y direcciones de memoria    (&  / address-of)
//  [2] Punteros                              (int*)
//  [3] Desreferenciar un puntero             (*ptr)
//  [4] Modificar un valor mediante puntero
//  [5] Puntero nulo                          (nullptr)
//  [6] Referencias                           (int&)
//  [7] Comparacion: puntero vs referencia
//  [8] Memoria dinamica / valor simple       (new / delete)
//  [9] Memoria dinamica / array dinamico     (new[] / delete[])
// [10] Preview: nodo para data structures
//  ──────────────────────────────────────────────────────────────────────────
//
//  Compilar:  g++ -std=c++17 -o fase_00 fase_00_punteros_referencias.cpp
//  Ejecutar:  ./fase_00
//
// =============================================================================

#include <iostream>    // cout, endl

// Usamos este alias para no escribir "std::" en cada línea
using namespace std;


// =============================================================================
//  FUNCIÓN AUXILIAR / imprime un separador de seccion
// =============================================================================
void seccion(const string& titulo) {
    cout << "\n";
    cout << "============================================================\n";
    cout << "  " << titulo << "\n";
    cout << "============================================================\n";
}


// =============================================================================
//  MAIN / todos los ejemplos corren aquí en orden
// =============================================================================
int main() {

    // =========================================================================
    //  [1] VARIABLES Y DIRECCIONES DE MEMORIA
    // =========================================================================
    seccion("[1] Variables y direcciones de memoria");

    // Declarar una variable normal
    int x = 42;
    //  └─ int  : tipo (4 bytes en la mayoría de sistemas)
    //  └─ x    : nombre con el que tú la conoces
    //  └─ = 42 : valor almacenado en esa casilla de RAM

    // El operador  &  (address-of) devuelve la direccion de memoria de la variable
    cout << "Valor de x     : " << x << "\n";   // 42
    cout << "Direccion de x : " << &x << "\n";   // algo como 0x7ffd1a2b  (varía cada ejecucion)

    // Cada vez que ejecutas el programa la direccion cambia,
    // pero x siempre vive en UNA casilla con UNA direccion única.

    int y = 100;
    cout << "Direccion de y : " << &y << "\n";   // direccion distinta a x


    // =========================================================================
    //  [2] PUNTEROS
    // =========================================================================
    seccion("[2] Punteros / declaracion e inicializacion");

    // Un puntero es una variable cuyo VALOR es una direccion de memoria.
    // En lugar de guardar 42, guarda "donde vive" otro dato.

    int* ptr;       // declara un puntero a int
    //   └─ int*  : tipo "puntero a int"  (el * es parte del tipo, no del nombre)
    //   └─ ptr   : nombre de la variable puntero
    //              ahora mismo contiene basura / NO lo uses aún

    ptr = &x;       // inicializa: ptr ahora guarda la direccion de x
    //   └─ &x    : operador address-of / devuelve la direccion de x

    cout << "Valor de ptr   : " << ptr << "\n";  // direccion de x   (ej. 0x7ffd1a2b)
    cout << "Direccion de x : " << &x << "\n";  // mismo número → ptr apunta a x

    // Declaracion + inicializacion en una sola línea (lo mas común):
    int* ptr2 = &x;     // ptr2 tambien apunta a x
    cout << "ptr2           : " << ptr2 << "\n";  // misma direccion


    // =========================================================================
    //  [3] DESREFERENCIAR UN PUNTERO  (*ptr)
    // =========================================================================
    seccion("[3] Desreferenciar / *ptr");

    // El operador  *  sobre un puntero significa:
    // "ve a esa direccion de memoria y trae el valor que hay ahí"
    //
    //   DECLARACIÓN:   int* ptr  → * significa "esto es un puntero"
    //   EXPRESIÓN:     *ptr      → * significa "desreferencia: dame el valor"
    //
    // Son dos usos distintos del mismo símbolo / no los confundas.

    int  a = 55;
    int* p = &a;      // p apunta a a

    cout << "a     = " << a << "\n";   // 55        / valor directo
    cout << "p     = " << p << "\n";   // 0x...     / direccion de a
    cout << "*p    = " << *p << "\n";   // 55        / desreferencia: valor en esa direccion
    cout << "&a    = " << &a << "\n";   // 0x...     / direccion de a
    cout << "p == &a : " << (p == &a) << "\n";  // 1 (true) / confirman que p apunta a a


    // =========================================================================
    //  [4] MODIFICAR UN VALOR MEDIANTE PUNTERO
    // =========================================================================
    seccion("[4] Modificar valor via puntero");

    int  num = 10;
    int* pNum = &num;

    cout << "Antes  / num = " << num << "\n";   // 10

    *pNum = 999;
    // └─ va a la direccion guardada en pNum (la casilla de num)
    //    y escribe 999 ahí dentro
    //    → num cambio sin mencionarla directamente

    cout << "Despues / num = " << num << "\n";   // 999
    cout << "Despues / *pNum = " << *pNum << "\n"; // 999  (los dos ven lo mismo)

    // Esto es clave para data structures:
    // desde una funcion puedes modificar variables de otra funcion,
    // y desde un nodo puedes modificar el valor de otro nodo.


    // =========================================================================
    //  [5] PUNTERO NULO / nullptr
    // =========================================================================
    seccion("[5] Puntero nulo / nullptr");

    int* pNulo = nullptr;
    // └─ nullptr : valor especial que significa "no apunta a ningún lado"
    //             En los nodos de linked list, nullptr marcara el final de la lista

    cout << "pNulo = " << pNulo << "\n";  // 0  (nullptr equivale a 0)

    // NUNCA desreferencies un puntero nulo → crash (segmentation fault)
    // Por eso siempre verificamos antes:
    if (pNulo != nullptr) {
        cout << "tiene valor: " << *pNulo << "\n";
    }
    else {
        cout << "pNulo es nullptr / no se puede desreferenciar\n";
    }

    // Inicializar siempre tus punteros, ya sea con una direccion o con nullptr:
    int  val = 7;
    int* pVal = &val;    // ok / apunta a algo
    int* pVacio = nullptr; // ok / explícitamente vacío
    // int* pBasura;       // MAL / contiene basura, desreferenciar es undefined behavior


    // =========================================================================
    //  [6] REFERENCIAS
    // =========================================================================
    seccion("[6] Referencias / int&");

    // Una referencia es un ALIAS: otro nombre para la misma variable.
    // No ocupa memoria nueva / comparte exactamente la misma casilla.

    int  orig = 42;
    int& ref = orig;
    //   └─ int& : tipo "referencia a int"   (& en la declaracion = referencia)
    //   └─ ref  : el alias
    //   └─ = orig : OBLIGATORIO inicializar al declarar (no puede quedar sin asignar)

    cout << "orig     = " << orig << "\n";   // 42
    cout << "ref      = " << ref << "\n";   // 42  / misma casilla

    // Modificar ref modifica orig directamente:
    ref = 999;
    cout << "orig tras ref=999 : " << orig << "\n";  // 999

    // Verificar que comparten la misma direccion:
    cout << "&orig = " << &orig << "\n";
    cout << "&ref  = " << &ref << "\n";
    // Imprime la MISMA direccion / ref no tiene direccion propia

    // No puedes redirigir una referencia una vez asignada:
    int  otro = 77;
    ref = otro;   // esto NO hace que ref apunte a otro
    //            esto COPIA el valor de otro en la casilla de orig
    cout << "orig tras ref=otro : " << orig << "\n";  // 77
    cout << "&ref sigue siendo : " << &ref << "\n";  // misma direccion que &orig


    // =========================================================================
    //  [7] COMPARACIÓN: PUNTERO vs REFERENCIA
    // =========================================================================
    seccion("[7] Puntero vs Referencia / diferencias");

    int base = 50;

    // --- Puntero ---
    int* pComp = &base;   // tiene su propia casilla de memoria
    *pComp = 60;           // necesita * para leer/escribir el valor
    pComp = nullptr;      // se puede redirigir o anular en cualquier momento
    cout << "pComp (nulled): " << pComp << "\n";

    // --- Referencia ---
    int& rComp = base;    // alias / misma casilla que base
    rComp = 70;            // NO necesita * / usas el alias directamente
    // rComp = nullptr;    // ERROR: no puedes "nullear" una referencia
    cout << "base tras rComp=70 : " << base << "\n";

    //  ┌──────────────────┬──────────────────────┬──────────────────────┐
    //  │                  │     Puntero (int*)   │   Referencia (int&)  │
    //  ├──────────────────┼──────────────────────┼──────────────────────┤
    //  │ Casilla propia   │  SÍ                  │  NO (es el mismo)    │
    //  │ Puede ser null   │  SÍ (nullptr)        │  NO                  │
    //  │ Se puede redir.  │  SÍ                  │  NO                  │
    //  │ Necesita *       │  SÍ                  │  NO                  │
    //  │ Init. obligat.   │  NO                  │  SÍ siempre          │
    //  └──────────────────┴──────────────────────┴──────────────────────┘


    // =========================================================================
    //  [8] MEMORIA DINÁMICA / VALOR SIMPLE   (new / delete)
    // =========================================================================
    seccion("[8] Memoria dinamica / new / delete");

    // Hasta ahora todo vivía en el STACK (se libera automaticamente al salir del scope).
    // Con  new  reservamos en el HEAP: la memoria dura hasta que nosotros la liberemos.
    // Esto es esencial para construir nodos de linked lists, arboles, grafos, etc.

    int* heap1 = new int;
    //           └─ new int : pide al SO una casilla de 4 bytes en el heap
    //                        devuelve la direccion de esa casilla → la guardamos en heap1

    *heap1 = 42;            // guarda el valor en esa casilla del heap
    cout << "*heap1 = " << *heap1 << "\n";   // 42

    *heap1 = 100;           // podemos modificarlo como cualquier variable
    cout << "*heap1 = " << *heap1 << "\n";   // 100

    delete heap1;
    //     └─ devuelve esa memoria al sistema operativo
    //        IMPORTANTE: despues de delete, heap1 sigue guardando la direccion (ya invalida)

    heap1 = nullptr;
    //      └─ buena practica: nulleamos el puntero para que no quede "colgando"
    //         si accidentalmente lo uses, el crash sera claro y no silencioso

    cout << "heap1 tras delete+nullptr : " << heap1 << "\n";  // 0

    // ¿Que pasa si no haces delete?
    // → memory leak: la memoria queda reservada y nunca se libera mientras el programa corre
    // → en un programa largo (servidor, app) esto consume toda la RAM eventualmente


    // =========================================================================
    //  [9] MEMORIA DINÁMICA / ARRAY DINÁMICO   (new[] / delete[])
    // =========================================================================
    seccion("[9] Memoria dinamica / array dinamico");

    int tamano = 5;

    int* arr = new int[tamano];
    //         └─ new int[5] : reserva 5 casillas de int CONTIGUAS en el heap
    //                         devuelve la direccion de la primera casilla

    // Acceso por índice / igual que un array normal:
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 40;
    arr[4] = 50;

    cout << "Array dinamico: ";
    for (int i = 0; i < tamano; i++) {
        cout << arr[i];
        if (i < tamano - 1) cout << ", ";
    }
    cout << "\n";

    // Tambien puedes acceder con aritmetica de punteros:
    // arr[i]  es exactamente lo mismo que  *(arr + i)
    cout << "arr[2]      = " << arr[2] << "\n";  // 30
    cout << "*(arr + 2)  = " << *(arr + 2) << "\n";  // 30  / equivalente

    delete[] arr;
    //       └─ libera el array COMPLETO
    //          IMPORTANTE: usa  delete[]  no  delete  para arrays
    //          delete sin []  en un array → undefined behavior

    arr = nullptr;  // buena practica

    // Diferencia crítica:
    //   delete  heap1;     → libera un solo elemento
    //   delete[] arr;      → libera el array completo


    // =========================================================================
    // [10] PREVIEW / NODO PARA DATA STRUCTURES
    // =========================================================================
    seccion("[10] Preview / así usaremos esto en data structures");

    // Cada estructura que vamos a construir usa exactamente lo que vimos arriba.
    // Este es un nodo basico de Linked List (lo haremos en detalle en la Fase 1):

    struct Node {
        int   data;   // el valor que guarda el nodo
        Node* next;   // puntero al siguiente nodo (nullptr si es el último)
    };

    // Crear un nodo en el heap:
    Node* nodo1 = new Node;
    nodo1->data = 10;     // nodo1->data  es lo mismo que  (*nodo1).data
    nodo1->next = nullptr;

    Node* nodo2 = new Node;
    nodo2->data = 20;
    nodo2->next = nullptr;

    // Enlazar los nodos:
    nodo1->next = nodo2;  // nodo1 apunta a nodo2 → tenemos una mini linked list

    // Recorrer:
    Node* current = nodo1;
    cout << "Mini linked list: ";
    while (current != nullptr) {
        cout << current->data;
        if (current->next != nullptr) cout << " -> ";
        current = current->next;  // avanza al siguiente nodo
    }
    cout << " -> nullptr\n";

    // Liberar memoria (siempre en orden inverso o con cuidado):
    delete nodo2;
    nodo2 = nullptr;
    delete nodo1;
    nodo1 = nullptr;

    cout << "\nMemoria liberada correctamente.\n";


    // =========================================================================
    //  FIN
    // =========================================================================
    cout << "\n============================================================\n";
    cout << "  Fase 0 completada / base lista para construir estructuras\n";
    cout << "============================================================\n\n";

    return 0;
}

// =============================================================================
//  RESUMEN RÁPIDO / cheat sheet
// =============================================================================
//
//  int  x   = 42;      variable normal
//  &x                  direccion de memoria de x
//
//  int* p   = &x;      puntero: guarda la direccion de x
//  p                   la direccion (0x...)
//  *p                  desreferencia: el valor en esa direccion
//  *p = 99             escribe en esa direccion
//
//  int& r   = x;       referencia: alias de x, misma casilla
//  r = 99              modifica x directamente, sin *
//
//  int* h   = new int; reserva 1 int en el heap
//  delete h;           libera ese int del heap
//  h = nullptr;        evita dangling pointer
//
//  int* a   = new int[N]; reserva N ints contiguos en el heap
//  a[i] == *(a + i)       acceso equivalente
//  delete[] a;            libera el array (SIEMPRE con [])
//  a = nullptr;
//
//  nodo->campo         equivale a  (*nodo).campo  (acceso por puntero a struct)
//
// =============================================================================