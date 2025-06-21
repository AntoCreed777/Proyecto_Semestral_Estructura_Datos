#pragma once

#include "definiciones.hpp"

/**
 * @class RobinKarp
 * @brief Implementación del algoritmo de búsqueda de patrones Rabin-Karp
 *        con soporte para variaciones de capitalización.
 */
class RobinKarp {
public:
    /**
     * @brief Busca un patrón en un texto utilizando el algoritmo de Robin-Karp.
     * 
     * @param texto Texto donde se realizará la búsqueda.
     * @param patron Patrón a buscar en el texto.
     * @return true Si el patrón se encuentra en el texto (exacta o por capitalización).
     * @return false Si no se encuentra.
     */
    static bool buscar(const std::string& texto, const std::string& patron);

private:
    /**
     * @brief Genera todas las variaciones de capitalización posibles de un patrón.
     * 
     * @param patron Cadena patrón original.
     * @param posicion Posición actual en la cadena (para recursión).
     * @param buffer_actual Cadena temporal donde se construyen las variaciones.
     * @param variaciones_capitalizacion Vector donde se almacenan todas las variaciones generadas.
     */
    static void generarVariacionesCapitalizacion(
        const std::string& patron,
        int posicion,
        std::string& buffer_actual,
        std::vector<std::string>& variaciones_capitalizacion
    );
};
