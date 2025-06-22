#pragma once

#include "definiciones.hpp"
#include <list>
#include <memory>
#include <unordered_map>

class SuffixTrees {
    public:
        /**
         * @brief Busca un patrón en un texto utilizando el algoritmo de Suffix Trees.
         * 
         * @param texto Texto donde se realizará la búsqueda.
         * @param patron Patrón a buscar en el texto.
         * @return cantidad de ocurrencias encontradas en el texto.
         */
        static unsigned int buscar(const std::string& texto, const std::string& patron);

        private:
            class Node {
                public:
                    Node();
                    void insertSuffix(const std::string& suffix, int index);
                    const std::list<int>* search(const std::string& patron) const;
                    ~Node();

                private:
                    std::unique_ptr<std::list<int>> ind;
                    std::vector<std::unique_ptr<Node>> children;
            };
};
