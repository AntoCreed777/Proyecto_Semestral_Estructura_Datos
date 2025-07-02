/**
 * @file utilities.hpp
 * @brief Funciones utilitarias para la entrada de datos del usuario.
 * 
 * Este archivo contiene funciones auxiliares para solicitar y validar
 * la entrada del usuario, específicamente para texto y patrones de búsqueda.
 * 
 * @date 2025
 */

#pragma once

#include "definiciones.hpp"

/**
 * @brief Solicita al usuario que ingrese un texto y un patrón.
 * 
 * Esta función solicita un archivo de texto del cual se leera su contenido y un patrón a utilizar
 * en los algoritmos de búsqueda.
 * 
 * @param[out] texto Referencia donde se almacenará el texto leido del un archivo.
 * @param[out] patron Referencia donde se almacenará el patrón ingresado.
 * 
 * @note Esta función modifica los parámetros pasados por referencia.
 */
void input(std::string& texto, std::string& patron);

/**
 * @brief Solicita al usuario que ingrese un patrón de búsqueda.
 * 
 * Función auxiliar que permite al usuario ingresar un patrón específico
 * para realizar búsquedas. Incluye validación básica de entrada.
 * 
 * @param[out] patron Referencia donde se almacenará el patrón ingresado.
 * 
 * @note El patrón devuelto no sera una cadena vacía.
 * @note Esta función puede solicitar reingresar el patrón si está vacío.
 */
void solicitarPatron(std::string& patron);