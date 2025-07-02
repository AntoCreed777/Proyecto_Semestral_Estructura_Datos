/**
 * @file knuth_morris_pratt.hpp
 * @brief Implementación del algoritmo de búsqueda Knuth-Morris-Pratt (KMP).
 * 
 * Contiene la clase KnuthMorrisPratt que implementa el algoritmo KMP,
 * conocido por su búsqueda lineal eficiente sin retroceso en el texto.
 * 
 * @date 2025
 */

#pragma once

#include "definiciones.hpp"

/**
 * @class KnuthMorrisPratt
 * @brief Implementación del algoritmo de búsqueda de patrones Knuth-Morris-Pratt.
 * 
 * El algoritmo KMP utiliza una tabla de fallas (failure function) para evitar
 * comparaciones innecesarias, logrando una búsqueda lineal sin nunca retroceder
 * en el texto de entrada.
 * 
 * Características principales:
 * - Preprocesa el patrón para crear la tabla de fallas
 * - Nunca retrocede en el texto durante la búsqueda
 * - Garantiza complejidad lineal en todos los casos
 * 
 * Complejidad temporal:
 * - Preprocesamiento: O(m) donde m es el tamaño del patrón
 * - Búsqueda: O(n) donde n es el tamaño del texto
 * - Total: O(n + m)
 * 
 * Complejidad espacial: O(m) para la tabla de fallas
 */
class KnuthMorrisPratt {
    public:
        /**
         * @brief Busca un patrón en un texto utilizando el algoritmo de Knuth-Morris-Pratt.
         * 
         * Ejecuta el algoritmo KMP completo: construye la tabla de fallas para el patrón
         * y luego realiza la búsqueda lineal en el texto sin retrocesos.
         * 
         * @param texto Texto donde se realizará la búsqueda.
         * @param patron Patrón a buscar en el texto.
         * @return Cantidad de ocurrencias encontradas del patrón en el texto.
         * 
         * @note Es sensible a mayúsculas y minúsculas.
         * @note Ideal para búsquedas en textos largos con patrones repetitivos.
         * 
         * @complexity
         * - Tiempo: O(n + m) donde n = |texto|, m = |patron|
         * - Espacio: O(m) para la tabla de fallas
         */
        static unsigned int buscar(const std::string& texto, const std::string& patron);

    private:
        /**
         * @brief Calcula la tabla de fallas (failure function) para el patrón.
         * 
         * La tabla de fallas indica cuántas posiciones se puede saltar cuando
         * ocurre una discrepancia, basándose en los prefijos y sufijos del patrón
         * que ya coincidieron.
         * 
         * @param patron Patrón para el cual calcular la tabla de fallas.
         * @return Vector con los valores de la función de falla para cada posición.
         * 
         * @note Elemento i contiene la longitud del prefijo propio más largo
         *       que es también sufijo del patrón[0...i].
         * 
         * @complexity
         * - Tiempo: O(m) donde m es el tamaño del patrón
         * - Espacio: O(m) para el vector resultante
         */
        static vc calcular_tabla_de_saltos(const std::string& patron);
};