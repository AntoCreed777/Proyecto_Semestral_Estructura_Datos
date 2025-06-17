#pragma once

#include "definiciones.hpp"
#include <list>
#include <string>

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
        class Node {
            private:
                Node* children[256];
                std::list<int>* ind;
            
            public:
                Node();
                void insertSuffix(const std::string& suffix, int index);
                std::list<int>* search(const std::string& pat) const;
                ~Node();
        };
};

