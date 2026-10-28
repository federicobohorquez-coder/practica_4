#include <iostream>
#include <string>
#include <list>
#include "Red.h"

void mostrarMenu() {
    std::cout << "   SIMULADOR DE RED DE ENRUTADORES\n";
    std::cout << "1. Cargar topologia desde archivo (.txt)\n";
    std::cout << "2. Agregar enrutador\n";
    std::cout << "3. Eliminar enrutador\n";
    std::cout << "4. Agregar / Actualizar enlace\n";
    std::cout << "5. Eliminar enlace\n";
    std::cout << "6. Ver topologia completa\n";
    std::cout << "7. Calcular ruta mas corta (Dijkstra)\n";
    std::cout << "8. Salir\n";
    std::cout << "Seleccione una opcion: ";
}

int main() {
    Red red;
    int opcion;

    do {
        mostrarMenu();
        std::cin >> opcion;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        switch (opcion) {
        case 1: {
            std::string archivo;
            std::cout << "Nombre del archivo (ej. red.txt): ";
            std::cin >> archivo;
            if (red.cargarDesdeArchivo(archivo)) {
                std::cout << ">> Topologia cargada exitosamente desde '" << archivo << "'.\n";
            } else {
                std::cout << ">> Error: No se pudo abrir el archivo.\n";
            }
            break;
        }
        case 2: {
            std::string nombre;
            std::cout << "Nombre del enrutador: ";
            std::cin >> nombre;
            if (red.agregarEnrutador(nombre)) {
                std::cout << ">> Enrutador '" << nombre << "' agregado.\n";
            } else {
                std::cout << ">> El enrutador ya existe.\n";
            }
            break;
        }
        case 3: {
            std::string nombre;
            std::cout << "Nombre del enrutador a eliminar: ";
            std::cin >> nombre;
            if (red.eliminarEnrutador(nombre)) {
                std::cout << ">> Enrutador '" << nombre << "' y sus enlaces eliminados.\n";
            } else {
                std::cout << ">> El enrutador no existe.\n";
            }
            break;
        }
        case 4: {
            std::string u, v;
            int costo;
            std::cout << "Origen: "; std::cin >> u;
            std::cout << "Destino: "; std::cin >> v;
            std::cout << "Costo: "; std::cin >> costo;
            if (red.agregarEnlace(u, v, costo)) {
                std::cout << ">> Enlace guardado exitosamente.\n";
            } else {
                std::cout << ">> Error: Uno o ambos enrutadores no existen.\n";
            }
            break;
        }
        case 5: {
            std::string u, v;
            std::cout << "Origen: "; std::cin >> u;
            std::cout << "Destino: "; std::cin >> v;
            if (red.eliminarEnlace(u, v)) {
                std::cout << ">> Enlace eliminado exitosamente.\n";
            } else {
                std::cout << ">> Error: No se pudo eliminar el enlace.\n";
            }
            break;
        }
        case 6: {
            std::cout << "1. Ver topologia completa (vecinos)\n";
            std::cout << "2. Ver tabla de costos de un enrutador\n";
            std::cout << "3. Ver tablas de costos de toda la red\n";
            std::cout << "Seleccione: ";
            int subOpcion;
            std::cin >> subOpcion;

            if (subOpcion == 1) {
                red.imprimirRed();
            } else if (subOpcion == 2) {
                std::string nombre;
                std::cout << "Nombre del enrutador: ";
                std::cin >> nombre;
                red.imprimirTablaEnrutador(nombre);
            } else if (subOpcion == 3) {
                red.imprimirTodasLasTablas();
            } else {
                std::cout << "Opcion no valida.\n";
            }
            break;
        }
        case 7: {
            std::string orig, dest;
            std::cout << "Enrutador origen: "; std::cin >> orig;
            std::cout << "Enrutador destino: "; std::cin >> dest;

            std::list<std::string> camino;
            int costoTotal = red.calcularRutaCorta(orig, dest, camino);

            if (costoTotal == -1) {
                std::cout << ">> No existe ruta entre " << orig << " y " << dest << ".\n";
            } else {
                std::cout << "\n>> Ruta mas corta: ";
                for (auto it = camino.begin(); it != camino.end(); ++it) {
                    std::cout << *it << (std::next(it) != camino.end() ? " -> " : "");
                }
                std::cout << "\n>> Costo total de envio: " << costoTotal << "\n";
            }
            break;
        }
        case 8:
            std::cout << "Saliendo del simulador...\n";
            break;
        default:
            std::cout << "Opcion invalida.\n";
        }
    } while (opcion != 8);

    return 0;
}