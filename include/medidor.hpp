#ifndef MEDIDOR_HPP
#define MEDIDOR_HPP

#include "definiciones.hpp"
#include "json.hpp"
#include "fm_index.hpp"
#include "suffix_arrays.hpp"
#include "suffix_trees.hpp"
#include "robin_karp.hpp"
#include "boyer_moore.hpp"
#include "knuth_morris_pratt.hpp"

#include <string>
#include <chrono>
#include <functional>
#include <memory>

/**
 * @brief Obtiene la memoria usada actualmente por el proceso en KB.
 * @return Memoria usada en KB.
 */
size_t get_memory_usage();

/**
 * @brief Obtiene la memoria máxima usada por el proceso en KB.
 * @return Memoria máxima usada en KB.
 */
size_t obtener_memoria_maxima_kb();

/**
 * @brief Inicia un temporizador de alta resolución.
 * @return Punto de tiempo inicial.
 */
std::chrono::high_resolution_clock::time_point iniciar_timer();

/**
 * @brief Detiene el temporizador de alta resolución.
 * @return Punto de tiempo final.
 */
std::chrono::high_resolution_clock::time_point detener_timer();

/**
 * @brief Calcula la duración en milisegundos entre dos puntos de tiempo.
 * @param inicio Punto de tiempo inicial.
 * @param fin Punto de tiempo final.
 * @return Duración en milisegundos.
 */
std::chrono::duration<double, std::milli> calcular_duracion(
    std::chrono::high_resolution_clock::time_point inicio,
    std::chrono::high_resolution_clock::time_point fin
);

/**
 * @brief Inicia la medición para un algoritmo y patrón específicos.
 * @param nombre Nombre del algoritmo o estructura.
 * @param tipo Tipo de algoritmo o estructura.
 * @param patron Patrón que se busca.
 */
void iniciar_medicion(const std::string& nombre, const std::string& tipo, const std::string& patron);

/**
 * @brief Registra la memoria y tiempo usados durante la construcción de la estructura.
 * @param mem_inicio Memoria antes de la construcción en KB.
 * @param mem_fin Memoria después de la construcción en KB.
 * @param duracion Duración de la construcción en milisegundos.
 */
void registrar_construccion(size_t mem_inicio, size_t mem_fin, std::chrono::duration<double, std::milli> duracion);

/**
 * @brief Registra la memoria, tiempo usados y ocurrencias durante la búsqueda.
 * @param mem_inicio Memoria antes de la búsqueda en KB.
 * @param mem_fin Memoria después de la búsqueda en KB.
 * @param duracion Duración de la búsqueda en milisegundos.
 * @param ocurrencias Cantidad de ocurrencias encontradas.
 */
void registrar_busqueda(size_t mem_inicio, size_t mem_fin, std::chrono::duration<double, std::milli> duracion, unsigned int ocurrencias);

/**
 * @brief Guarda el resultado actual en el arreglo de resultados.
 */
void guardar_resultado();

/**
 * @brief Guarda todos los resultados en un archivo JSON y muestra la memoria total acumulada.
 * @param patron Patrón que se buscó.
 * @param ocurrencias Total de ocurrencias encontradas.
 * @param memoria_maxima_kb Memoria máxima usada (no usada en esta versión, pero se mantiene el parámetro).
 */
void guardar_resultados_finales(const std::string& patron, unsigned int ocurrencias, size_t memoria_maxima_kb);

/**
 * @brief Ejecuta y mide un algoritmo de búsqueda.
 * @param nombre Nombre del algoritmo.
 * @param func Función de búsqueda que recibe texto y patrón y devuelve ocurrencias.
 * @param texto Texto donde buscar.
 * @param patron Patrón a buscar.
 * @return Cantidad de ocurrencias encontradas.
 */
unsigned int medir_algoritmo(const std::string& nombre, unsigned int(*func)(const std::string&, const std::string&), 
                            const std::string& texto, const std::string& patron);

/**
 * @brief Ejecuta y mide la construcción y búsqueda de una estructura.
 * @param nombre Nombre de la estructura.
 * @param constructor Función para construir la estructura a partir del texto.
 * @param texto Texto donde construir la estructura.
 * @param patron Patrón a buscar.
 * @return Cantidad de ocurrencias encontradas.
 */
unsigned int medir_estructura(const std::string& nombre, std::function<std::unique_ptr<BaseStructure>(const std::string&)> constructor,
                             const std::string& texto, const std::string& patron);

#endif