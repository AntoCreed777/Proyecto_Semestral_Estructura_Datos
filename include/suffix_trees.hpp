#pragma once

#include "definiciones.hpp"
#include <list>
#include <string>
#include <memory>
#include <unordered_map>

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
class SuffixTrees_VERSION_2 {
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
            std::unordered_map<char, std::unique_ptr<Node>> children;
            std::string contenido;
            std::list<int> ind; // Índices de ocurrencias

            void dividirNodo(size_t pos);

            Node* encontrarHijo(char c) const;

            void moverHijos(std::unordered_map<char, std::unique_ptr<Node>> nuevosHijos);

            void moverIndices(std::list<int> nuevosIndices);

            char contenidoInicial() const;

            void setContenido(const std::string& nuevoContenido);

        public:
            Node() = default;
            ~Node() = default; // La memoria se gestiona automáticamente con std::unique_ptr

            void insertSuffix(const std::string& suffix, int index);
            std::unique_ptr<std::list<int>> search(const std::string& pat) const;
        };
};
