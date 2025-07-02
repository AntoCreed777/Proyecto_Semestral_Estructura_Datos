/**
 * @file definiciones.hpp
 * @brief Definiciones globales, tipos de datos y macros para el proyecto.
 * 
 * Este archivo contiene todas las definiciones fundamentales utilizadas
 * a lo largo del proyecto, incluyendo:
 * - Tipos de datos personalizados y aliases
 * - Macros para optimización y conveniencia
 * - Constantes globales y códigos de color
 * - Funciones de optimización de I/O
 * 
 * Se recomienda incluir este archivo en todos los módulos del proyecto
 * para asegurar consistencia en tipos y definiciones.
 * 
 * @date 2025
 * @note Incluir este archivo al inicio de cada implementación
 */

#pragma once

#include <iostream>
#include <vector>
#include <utility> // Para std::pair
#include <limits>
#include <string>
#include <algorithm>
#include <map> // Para typedef mcharvc

// Includes condicionales para archivos específicos
// <filesystem> - solo para main.cpp, utilities.cpp y medidor.cpp
// <fstream> - solo para archivos que leen/escriben archivos
// <cctype> - solo para robin_karp.cpp
// <map> - solo para fm_index.cpp
// <unordered_set> - solo para fm_index.cpp (comentado)

// Nota: namespace fs = std::filesystem; debe definirse en cada archivo que use <filesystem>

typedef std::vector<int> vc;
typedef std::vector<std::string> vs;
typedef std::pair<int, int> par;
typedef std::map<char, vc> mcharvc;   // Para mapas de char a vector<int> (usado en fm_index)

#define rep(i,n) for(int i=0;i<(int)n;i++)
#define imprimir(mensaje) std::cout << mensaje << std::endl

// ========== ELEMENTOS COMENTADOS (NO UTILIZADOS ACTUALMENTE) ==========
// Descomentar solo si se necesitan en futuras implementaciones:
// #define repx(i,x,n) for(int i=x;i<(int)n;i++)    // Bucle con inicio personalizado
// #define invrep(i,n) for(int i=n;i>=0;i--)        // Bucle inverso
// #define INF std::numeric_limits<int>::max()       // Valor infinito positivo
// #define NEG_INF std::numeric_limits<int>::min()   // Valor infinito negativo

//Constantes para manejar colores
#define ROJO        "\033[0;31m"
#define VERDE       "\033[0;32m"
#define AMARILLO    "\033[0;33m"
#define AZUL        "\033[0;34m"
#define MAGENTA     "\033[1;35m"
#define CIAN        "\033[1;36m"
#define BLANCO      "\033[1;37m"
#define RESET_COLOR "\033[0m"

/**
 * @brief Función para optimizar la entrada/salida
 * 
 * Esta función desactiva la sincronización de C y C++ para mejorar la velocidad de entrada/salida.
 * Además, desactiva el uso de la función std::endl para evitar la sincronización innecesaria.
 * 
 * @note Se recomienda usar esta función al inicio del programa para optimizar el rendimiento.
 * @note En caso de estar testando el código, se recomienda comentar esta función.
 * @warning Esta función puede causar problemas si se mezcla con otras funciones de entrada/salida que dependen de la sincronización.
 */
inline void FunctionOptimization() {
   std::ios_base::sync_with_stdio(false);
   std::cin.tie(0);
}