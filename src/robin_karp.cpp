#include "../include/definiciones.hpp"
#include "../include/robin_karp.hpp"

/**
 * @brief Genera todas las variaciones de capitalización posibles del patrón,
 *        modificando `buffer_actual` y agregando resultados a `variaciones_capitalizacion`.
 * 
 * @param patron Patrón base.
 * @param posicion Posición actual del caracter a modificar.
 * @param buffer_actual Cadena en proceso de generación.
 * @param variaciones_capitalizacion Lista de resultados generados.
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
 * @brief Ejecuta el algoritmo de búsqueda Rabin-Karp con soporte para variaciones
 *        de capitalización del patrón.
 * 
 * @param ruta_archivo Ruta al archivo donde se realizará la búsqueda.
 * @param patron Patrón a buscar.
 * @return true Si se encontró al menos una coincidencia (exacta o por capitalización).
 * @return false Si no se encontró ninguna coincidencia o hubo error de apertura.
 */
bool RobinKarp::buscar(const fs::path& ruta_archivo, const std::string& patron) {
    const int BASE_HASH = 256;
    const int MODULO_HASH = 101;

    int longitud_patron = static_cast<int>(patron.size());
    if (longitud_patron == 0) return false;

    std::ifstream archivo_entrada(ruta_archivo);
    if (!archivo_entrada.is_open()) return false;

    std::string texto((std::istreambuf_iterator<char>(archivo_entrada)),
                      std::istreambuf_iterator<char>());
    archivo_entrada.close();

    int longitud_texto = static_cast<int>(texto.size());
    if (longitud_texto < longitud_patron) return false;

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

    if (total_coincidencias > 0) {
        std::cout << AMARILLO << "Coincidencias exactas: " << coincidencias_exactas << RESET_COLOR << std::endl;
        std::cout << CIAN << "Coincidencias con mayusculas/minusculas: " << coincidencias_capitalizacion << RESET_COLOR << std::endl;
        std::cout << ROJO << "Total coincidencias: " << total_coincidencias << RESET_COLOR << std::endl;
    }

    return total_coincidencias > 0;
}