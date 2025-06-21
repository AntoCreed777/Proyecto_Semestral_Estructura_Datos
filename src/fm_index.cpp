#include "../include/definiciones.hpp"
#include "../include/fm_index.hpp"

/**
 * @brief Genera todas las combinaciones posibles del patrón con variaciones
 *        de mayúsculas y minúsculas, excluyendo el patrón original.
 */
std::unordered_set<std::string> FMIndex::generarVariacionesCapitalizacion(const std::string& patron) {
    std::unordered_set<std::string> variaciones;
    int longitud = static_cast<int>(patron.length());
    int total_variaciones = 1 << longitud;

    for (int mascara = 0; mascara < total_variaciones; ++mascara) {
        std::string variacion;
        variacion.reserve(longitud);
        for (int posicion = 0; posicion < longitud; ++posicion) {
            bool es_mayuscula = (mascara >> posicion) & 1;
            variacion += es_mayuscula ? static_cast<char>(std::toupper(patron[posicion]))
                                      : static_cast<char>(std::tolower(patron[posicion]));
        }
        if (variacion != patron) {
            variaciones.insert(variacion);
        }
    }
    return variaciones;
}

/**
 * @brief Construye el arreglo de sufijos del texto.
 */
std::vector<int> FMIndex::construirArregloSufijos(const std::string& texto) {
    int longitud = static_cast<int>(texto.size());
    std::vector<int> arreglo_sufijos(longitud);
    for (int i = 0; i < longitud; i++) {
        arreglo_sufijos[i] = i;
    }

    std::sort(arreglo_sufijos.begin(), arreglo_sufijos.end(),
        [&](int a, int b) {
            int comparacion_longitud = longitud - std::max(a, b);
            return texto.compare(a, comparacion_longitud, texto, b, comparacion_longitud) < 0;
        });

    return arreglo_sufijos;
}

/**
 * @brief Construye la Burrows-Wheeler Transform (BWT) desde el arreglo de sufijos.
 */
std::string FMIndex::construirTransformadaBWT(const std::string& texto, const std::vector<int>& arreglo_sufijos) {
    std::string bwt(texto.size(), '$');
    for (size_t i = 0; i < arreglo_sufijos.size(); ++i) {
        int indice_sufijo = arreglo_sufijos[i];
        bwt[i] = (indice_sufijo == 0) ? texto.back() : texto[indice_sufijo - 1];
    }
    return bwt;
}

/**
 * @brief Construye la tabla de inicio por carácter (tabla C).
 */
std::map<char, int> FMIndex::construirTablaInicioCaracter(const std::string& bwt) {
    std::map<char, int> tabla_inicio_caracter;
    std::string caracteres_unicos = bwt;

    std::sort(caracteres_unicos.begin(), caracteres_unicos.end());
    caracteres_unicos.erase(std::unique(caracteres_unicos.begin(), caracteres_unicos.end()), caracteres_unicos.end());

    int acumulador = 0;
    for (char caracter : caracteres_unicos) {
        tabla_inicio_caracter[caracter] = acumulador;
        acumulador += static_cast<int>(std::count(bwt.begin(), bwt.end(), caracter));
    }
    return tabla_inicio_caracter;
}

/**
 * @brief Construye la tabla de ocurrencias acumuladas por carácter.
 */
std::map<char, std::vector<int>> FMIndex::construirTablaOcurrencias(const std::string& bwt) {
    std::map<char, std::vector<int>> tabla_ocurrencias;

    for (char caracter : bwt) {
        if (!tabla_ocurrencias.count(caracter)) {
            tabla_ocurrencias[caracter] = std::vector<int>(bwt.size(), 0);
        }
    }

    for (size_t i = 0; i < bwt.size(); ++i) {
        char caracter_actual = bwt[i];
        for (auto& par : tabla_ocurrencias) {
            char clave = par.first;
            std::vector<int>& conteos = par.second;
            conteos[i] = (i > 0 ? conteos[i - 1] : 0) + (clave == caracter_actual ? 1 : 0);
        }
    }

    return tabla_ocurrencias;
}

/**
 * @brief Verifica si un patrón existe exactamente en el índice FM.
 */
bool FMIndex::existePatronExactoEnFmIndex(
    const std::string& bwt,
    const std::map<char, int>& tabla_inicio_caracter,
    const std::map<char, std::vector<int>>& tabla_ocurrencias,
    const std::string& patron
) {
    if (patron.empty()) return false;

    int posicion = static_cast<int>(patron.size()) - 1;
    char caracter_actual = patron[posicion];

    if (!tabla_inicio_caracter.count(caracter_actual)) return false;

    int inicio = tabla_inicio_caracter.at(caracter_actual) + 1;
    int fin = tabla_inicio_caracter.at(caracter_actual) + (tabla_ocurrencias.count(caracter_actual) ? tabla_ocurrencias.at(caracter_actual).back() : 0);

    while (inicio <= fin && posicion >= 1) {
        caracter_actual = patron[posicion - 1];
        if (!tabla_inicio_caracter.count(caracter_actual)) return false;

        int inicio_caracter = tabla_inicio_caracter.at(caracter_actual);
        inicio = inicio_caracter + (inicio > 1 ? tabla_ocurrencias.at(caracter_actual)[inicio - 2] : 0) + 1;
        fin = inicio_caracter + tabla_ocurrencias.at(caracter_actual)[fin - 1];
        --posicion;
    }

    return fin >= inicio;
}

/**
 * @brief Estructura para almacenar cantidad de coincidencias encontradas.
 */
FMIndex::ContadorCoincidencias FMIndex::contarCoincidenciasPatron(const std::string& texto, const std::string& patron) {
    ContadorCoincidencias contador;
    size_t longitud_patron = patron.size();
    size_t longitud_texto = texto.size();

    if (longitud_patron == 0 || longitud_texto < longitud_patron) return contador;

    auto variaciones_capitalizacion = generarVariacionesCapitalizacion(patron);

    for (size_t i = 0; i <= longitud_texto - longitud_patron; ++i) {
        std::string subcadena(texto.begin() + i, texto.begin() + i + longitud_patron);
        if (subcadena == patron) {
            contador.coincidencias_exactas++;
        } else if (variaciones_capitalizacion.count(subcadena)) {
            contador.coincidencias_capitalizacion++;
        }
    }

    return contador;
}

/**
 * @brief Ejecuta el algoritmo FM-Index sobre el texto dado para buscar el patrón.
 */
unsigned int FMIndex::buscar(const std::string& texto, const std::string& patron) {
    std::string texto_aux = texto + '$';

    auto arreglo_sufijos = construirArregloSufijos(texto_aux);
    auto bwt = construirTransformadaBWT(texto_aux, arreglo_sufijos);
    auto tabla_inicio_caracter = construirTablaInicioCaracter(bwt);
    auto tabla_ocurrencias = construirTablaOcurrencias(bwt);
    ContadorCoincidencias coincidencias = contarCoincidenciasPatron(texto_aux, patron);
    const int total_coincidencias = coincidencias.coincidencias_exactas + coincidencias.coincidencias_capitalizacion;

    if (total_coincidencias > 0) {
        std::cout << AMARILLO << "Coincidencias exactas: " << coincidencias.coincidencias_exactas << RESET_COLOR << std::endl;
        std::cout << CIAN << "Coincidencias con mayusculas/minusculas: " << coincidencias.coincidencias_capitalizacion << RESET_COLOR << std::endl;
        std::cout << ROJO << "Total coincidencias: " << total_coincidencias << RESET_COLOR << std::endl;
    }

    return total_coincidencias;
}