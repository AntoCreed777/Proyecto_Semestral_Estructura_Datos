#include "../include/definiciones.hpp"
#include "../include/knuth_morris_pratt.hpp"
#include <fstream>

unsigned int KnuthMorrisPratt::buscar(const std::string& texto, const std::string& patron) {
    vc tabla_de_saltos = calcular_tabla_de_saltos(patron);

    size_t posicion_patron = 0;
    unsigned int ocurrencias = 0;

    // Leer carácter por carácter
    for (char caracter : texto) {
        while (posicion_patron > 0 && caracter != patron[posicion_patron]) {
            posicion_patron = tabla_de_saltos[posicion_patron - 1];
        }

        if (caracter == patron[posicion_patron]) {
            posicion_patron++;
        }

        if (posicion_patron == patron.size()) {
            ocurrencias++;
            posicion_patron = tabla_de_saltos[posicion_patron - 1];
        }
    }

    return ocurrencias;   // Retorna la cantidad de ocurrencias encontradas
}

vc KnuthMorrisPratt::calcular_tabla_de_saltos(const std::string& patron) {
    vc tabla_de_saltos(patron.size(), 0);
    size_t j = 0; // Índice para el prefijo más largo

    for (size_t i = 1; i < patron.size(); i++) {

        // Retroceder usando valores previos de la tabla
        while (j > 0 && patron[i] != patron[j]) {
            j = tabla_de_saltos[j - 1];
        }

        if (patron[i] == patron[j]) j++;

        tabla_de_saltos[i] = j;
    }
    
    return tabla_de_saltos;
}
