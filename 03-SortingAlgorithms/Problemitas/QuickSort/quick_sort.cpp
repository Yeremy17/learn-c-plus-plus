#include "Sort.h"
#include <iostream>
#include <string>

using std::cout; using std::cin; using std::string; using std::vector;

class Puntos {
public:
	int puntuaciones;
};

void printPuntos(const std::vector<Puntos>& p)
{
	cout << "==============================\n"; cout << "Puntuaciones: { ";
	for (const auto& tabla : p)
	{
		
		 cout << tabla.puntuaciones << ", ";
	}

	cout << "}";
}

void recursiveQuickSortOrder(std::vector<Puntos>& p)
{
	Sort::quickSortRecursive(p, [](const Puntos& p1, const Puntos& p2)
		{
			return p1.puntuaciones > p2.puntuaciones;
		}
	);
}

int main()
{
	vector<Puntos> misPuntitos = {
		{1},{23},{12},{54},{80},{129},{26},{35},{45},{45},{12},{45},{8}, {75},{74},{67},{100},{99},{84}
	};

	printPuntos(misPuntitos);

	recursiveQuickSortOrder(misPuntitos);

	cout << "\n\n";

	printPuntos(misPuntitos);

	cout << "\n\n";

	return 0;
}