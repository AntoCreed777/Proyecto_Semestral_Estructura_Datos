#include "../include/definiciones.hpp"
#include "../include/robin_karp.hpp"

/**
 * @brief Genera todas las variaciones de capitalización posibles de un patrón.
 * 
 * @param patron Cadena patrón original.
 * @param posicion Posición actual en la cadena (para recursión).
 * @param buffer_actual Cadena temporal donde se construyen las variaciones.
 * @param variaciones_capitalizacion Vector donde se almacenan todas las variaciones generadas.
 */
void RobinKarp::generarVariacionesCapitalizacion(
    const std::string& patron,
    int posicion,
    std::string& buffer_actual,
    std::vector<std::string>& variaciones_capitalizacion)
{
    if (posicion == static_cast<int>(patron.size())) {
        variaciones_capitalizacion.push_back(buffer_actual);
        return;
    }

    char caracter_actual = patron[posicion];
    if (std::isalpha(static_cast<unsigned char>(caracter_actual))) {
        // Rama con minúscula
        buffer_actual[posicion] = std::tolower(static_cast<unsigned char>(caracter_actual));
        generarVariacionesCapitalizacion(patron, posicion + 1, buffer_actual, variaciones_capitalizacion);
        // Rama con mayúscula
        buffer_actual[posicion] = std::toupper(static_cast<unsigned char>(caracter_actual));
        generarVariacionesCapitalizacion(patron, posicion + 1, buffer_actual, variaciones_capitalizacion);
    } else {
        // Carácter no alfabético, se mantiene igual
        buffer_actual[posicion] = caracter_actual;
        generarVariacionesCapitalizacion(patron, posicion + 1, buffer_actual, variaciones_capitalizacion);
    }
}

/**
 * @brief Busca un patrón en un texto utilizando el algoritmo de Robin-Karp.
 * 
 * @param texto Texto donde se realizará la búsqueda.
 * @param patron Patrón a buscar en el texto.
 * @return true Si el patrón se encuentra en el texto (exacta o por capitalización).
 * @return false Si no se encuentra.
 */
unsigned int RobinKarp::buscar(const std::string& texto, const std::string& patron) {
    const int BASE_HASH = 256;
    const int MODULO_HASH = 101;

    int longitud_patron = static_cast<int>(patron.size());
    int longitud_texto = static_cast<int>(texto.size());
    if (longitud_patron == 0 || longitud_texto < longitud_patron) return false;

    /**
     * @brief Cuenta cuántas veces aparece un patrón exacto usando Rabin-Karp.
     * 
     * @param patron_busqueda Patrón a buscar.
     * @return int Número de coincidencias exactas.
     */
    auto contarCoincidenciasPatron = [&](const std::string& patron_busqueda) -> int {
        int hash_patron = 0, hash_ventana = 0, factor_potencia = 1;

        for (int i = 0; i < longitud_patron - 1; i++) {
            factor_potencia = (factor_potencia * BASE_HASH) % MODULO_HASH;
        }

        for (int i = 0; i < longitud_patron; i++) {
            hash_patron = (BASE_HASH * hash_patron + patron_busqueda[i]) % MODULO_HASH;
            hash_ventana = (BASE_HASH * hash_ventana + texto[i]) % MODULO_HASH;
        }

        int coincidencias_exactas = 0;
        for (int i = 0; i <= longitud_texto - longitud_patron; i++) {
            if (hash_patron == hash_ventana) {
                if (texto.substr(i, longitud_patron) == patron_busqueda) {
                    coincidencias_exactas++;
                }
            }

            if (i < longitud_texto - longitud_patron) {
                hash_ventana = (BASE_HASH * (hash_ventana - texto[i] * factor_potencia) + texto[i + longitud_patron]) % MODULO_HASH;
                if (hash_ventana < 0) hash_ventana += MODULO_HASH;
            }
        }

        return coincidencias_exactas;
    };

    // Coincidencias exactas
    int coincidencias_exactas = contarCoincidenciasPatron(patron);

    // Generar todas las variaciones de capitalización
    std::vector<std::string> variaciones_capitalizacion;
    std::string buffer_actual = patron;
    generarVariacionesCapitalizacion(patron, 0, buffer_actual, variaciones_capitalizacion);

    // Coincidencias por capitalización (excluyendo el patrón original)
    int coincidencias_capitalizacion = 0;
    for (const std::string& variante : variaciones_capitalizacion) {
        if (variante != patron) {
            coincidencias_capitalizacion += contarCoincidenciasPatron(variante);
        }
    }

    int total_coincidencias = coincidencias_exactas + coincidencias_capitalizacion;

    /*
    if (total_coincidencias > 0) {
        std::cout << AMARILLO << "Coincidencias exactas: " << coincidencias_exactas << RESET_COLOR << std::endl;
        std::cout << CIAN << "Coincidencias con mayusculas/minusculas: " << coincidencias_capitalizacion << RESET_COLOR << std::endl;
        std::cout << ROJO << "Total coincidencias: " << total_coincidencias << RESET_COLOR << std::endl;
    }
    */

    return total_coincidencias;
}