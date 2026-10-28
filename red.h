#ifndef RED_H
#define RED_H

#include "Enrutador.h"
#include <map>
#include <string>
#include <list>

class Red {
private:
    std::map<std::string, Enrutador> enrutadores; // <NombreEnrutador, ObjetoEnrutador>

public:
    Red();

    // Gestión de enrutadores
    bool agregarEnrutador(const std::string& nombre);
    bool eliminarEnrutador(const std::string& nombre);
    bool existeEnrutador(const std::string& nombre) const;

    // Gestión de conexiones (Enlaces bidireccionales)
    bool agregarEnlace(const std::string& origen, const std::string& destino, int costo);
    bool eliminarEnlace(const std::string& origen, const std::string& destino);

    // Visualización de la topología
    void imprimirRed() const;
    void imprimirTablaEnrutador(const std::string& nombre) const;
    bool cargarDesdeArchivo(const std::string& nombreArchivo);
    int calcularRutaCorta(const std::string& origen, const std::string& destino, std::list<std::string>& camino) const;
    void imprimirTodasLasTablas() const;
};

#endif