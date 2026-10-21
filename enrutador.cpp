#include "Enrutador.h"

Enrutador::Enrutador() : nombre("") {}

Enrutador::Enrutador(const std::string& nombre) : nombre(nombre) {
    tablaCostos[nombre] = 0; // El costo hacia sí mismo siempre es 0
}

std::string Enrutador::getNombre() const {
    return nombre;
}

void Enrutador::agregarOActualizarVecino(const std::string& vecino, int costo) {
    vecinos[vecino] = costo;
}

void Enrutador::eliminarVecino(const std::string& vecino) {
    vecinos.erase(vecino);
}

const std::map<std::string, int>& Enrutador::getVecinos() const {
    return vecinos;
}

void Enrutador::setCostoDestino(const std::string& destino, int costo) {
    tablaCostos[destino] = costo;
}

int Enrutador::getCostoDestino(const std::string& destino) const {
    auto it = tablaCostos.find(destino);
    if (it != tablaCostos.end()) {
        return it->second;
    }
    return -1; // Inalcanzable o no registrado
}

void Enrutador::imprimirVecinos() const {
    std::cout << "Vecinos directos de " << nombre << ":\n";
    for (const auto& par : vecinos) {
        std::cout << "  -> " << par.first << " (Costo: " << par.second << ")\n";
    }
}

void Enrutador::imprimirTabla() const {
    std::cout << "\nTabla de costos local para: " << nombre << "\n";
    std::cout << "Destino\t|\tCosto\n";
    std::cout << "-----------------------\n";
    for (const auto& par : tablaCostos) {
        std::cout << par.first << "\t|\t" << par.second << "\n";
    }
}