/**
 * @file class_base.hpp
 * @brief Clase base abstracta para estructuras de búsqueda de patrones.
 * 
 * Define la interfaz común que deben implementar todas las estructuras
 * de datos utilizadas para búsqueda de patrones en texto.
 * 
 * @date 2025
 */

#pragma once

#include "definiciones.hpp"

/**
 * @class BaseStructure
 * @brief Clase base abstracta para estructuras de búsqueda de patrones.
 * 
 * Esta clase define la interfaz común que deben implementar todas las
 * estructuras de datos especializadas en búsqueda de patrones
 * (Suffix Arrays, Suffix Trees, FM-Index).
 * 
 * Utiliza el patrón de diseño Template Method para proporcionar una
 * interfaz uniforme para diferentes algoritmos de búsqueda.
 */
class BaseStructure {
    public:
        /**
         * @brief Destructor virtual por defecto.
         * 
         * Asegura la correcta destrucción de objetos derivados cuando
         * se accede a través de punteros a la clase base.
         */
        virtual ~BaseStructure() = default;
        
        /**
         * @brief Busca un patrón en el texto previamente procesado.
         * 
         * Método abstracto que debe ser implementado por cada estructura
         * derivada para realizar la búsqueda del patrón especificado.
         * 
         * @param patron Patrón a buscar en el texto.
         * @return Número de ocurrencias encontradas del patrón.
         * 
         * @note Este método debe ser implementado por todas las clases derivadas.
         * @note La complejidad temporal depende de la implementación específica.
         */
        virtual unsigned int buscar(const std::string& patron) const = 0;
};