#include "../include/definiciones.hpp"
#include "../include/knuth_morris_pratt.hpp"
#include <fstream>

bool KnuthMorrisPratt::buscar(const std::string& texto, const std::string& patron) {
    vc tabla_de_saltos = calcular_tabla_de_saltos(patron);

    size_t posicion_patron = 0;

    // Leer carácter por carácter
    for (char caracter : texto) {
        if (caracter == patron[posicion_patron]) {
            posicion_patron++;

            // Se encontró el patrón completo
            if (posicion_patron == patron.size()) return true;
        }
        else {
            posicion_patron = (posicion_patron > 0) ? tabla_de_saltos[posicion_patron] : 0;
        }
    }

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
