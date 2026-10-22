#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>
#include <map>
#include <iostream>

class Enrutador {
private:
    std::string nombre;
    std::map<std::string, int> vecinos;
    std::map<std::string, int> tablaCostos;

public:
    Enrutador();
    Enrutador(const std::string& nombre);

    std::string getNombre() const;

    // Gestión de vecinos directamente conectados
    void agregarOActualizarVecino(const std::string& vecino, int costo);
    void eliminarVecino(const std::string& vecino);
    const std::map<std::string, int>& getVecinos() const;

    // Gestión de la tabla de costos local
    void setCostoDestino(const std::string& destino, int costo);
    int getCostoDestino(const std::string& destino) const;

    // Métodos de visualización
    void imprimirTabla() const;
    void imprimirVecinos() const;
};

#endif