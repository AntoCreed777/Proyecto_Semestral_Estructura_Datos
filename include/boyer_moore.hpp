/**
 * @file boyer_moore.hpp
 * @brief Implementación del algoritmo de búsqueda Boyer-Moore.
 * 
 * Contiene la clase BoyerMoore que implementa el algoritmo de búsqueda
 * de patrones Boyer-Moore, conocido por su eficiencia en textos largos
 * y patrones de tamaño considerable.
 * 
 * @date 2025
 */

#pragma once

#include "definiciones.hpp"

/**
 * @class BoyerMoore
 * @brief Implementación del algoritmo de búsqueda de patrones Boyer-Moore.
 * 
 * El algoritmo Boyer-Moore es uno de los algoritmos de búsqueda de cadenas
 * más eficientes, especialmente para patrones largos. Esta implementación
 * utiliza una versión simplificada que emplea principalmente:
 * - Bad Character Rule simplificada: salta caracteres basándose en discrepancias
 * - Comparación de derecha a izquierda en el patrón
 * 
 * Complejidad temporal:
 * - Mejor caso: O(n/m) donde n es el tamaño del texto y m del patrón
 * - Caso promedio: O(n)
 * - Peor caso: O(n*m)
 * 
 * Complejidad espacial: O(1) - no usa tablas de pre-cómputo extensas
 */
class BoyerMoore {
    public:
        /**
         * @brief Busca un patrón en un texto utilizando el algoritmo de Boyer-Moore.
         * 
         * Este método implementa una versión simplificada del algoritmo Boyer-Moore.
         * Compara el patrón de derecha a izquierda y usa una heurística básica
         * de salto cuando encuentra discrepancias.
         * 
         * @param texto Texto donde se realizará la búsqueda.
         * @param patron Patrón a buscar en el texto.
         * @return Cantidad de ocurrencias encontradas del patrón en el texto.
         * 
         * @note Implementación simplificada sin tablas de pre-cómputo completas.
         * @note Es sensible a mayúsculas y minúsculas.
         * @note Más eficiente con patrones largos que con cortos.
         * 
         * @complexity
         * - Tiempo: O(n) en promedio, O(n*m) en el peor caso
         * - Espacio: O(1) sin tablas de pre-cómputo
         */
        static unsigned int buscar(const std::string& texto, const std::string& patron);
};
