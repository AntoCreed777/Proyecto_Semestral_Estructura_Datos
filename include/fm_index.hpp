/**
 * @file fm_index.hpp
 * @brief Implementación de FM-Index para búsqueda eficiente de patrones.
 * 
 * Contiene la clase FMIndex que implementa el algoritmo FM-Index,
 * una estructura de datos avanzada que combina la transformada de
 * Burrows-Wheeler con arrays de sufijos para búsquedas muy eficientes.
 * 
 * @date 2025
 */

#pragma once

#include "definiciones.hpp"
#include "class_base.hpp"

#include <unordered_set>
#include <map>

/**
 * @class FMIndex
 * @brief Implementación de búsqueda de patrones mediante FM-Index con soporte
 *        para variaciones de capitalización.
 * 
 * FM-Index es una estructura de datos altamente eficiente que combina:
 * - Transformada de Burrows-Wheeler (BWT) para compresión
 * - Array de sufijos para indexación
 * - Tablas auxiliares (C table y Occ table) para búsqueda rápida
 * 
 * Características de esta implementación:
 * - Búsqueda backward (de derecha a izquierda en el patrón)
 * - Búsqueda solo exacta (variaciones de capitalización comentadas)
 * - Muy eficiente en memoria para textos largos
 * - Construcción completa de BWT y tablas auxiliares
 * 
 * Complejidad temporal:
 * - Construcción: O(n log n) donde n es el tamaño del texto
 * - Búsqueda: O(m) donde m es el tamaño del patrón
 * 
 * Complejidad espacial: O(n) para las estructuras principales
 * 
 * @note Las variaciones de capitalización están comentadas en la implementación actual.
 */
class FMIndex : public BaseStructure {
public:
    /**
     * @brief Constructor que inicializa la estructura FM-Index con el texto.
     * 
     * @param texto Texto donde se construirá el índice.
     */
    FMIndex(const std::string& texto);  // Constructor

    /**
     * @brief Busca un patrón en el texto previamente procesado.
     * 
     * @param patron Patrón a buscar.
     * @return Cantidad de ocurrencias encontradas.
     */
    unsigned int buscar(const std::string& patron) const override;  // Override

    /**
     * @brief Versión estática de búsqueda para uso directo sin construir instancia.
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
    std::unordered_set<std::string> generarVariacionesCapitalizacion(const std::string& patron) const;

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

    // Miembros de instancia
    std::string texto_;
    std::vector<int> arreglo_sufijos_;
    std::string bwt_;
    std::map<char, int> tabla_inicio_caracter_;
    std::map<char, std::vector<int>> tabla_ocurrencias_;
};
