#include "Sort.hpp"
#include <iostream>
#include <string>

using std::cout; using std::cin; using std::string; using std::vector;

class Compra {
public:
    string producto;
    string fecha;
};

void printCompra(const vector<Compra>& co)
{
    for (const auto& compra : co)
    {
        cout << "==============================\n";
        cout << "Producto: " << compra.producto << '\n';
        cout << "Fecha: " << compra.fecha << "\n";
    }
    cout << "==============================";
}

void recursiveMergeSortOrder(vector<Compra>& co)
{
    Sort::mergeSortRecursive(co, [](const Compra& a, const Compra& b)
        {
            return a.fecha < b.fecha;
        }
    );
}
int main()
{
    vector<Compra> historial =
    {
        {"Laptop", "2026/12/10"},
        {"Mouse", "2026/05/25"},
        {"Teclado", "2026/01/05"}
    };

    recursiveMergeSortOrder(historial);

    printCompra(historial);


    return 0;
}