/**
 * @file suffix_trees.hpp
 * @brief Implementación de la estructura de datos Suffix Trees para búsqueda de patrones.
 * 
 * Contiene la clase SuffixTrees que implementa un árbol de sufijos
 * para realizar búsquedas muy eficientes de patrones en texto.
 * 
 * @date 2025
 */

#pragma once

#include "definiciones.hpp"
#include "class_base.hpp"
#include <list>
#include <memory>
#include <unordered_map>

/**
 * @class SuffixTrees
 * @brief Implementación de búsqueda de patrones usando Suffix Trees.
 * 
 * Los Suffix Trees son una estructura de datos en forma de árbol que
 * representa todos los sufijos de un texto. Esta implementación utiliza
 * una estructura simplificada donde cada nodo almacena todos los índices
 * de sufijos que pasan por él.
 * 
 * Características de esta implementación:
 * - Cada nodo almacena TODOS los índices de sufijos que pasan por él
 * - Los nodos hijos se indexan por carácter ASCII (256 posiciones)
 * - Construcción simple insertando cada sufijo secuencialmente
 * - Búsqueda recorre el árbol siguiendo los caracteres del patrón
 * 
 * Complejidad temporal:
 * - Construcción: O(n²) donde n es el tamaño del texto
 * - Búsqueda: O(m) donde m es el tamaño del patrón
 * 
 * Complejidad espacial: O(n²) en el peor caso debido a que cada nodo 
 * almacena listas de índices de todos los sufijos que pasan por él
 * 
 * @note Esta NO es la implementación óptima de Ukkonen, sino una versión
 *       más simple de entender pero menos eficiente.
 */
class SuffixTrees: public BaseStructure {
    public:
        /**
         * @brief Constructor que construye el suffix tree para el texto dado.
         * 
         * Construye el árbol insertando cada sufijo del texto secuencialmente.
         * Cada sufijo se inserta como un camino desde la raíz, y cada nodo
         * almacena los índices de TODOS los sufijos que pasan por él.
         * 
         * @param texto Texto fuente para construir el suffix tree.
         * 
         * @note Cada sufijo i se inserta como texto[i..n-1] desde la raíz.
         * @note Cada nodo intermedio almacena todos los índices de sufijos.
         * @note No hay terminador especial, se usan todos los caracteres del texto.
         * 
         * @complexity
         * - Tiempo: O(n²) donde n es el tamaño del texto
         * - Espacio: O(n²) debido a almacenar listas en cada nodo
         */
        SuffixTrees(const std::string& texto);
        
        /**
         * @brief Destructor que libera la memoria del árbol.
         * 
         * Libera recursivamente todos los nodos del árbol de sufijos
         * utilizando la gestión automática de smart pointers.
         */
        ~SuffixTrees();

        /**
         * @brief Busca un patrón en el texto utilizando el suffix tree precomputado.
         * 
         * Realiza una búsqueda dirigida siguiendo los caracteres del patrón
         * desde la raíz. Si logra recorrer todo el patrón, retorna el tamaño
         * de la lista de índices en el nodo final (todos los sufijos que
         * contienen el patrón como prefijo).
         * 
         * @param patron Patrón a buscar en el texto.
         * @return Cantidad de ocurrencias encontradas del patrón.
         * 
         * @note Busca carácter por carácter siguiendo los hijos del árbol.
         * @note Si encuentra el patrón completo, cuenta todos los índices del nodo.
         * @note Es sensible a mayúsculas y minúsculas.
         * 
         * @complexity
         * - Tiempo: O(m) donde m es la longitud del patrón
         * - Espacio: O(1) adicional
         */
        unsigned int buscar(const std::string& patron) const override;

    private:
        /**
         * @class Node
         * @brief Nodo interno del suffix tree.
         * 
         * Representa un nodo en el árbol de sufijos. Cada nodo puede tener
         * múltiples hijos y almacena una lista de índices donde terminan
         * los sufijos que pasan por ese nodo.
         */
        class Node {
            public:
                /**
                 * @brief Constructor por defecto del nodo.
                 * 
                 * Inicializa un nodo con una lista vacía de índices y
                 * un vector de 256 posiciones para los hijos (one per ASCII char).
                 */
                Node();
                
                /**
                 * @brief Inserta un sufijo en el subárbol que comienza en este nodo.
                 * 
                 * Agrega el índice del sufijo a la lista de este nodo, luego
                 * recursivamente inserta el resto del sufijo en el hijo correspondiente
                 * al siguiente carácter. Crea hijos nuevos si es necesario.
                 * 
                 * @param texto Texto completo de referencia.
                 * @param posicion_texto Posición actual dentro del texto.
                 * @param index Índice del sufijo que se está insertando.
                 * 
                 * @note SIEMPRE agrega el índice a la lista del nodo actual.
                 * @note Crea hijo dinámicamente si no existe para el carácter.
                 * @note La recursión termina cuando se acaba el texto.
                 */
                void insertSuffix(const std::string& texto, size_t posicion_texto, int index);
                
                /**
                 * @brief Busca un patrón en el subárbol que comienza en este nodo.
                 * 
                 * Si se ha procesado todo el patrón (posicion == tamaño), retorna
                 * la lista de índices de este nodo. Caso contrario, busca recursivamente
                 * en el hijo correspondiente al siguiente carácter del patrón.
                 * 
                 * @param patron Patrón a buscar.
                 * @param posicion Posición actual dentro del patrón.
                 * @return Puntero a la lista de índices donde aparece el patrón,
                 *         o nullptr si no se encuentra.
                 * 
                 * @note Retorna la lista del nodo actual si se terminó el patrón.
                 * @note Retorna nullptr si no existe el hijo para el siguiente carácter.
                 */
                const std::list<int>* search(const std::string& patron, size_t posicion) const;
                
                /**
                 * @brief Destructor que libera recursivamente la memoria del subárbol.
                 */
                ~Node();

            private:
                /**
                 * @brief Lista de índices de sufijos que pasan por este nodo.
                 * 
                 * Contiene los índices de inicio de todos los sufijos que
                 * pasan por este nodo en su camino desde la raíz.
                 * En las hojas, representa sufijos que terminan aquí.
                 * En nodos internos, representa sufijos que continúan.
                 */
                std::unique_ptr<std::list<int>> ind;
                
                /**
                 * @brief Vector de punteros a nodos hijos indexados por carácter ASCII.
                 * 
                 * Array de 256 posiciones donde children[c] apunta al nodo hijo
                 * que maneja el carácter ASCII 'c'. Utiliza smart pointers
                 * para gestión automática de memoria.
                 */
                std::vector<std::unique_ptr<Node>> children;
        };

        /**
         * @brief Nodo raíz del suffix tree.
         * 
         * Punto de entrada para todas las operaciones en el árbol.
         * Todos los sufijos del texto se insertan como caminos desde esta raíz.
         */
        std::unique_ptr<Node> root;
};
