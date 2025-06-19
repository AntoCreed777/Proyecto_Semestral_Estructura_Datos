#pragma once

#include "definiciones.hpp"

class BoyerMoore {
    public:
        /**
         * @brief Busca un patrón en un archivo utilizando el algoritmo de Boyer-Moore.
         * 
         * @param nombre_archivo Nombre del archivo donde se realizará la búsqueda.
         * @param patron Patrón a buscar en el archivo.
         * @return true Si el patrón se encuentra en el archivo.
         */
        static int buscar(const std::string& nombre_archivo, const std::string& patron);
};
