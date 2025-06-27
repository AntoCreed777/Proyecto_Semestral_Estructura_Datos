#pragma once

#include "definiciones.hpp"

class BoyerMoore {
    public:
        /**
         * @brief Busca un patrón en un texto utilizando el algoritmo de Boyer-Moore.
         * 
         * @param texto Texto donde se realizará la búsqueda.
         * @param patron Patrón a buscar en el texto.
         * @return cantidad de ocurrencias encontradas en el texto.
         */
        static unsigned int buscar(const std::string& texto, const std::string& patron);
};
