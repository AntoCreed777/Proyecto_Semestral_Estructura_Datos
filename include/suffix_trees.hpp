#pragma once

#include "definiciones.hpp"
#include "class_base.hpp"
#include <list>
#include <memory>
#include <unordered_map>

class SuffixTrees: public BaseStructure {
    public:

        SuffixTrees(const std::string& texto);
        ~SuffixTrees();

        /**
         * @brief Busca un patrón en un texto utilizando el algoritmo de Suffix Trees.
         * 
         * @param texto Texto donde se realizará la búsqueda.
         * @param patron Patrón a buscar en el texto.
         * @return cantidad de ocurrencias encontradas en el texto.
         */
        unsigned int buscar(const std::string& patron) const override;

        private:
            class Node {
                public:
                    Node();
                    void insertSuffix(const std::string& texto, size_t posicion_texto, int index);
                    const std::list<int>* search(const std::string& patron, size_t posicion) const;
                    ~Node();

                private:
                    std::unique_ptr<std::list<int>> ind;
                    std::vector<std::unique_ptr<Node>> children;
            };

            std::unique_ptr<Node> root;
};
