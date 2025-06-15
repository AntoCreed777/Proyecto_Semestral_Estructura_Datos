#pragma once

#include "definiciones.hpp"

class SuffixTrees {
    public:
        /**
         * @brief Busca un patrón en un archivo utilizando el algoritmo de Suffix Trees.
         * 
         * @param nombre_archivo Nombre del archivo donde se realizará la búsqueda.
         * @param patron Patrón a buscar en el archivo.
         * @return true Si el patrón se encuentra en el archivo.
         */
        static bool buscar(const fs::path& nombre_archivo, const std::string& patron);

    private:
        // Agregar todas las funciones privadas necesarias para implementar el algoritmo de Suffix Trees
};