#include "Red.h"
#include <iostream>
#include <fstream>

Red::Red() {}

bool Red::existeEnrutador(const std::string& nombre) const {
    return enrutadores.find(nombre) != enrutadores.end();
}

bool Red::agregarEnrutador(const std::string& nombre) {
    if (existeEnrutador(nombre)) {
        return false; // El enrutador ya existe
    }
    enrutadores[nombre] = Enrutador(nombre);
    return true;
}

bool Red::eliminarEnrutador(const std::string& nombre) {
    if (!existeEnrutador(nombre)) {
        return false;
    }

    // 1. Elimina el enrutador de la red
    enrutadores.erase(nombre);

    // 2. Remueve las conexiones hacia este enrutador en los demás vecinos
    for (auto& par : enrutadores) {
        par.second.eliminarVecino(nombre);
    }

    return true;
}

bool Red::agregarEnlace(const std::string& origen, const std::string& destino, int costo) {
    if (!existeEnrutador(origen) || !existeEnrutador(destino)) {
        return false; // Ambos nodos deben existir en la red
    }

    enrutadores[origen].agregarOActualizarVecino(destino, costo);
    enrutadores[destino].agregarOActualizarVecino(origen, costo);
    return true;
}

bool Red::eliminarEnlace(const std::string& origen, const std::string& destino) {
    if (!existeEnrutador(origen) || !existeEnrutador(destino)) {
        return false;
    }

    enrutadores[origen].eliminarVecino(destino);
    enrutadores[destino].eliminarVecino(origen);
    return true;
}

void Red::imprimirRed() const {
    if (enrutadores.empty()) {
        std::cout << "La red esta vacia.\n";
    } else {
        for (const auto& par : enrutadores) {
            par.second.imprimirVecinos();
        }
    }
}

void Red::imprimirTablaEnrutador(const std::string& nombre) const {
    auto it = enrutadores.find(nombre);
    if (it != enrutadores.end()) {
        it->second.imprimirTabla();
    } else {
        std::cout << "Error: El enrutador '" << nombre << "' no existe.\n";
    }
}
bool Red::cargarDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) return false;

    std::string origen, destino;
    int costo;

    while (archivo >> origen >> destino >> costo) {
        if (!existeEnrutador(origen)) agregarEnrutador(origen);
        if (!existeEnrutador(destino)) agregarEnrutador(destino);
        agregarEnlace(origen, destino, costo);
    }

    archivo.close();
    return true;
}