#pragma once

#include "definiciones.hpp"

class BoyerMoore {
    public:
        /**
         * @brief Busca un patrón en un texto utilizando el algoritmo de Boyer-Moore.
         * 
         * @param texto Texto donde se realizará la búsqueda.
         * @param patron Patrón a buscar en el texto.
         * @return true Si el patrón se encuentra en el texto.
         */
        static bool buscar(const std::string& texto, const std::string& patron);

    private:
        // Agregar todas las funciones privadas necesarias para implementar el algoritmo de Boyer-Moore
};