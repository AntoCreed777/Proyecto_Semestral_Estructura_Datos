/**
 * @file medidor.hpp
 * @brief Sistema de medición de rendimiento para algoritmos de búsqueda de patrones.
 * 
 * Proporciona funciones para medir tiempo de ejecución, uso de memoria y
 * rendimiento general de diferentes algoritmos y estructuras de datos
 * utilizados en búsqueda de patrones. Incluye exportación de resultados a JSON.
 * 
 * @date 2025
 */

#pragma once

#include "definiciones.hpp"
#include "json.hpp"
#include "fm_index.hpp"
#include "suffix_arrays.hpp"
#include "suffix_trees.hpp"
#include "robin_karp.hpp"
#include "boyer_moore.hpp"
#include "knuth_morris_pratt.hpp"

#include <chrono>
#include <functional>

/**
 * @brief Obtiene la memoria usada actualmente por el proceso en KB.
 * @return Memoria usada en KB.
 */
size_t getMemoryUsage();

/**
 * @brief Obtiene la memoria máxima usada por el proceso en KB.
 * @return Memoria máxima usada en KB.
 */
size_t obtenerMemoriaMaximaKb();

/**
 * @brief Inicia un temporizador de alta resolución.
 * @return Punto de tiempo inicial.
 */
std::chrono::high_resolution_clock::time_point iniciarTimer();

/**
 * @brief Detiene el temporizador de alta resolución.
 * @return Punto de tiempo final.
 */
std::chrono::high_resolution_clock::time_point detenerTimer();

/**
 * @brief Calcula la duración en milisegundos entre dos puntos de tiempo.
 * @param inicio Punto de tiempo inicial.
 * @param fin Punto de tiempo final.
 * @return Duración en milisegundos.
 */
std::chrono::duration<double, std::milli> calcularDuracion(
    std::chrono::high_resolution_clock::time_point inicio,
    std::chrono::high_resolution_clock::time_point fin
);

/**
 * @brief Inicia la medición para un algoritmo y patrón específicos.
 * @param nombre Nombre del algoritmo o estructura.
 * @param tipo Tipo de algoritmo o estructura.
 * @param patron Patrón que se busca.
 */
void iniciarMedicion(const std::string& nombre, const std::string& tipo, const std::string& patron);

/**
 * @brief Registra la memoria y tiempo usados durante la construcción de la estructura.
 * @param mem_inicio Memoria antes de la construcción en KB.
 * @param mem_fin Memoria después de la construcción en KB.
 * @param duracion Duración de la construcción en milisegundos.
 */
void registrarConstruccion(size_t mem_inicio, size_t mem_fin, std::chrono::duration<double, std::milli> duracion);

/**
 * @brief Registra la memoria, tiempo usados y ocurrencias durante la búsqueda.
 * @param mem_inicio Memoria antes de la búsqueda en KB.
 * @param mem_fin Memoria después de la búsqueda en KB.
 * @param duracion Duración de la búsqueda en milisegundos.
 * @param ocurrencias Cantidad de ocurrencias encontradas.
 */
void registrarBusqueda(size_t mem_inicio, size_t mem_fin, std::chrono::duration<double, std::milli> duracion, unsigned int ocurrencias);

/**
 * @brief Guarda el resultado actual en el arreglo de resultados.
 */
void guardarResultado();

/**
 * @brief Guarda todos los resultados en un archivo JSON y muestra la memoria total acumulada.
 * @param nombre_archivo Nombre del archivo en que se buscara el patron
 * @param patron Patrón que se buscó.
 * @param ocurrencias Total de ocurrencias encontradas.
 * @param memoria_maxima_kb Memoria máxima usada (no usada en esta versión, pero se mantiene el parámetro).
 */
void guardarResultadosFinales(const std::string& nombre_archivo, const std::string& patron, unsigned int ocurrencias, size_t memoria_maxima_kb);

/**
 * @brief Ejecuta y mide un algoritmo de búsqueda.
 * @param nombre Nombre del algoritmo.
 * @param func Función de búsqueda que recibe texto y patrón y devuelve ocurrencias.
 * @param texto Texto donde buscar.
 * @param patron Patrón a buscar.
 * @return Cantidad de ocurrencias encontradas.
 */
unsigned int medirAlgoritmo(const std::string& nombre, unsigned int(*func)(const std::string&, const std::string&), 
                            const std::string& texto, const std::string& patron);

/**
 * @brief Ejecuta y mide la construcción y búsqueda de una estructura.
 * @param nombre Nombre de la estructura.
 * @param constructor Función para construir la estructura a partir del texto.
 * @param texto Texto donde construir la estructura.
 * @param patron Patrón a buscar.
 * @return Cantidad de ocurrencias encontradas.
 */
unsigned int medirEstructura(const std::string& nombre, std::function<std::unique_ptr<BaseStructure>(const std::string&)> constructor,
                             const std::string& texto, const std::string& patron);