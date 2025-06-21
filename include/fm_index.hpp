#pragma once

#include "definiciones.hpp"

class FMIndex {
    public:
        /**
         * @brief Busca un patrón en un texto utilizando el algoritmo de FM-Index.
         * 
         * @param texto Texto donde se realizará la búsqueda.
         * @param patron Patrón a buscar en el texto.
         * @return true Si el patrón se encuentra en el texto.
         */
        static bool buscar(const std::string& texto, const std::string& patron);

    private:
        // Agregar todas las funciones privadas necesarias para implementar el algoritmo de FMIndex
};