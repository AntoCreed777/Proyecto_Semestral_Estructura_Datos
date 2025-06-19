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
     * @brief Busca un patrón en un archivo utilizando el algoritmo de Robin-Karp.
     * 
     * @param ruta_archivo Ruta del archivo donde se realizará la búsqueda.
     * @param patron Cadena patrón a buscar.
     * @return true Si el patrón se encuentra en el archivo (exacta o por capitalización).
     * @return false Si no se encuentra o hay error al abrir el archivo.
     */
    static bool buscar(const fs::path& ruta_archivo, const std::string& patron);

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
