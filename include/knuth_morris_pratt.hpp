#pragma once

#include "definiciones.hpp"

class KnuthMorrisPratt {
    public:
        /**
         * @brief Busca un patrón en un texto utilizando el algoritmo de Knuth-Morris-Pratt.
         * 
         * @param texto Texto donde se realizará la búsqueda.
         * @param patron Patrón a buscar en el texto.
         * @return true Si el patrón se encuentra en el texto.
         */
        static bool buscar(const std::string& texto, const std::string& patron);

    private:
        static vc calcular_tabla_de_saltos(const std::string& patron);
};