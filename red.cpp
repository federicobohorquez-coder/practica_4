#include "Red.h"
#include <iostream>
#include <fstream>
#include <limits>

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
int Red::calcularRutaCorta(const std::string& origen, const std::string& destino, std::list<std::string>& camino) const {
    camino.clear();

    if (!existeEnrutador(origen) || !existeEnrutador(destino)) return -1;
    if (origen == destino) {
        camino.push_back(origen);
        return 0;
    }

    const int INF = std::numeric_limits<int>::max();
    std::map<std::string, int> distancias;
    std::map<std::string, std::string> previo;
    std::map<std::string, bool> visitados;

    for (const auto& par : enrutadores) {
        distancias[par.first] = INF;
        visitados[par.first] = false;
    }

    distancias[origen] = 0;

    for (size_t i = 0; i < enrutadores.size(); ++i) {
        std::string u = "";
        int minDist = INF;

        for (const auto& par : distancias) {
            if (!visitados[par.first] && par.second < minDist) {
                minDist = par.second;
                u = par.first;
            }
        }

        if (u.empty() || u == destino) break;
        visitados[u] = true;

        const auto& vecinos = enrutadores.at(u).getVecinos();
        for (const auto& parVecino : vecinos) {
            std::string v = parVecino.first;
            int peso = parVecino.second;

            if (!visitados[v] && distancias[u] != INF && distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
                previo[v] = u;
            }
        }
    }

    if (distancias[destino] == INF) return -1;

    // Reconstrucción del camino en std::list insertando al inicio O(1)
    std::string actual = destino;
    while (actual != origen) {
        camino.push_front(actual);
        actual = previo[actual];
    }
    camino.push_front(origen);

    return distancias[destino];
}