#pragma once

#include "definiciones.hpp"

class RobinKarp {
    public:
        /**
         * @brief Busca un patrón en un archivo utilizando el algoritmo de Robin-Karp.
         * 
         * @param nombre_archivo Nombre del archivo donde se realizará la búsqueda.
         * @param patron Patrón a buscar en el archivo.
         * @return true Si el patrón se encuentra en el archivo.
         */
        static bool buscar(const std::string& nombre_archivo, const std::string& patron);

    private:
        // Agregar todas las funciones privadas necesarias para implementar el algoritmo de Robin-Karp
};