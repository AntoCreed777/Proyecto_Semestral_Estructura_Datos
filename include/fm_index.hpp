#pragma once

#include "definiciones.hpp"

/**
 * @class FMIndex
 * @brief Clase para implementar búsqueda de patrones en archivos mediante FM-Index.
 */
class FMIndex {
public:
    /**
     * @brief Busca un patrón en un archivo utilizando el algoritmo FM-Index.
     * 
     * @param ruta_archivo Ruta al archivo donde se realizará la búsqueda.
     * @param patron Cadena que representa el patrón a buscar.
     * @return true Si el patrón se encuentra en el archivo.
     * @return false Si el patrón no se encuentra o hay error al abrir el archivo.
     */
    static bool buscar(const fs::path& ruta_archivo, const std::string& patron);

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
     * @return std::map<char, int> Tabla C.
     */
    static std::map<char, int> construirTablaInicioCaracter(const std::string& bwt);

    /**
     * @brief Construye la tabla de ocurrencias (Occ) para cada carácter y posición en la BWT.
     * 
     * @param bwt Cadena BWT.
     * @return std::map<char, std::vector<int>> Tabla de ocurrencias.
     */
    static std::map<char, std::vector<int>> construirTablaOcurrencias(const std::string& bwt);

    /**
     * @brief Busca si existe un patrón exacto dentro del FM-Index construido.
     * 
     * @param bwt Cadena BWT.
     * @param tabla_inicio_caracter Tabla C.
     * @param tabla_ocurrencias Tabla Occ.
     * @param patron Patrón a buscar.
     * @return true Si existe al menos una coincidencia exacta.
     * @return false Si no existe coincidencia exacta.
     */
    static bool existePatronExactoEnFmIndex(
        const std::string& bwt,
        const std::map<char, int>& tabla_inicio_caracter,
        const std::map<char, std::vector<int>>& tabla_ocurrencias,
        const std::string& patron
    );

    /**
     * @struct ContadorCoincidencias
     * @brief Almacena conteos de coincidencias exactas y variantes de capitalización.
     */
    struct ContadorCoincidencias {
        int coincidencias_exactas = 0;                ///< Coincidencias exactas.
        int coincidencias_capitalizacion = 0;         ///< Coincidencias por variaciones de capitalización.
    };

    /**
     * @brief Cuenta las coincidencias exactas y variantes de capitalización en el texto.
     * 
     * @param texto Texto completo.
     * @param patron Patrón original.
     * @return ContadorCoincidencias Estructura con conteos de coincidencias.
     */
    static ContadorCoincidencias contarCoincidenciasPatron(const std::string& texto, const std::string& patron);
};