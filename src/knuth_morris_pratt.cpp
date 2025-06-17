#include "../include/definiciones.hpp"
#include "../include/knuth_morris_pratt.hpp"
#include <fstream>

bool KnuthMorrisPratt::buscar(const fs::path& nombre_archivo, const std::string& patron) {
    std::ifstream archivo(nombre_archivo, std::ios::in);
    if (!archivo.is_open()) {
        throw std::ios_base::failure("No se pudo abrir el archivo: " + nombre_archivo.string());
    }

    vc tabla_de_saltos = calcular_tabla_de_saltos(patron);

    char caracter;
    size_t posicion_patron = 0;

    // Leer carácter por carácter
    while (archivo.get(caracter)) {
        if (caracter == patron[posicion_patron]) {
            posicion_patron++;
            if (posicion_patron == patron.size()) {
                // Se encontró el patrón completo
                archivo.close();
                return true;
            }
        }
        else {
            posicion_patron = (posicion_patron > 0) ? tabla_de_saltos[posicion_patron] : 0;
        }
    }

    archivo.close();
    return false;   // El patrón no fue encontrado
}

vc KnuthMorrisPratt::calcular_tabla_de_saltos(const std::string& patron) {
    vc tabla_de_saltos(patron.size(), 0);
    size_t j = 0; // Índice para el prefijo más largo

    for (size_t i = 1; i < patron.size(); i++) {
        if (patron[i] == patron[j]) {
            j++;
            tabla_de_saltos[i] = j;
        } else if (j > 0) {
            // Retroceder usando valores previos de la tabla
            j = tabla_de_saltos[j - 1];
            i--; // Revisar el carácter actual nuevamente
        } else {
            // No hay coincidencias
            tabla_de_saltos[i] = 0;
        }
    }

    return tabla_de_saltos;
}
