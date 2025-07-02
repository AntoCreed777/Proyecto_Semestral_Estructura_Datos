/**
 * @file suffix_arrays.hpp
 * @brief Implementación de la estructura de datos Suffix Arrays para búsqueda de patrones.
 * 
 * Contiene la clase SuffixArrays que implementa una estructura de datos
 * basada en arrays de sufijos para realizar búsquedas eficientes de patrones.
 * 
 * @date 2025
 */

#pragma once

#include "definiciones.hpp"
#include "class_base.hpp"

/**
 * @class SuffixArrays
 * @brief Implementación de búsqueda de patrones usando Suffix Arrays.
 * 
 * Los Suffix Arrays son una estructura de datos que almacena todos los sufijos
 * de una cadena de texto ordenados lexicográficamente. Esta implementación
 * permite búsquedas eficientes de patrones en el texto preprocesado.
 * 
 * Características principales:
 * - Preprocesa el texto una vez en el constructor
 * - Permite múltiples búsquedas eficientes
 * - Utiliza ordenamiento lexicográfico de sufijos
 * - Hereda de BaseStructure para interfaz uniforme
 * Complejidad temporal:
 * - Construcción: O(n² log n) donde n es el tamaño del texto (por ordenamiento de strings)
 * - Búsqueda: O(log n + k) donde k es el número de ocurrencias
 * 
 * Complejidad espacial: O(n²) para almacenar todos los sufijos como strings completos
 * 
 * @note Esta implementación almacena los sufijos como strings completos,
 *       lo que puede ser memory-intensive para textos largos.
 */
class SuffixArrays: public BaseStructure {
    public:
        /**
         * @brief Constructor que preprocesa el texto para crear el array de sufijos.
         * 
         * Genera todos los sufijos del texto de entrada y los ordena
         * lexicográficamente para permitir búsquedas eficientes posteriores.
         * 
         * @param texto Texto fuente del cual extraer y ordenar los sufijos.
         * 
         * @note El texto se procesa completamente en el constructor.
         * @note Los sufijos se almacenan como strings completos ordenados.
         * 
         * @complexity
         * - Tiempo: O(n² log n) por el ordenamiento de strings
         * - Espacio: O(n²) para almacenar todos los sufijos
         */
        SuffixArrays(const std::string& texto);
        
        /**
         * @brief Busca un patrón en el texto utilizando el array de sufijos precomputado.
         * 
         * Realiza una búsqueda binaria en el array ordenado de sufijos para
         * encontrar todas las ocurrencias del patrón especificado.
         * 
         * @param patron Patrón a buscar en el texto.
         * @return Cantidad de ocurrencias encontradas del patrón.
         * 
         * @note Utiliza búsqueda binaria para eficiencia.
         * @note Es sensible a mayúsculas y minúsculas.
         * 
         * @complexity
         * - Tiempo: O(m log n) donde m = |patron|, n = número de sufijos
         * - Espacio: O(1) adicional
         */
        unsigned int buscar(const std::string& patron) const override;

    private:
        /**
         * @brief Vector que almacena todos los sufijos del texto ordenados lexicográficamente.
         * 
         * Cada elemento es un sufijo completo del texto original, ordenado
         * alfabéticamente para permitir búsquedas binarias eficientes.
         */
        std::vector<std::string> sufijos;
};
