#pragma once

#include "definiciones.hpp"

/**
 * @class FMIndex
 * @brief Clase para implementar búsqueda de patrones en textos mediante FM-Index.
 */
class FMIndex {
public:
    /**
     * @brief Busca un patrón en un texto utilizando el algoritmo de FM-Index.
     * 
     * @param texto Texto donde se realizará la búsqueda.
     * @param patron Patrón a buscar en el texto.
     * @return Cantidad de ocurrencias encontradas en el texto.
     */
    static unsigned int buscar(const std::string& texto, const std::string& patron);

private:
        /**
         * @brief Genera todas las variaciones de capitalización de un patrón,
         *        excluyendo el patrón original.
         * 
         * @param patron Cadena patrón original.
         * @return std::unordered_set<std::string> Conjunto con todas las variaciones.
         */
        static std::unordered_set<std::string> generarVariacionesCapitalizacion(const std::string& patron);

    /**
     * @brief Construye el arreglo de sufijos de un texto.
     * 
     * @param texto Texto fuente.
         * @return std::vector<int> Vector con los índices del arreglo de sufijos.
     */
    static std::vector<int> construirArregloSufijos(const std::string& texto);

    /**
     * @brief Construye la transformada de Burrows-Wheeler (BWT) a partir del texto y su arreglo de sufijos.
     * 
     * @param texto Texto original.
     * @param arreglo_sufijos Arreglo de sufijos construido sobre el texto.
         * @return std::string Cadena resultante de la BWT.
     */
    static std::string construirTransformadaBWT(const std::string& texto, const std::vector<int>& arreglo_sufijos);

    /**
     * @brief Construye la tabla de inicio por carácter (tabla C) a partir de la BWT.
     * 
     * @param bwt Cadena BWT.
     * @return Tabla C.
     */
    static std::map<char, int> construirTablaInicioCaracter(const std::string& bwt);

    /**
     * @brief Construye la tabla de ocurrencias (Occ) para cada carácter y posición en la BWT.
     * 
     * @param bwt Cadena BWT.
     * @return Tabla de ocurrencias.
     */
    static std::map<char, std::vector<int>> construirTablaOcurrencias(const std::string& bwt);
};