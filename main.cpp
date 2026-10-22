#include <iostream>
#include "Red.h"

int main() {
    Red miRed;

    miRed.agregarEnrutador("A");
    miRed.agregarEnrutador("B");
    miRed.agregarEnrutador("C");
    miRed.agregarEnrutador("D");

    miRed.agregarEnlace("A", "B", 4);
    miRed.agregarEnlace("A", "D", 5);
    miRed.agregarEnlace("A", "C", 10);
    miRed.agregarEnlace("B", "C", 3);
    miRed.agregarEnlace("B", "D", 1);
    miRed.agregarEnlace("C", "D", 2);

    miRed.imprimirRed();

    std::cout << "\nEliminando enlace B <-> C y enrutador D...\n";
    miRed.eliminarEnlace("B", "C");
    miRed.eliminarEnrutador("D");

    miRed.imprimirRed();

    return 0;
}