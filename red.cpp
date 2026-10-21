#include "Red.h"
#include <iostream>

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

    // Enlace simétrico/bidireccional
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
    std::cout << "\n================ TOPOLOGIA DE LA RED ================\n";
    if (enrutadores.empty()) {
        std::cout << "La red esta vacia.\n";
    } else {
        for (const auto& par : enrutadores) {
            par.second.imprimirVecinos();
        }
    }
    std::cout << "=====================================================\n";
}

void Red::imprimirTablaEnrutador(const std::string& nombre) const {
    auto it = enrutadores.find(nombre);
    if (it != enrutadores.end()) {
        it->second.imprimirTabla();
    } else {
        std::cout << "Error: El enrutador '" << nombre << "' no existe.\n";
    }
}