#include "../include/definiciones.hpp"
#include "../include/fm_index.hpp"

#include <map>
#include <unordered_set>

/**
 * @brief Constructor que inicializa la estructura FM-Index con el texto dado.
 *        Utiliza el texto para construir las estructuras necesarias (BWT, tablas).
 */
FMIndex::FMIndex(const std::string& texto) : texto_(texto) {
    arreglo_sufijos_ = construirArregloSufijos(texto_);
    bwt_ = construirTransformadaBWT(texto_, arreglo_sufijos_);
    tabla_inicio_caracter_ = construirTablaInicioCaracter(bwt_);
    tabla_ocurrencias_ = construirTablaOcurrencias(bwt_);
}

/**
 * @brief Uso de FM-Index para contar cuántas veces aparece el patrón
 *        en el texto preprocesado. Este método es no estático.
 */
unsigned int FMIndex::buscar(const std::string& patron) const {
    if (patron.empty()) return 0;

    int i = static_cast<int>(patron.size()) - 1;
    char c = patron[i];

    if (!tabla_inicio_caracter_.count(c)) return 0;

    int inicio = tabla_inicio_caracter_.at(c);
    int fin = inicio + tabla_ocurrencias_.at(c).back();

    while (i > 0 && inicio < fin) {
        i--;
        c = patron[i];
        if (!tabla_inicio_caracter_.count(c)) return 0;

        int nuevo_inicio = tabla_inicio_caracter_.at(c) + (inicio > 0 ? tabla_ocurrencias_.at(c)[inicio - 1] : 0);
        int nuevo_fin = tabla_inicio_caracter_.at(c) + tabla_ocurrencias_.at(c)[fin - 1];

        inicio = nuevo_inicio;
        fin = nuevo_fin;
    }

    unsigned int coincidencias = (inicio < fin) ? (fin - inicio) : 0;
    return coincidencias;
}

/**
 * @brief Genera todas las combinaciones posibles del patrón con variaciones
 *        de mayúsculas y minúsculas, excluyendo el patrón original.
 */
std::unordered_set<std::string> FMIndex::generarVariacionesCapitalizacion(const std::string& patron) const {
    std::unordered_set<std::string> variaciones;
    // int longitud = static_cast<int>(patron.length());
    // int total_variaciones = 1 << longitud;

    // for (int mascara = 0; mascara < total_variaciones; ++mascara) {
    //     std::string variacion;
    //     variacion.reserve(longitud);
    //     for (int posicion = 0; posicion < longitud; ++posicion) {
    //         bool es_mayuscula = (mascara >> posicion) & 1;
    //         variacion += es_mayuscula ? static_cast<char>(std::toupper(patron[posicion]))
    //                                   : static_cast<char>(std::tolower(patron[posicion]));
    //     }
    //     if (variacion != patron) {
    //         variaciones.insert(variacion);
    //     }
    // }
    return variaciones;
}

/**
 * @brief Construye el arreglo de sufijos del texto.
 */
vc FMIndex::construirArregloSufijos(const std::string& texto) {
    int longitud = static_cast<int>(texto.size());
    vc arreglo_sufijos(longitud);
    rep(i, longitud) {
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
 * @brief Construye la BWT (Burrows-Wheeler Transform) desde el arreglo de sufijos.
 */
std::string FMIndex::construirTransformadaBWT(const std::string& texto, const vc& arreglo_sufijos) {
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
mcharvc FMIndex::construirTablaOcurrencias(const std::string& bwt) {
    mcharvc tabla_ocurrencias;

    for (char caracter : bwt) {
        if (!tabla_ocurrencias.count(caracter)) {
            tabla_ocurrencias[caracter] = vc(bwt.size(), 0);
        }
    }

    for (size_t i = 0; i < bwt.size(); ++i) {
        char caracter_actual = bwt[i];
        for (auto& par : tabla_ocurrencias) {
            char clave = par.first;
            vc& conteos = par.second;
            conteos[i] = (i > 0 ? conteos[i - 1] : 0) + (clave == caracter_actual ? 1 : 0);
        }
    }

    return tabla_ocurrencias;
}

/**
 * @brief Método estático alternativo que permite buscar sin construir la clase.
 * 
 * Esta función realiza todo el proceso (construcción de BWT, tablas, etc.)
 * desde cero en cada llamada. Es útil para búsquedas puntuales cuando no se
 * necesita reutilizar estructuras ni mantener estado.
 * 
 * Se mantiene junto al constructor y al método no estático para dar flexibilidad:
 * - El método estático es ideal para búsquedas únicas o pruebas rápidas.
 * - La versión con constructor es más eficiente para múltiples búsquedas
 *   sobre el mismo texto, ya que evita reprocesar todo cada vez.
 */
unsigned int FMIndex::buscar(const std::string& texto, const std::string& patron) {
    if (patron.empty()) return 0;

    auto arreglo_sufijos = construirArregloSufijos(texto);
    auto bwt = construirTransformadaBWT(texto, arreglo_sufijos);
    auto tabla_inicio_caracter = construirTablaInicioCaracter(bwt);
    auto tabla_ocurrencias = construirTablaOcurrencias(bwt);

    int i = static_cast<int>(patron.size()) - 1;
    char c = patron[i];

    if (!tabla_inicio_caracter.count(c)) return 0;

    int inicio = tabla_inicio_caracter[c];
    int fin = inicio + tabla_ocurrencias[c].back();

    while (i > 0 && inicio < fin) {
        i--;
        c = patron[i];
        if (!tabla_inicio_caracter.count(c)) return 0;

        int nuevo_inicio = tabla_inicio_caracter[c] + (inicio > 0 ? tabla_ocurrencias[c][inicio - 1] : 0);
        int nuevo_fin = tabla_inicio_caracter[c] + tabla_ocurrencias[c][fin - 1];

        inicio = nuevo_inicio;
        fin = nuevo_fin;
    }

    unsigned int coincidencias = (inicio < fin) ? (fin - inicio) : 0;

    /*
    // Si se desea considerar también coincidencias con diferentes combinaciones
    // de mayúsculas y minúsculas (por ejemplo, "Casa", "CASA", "cAsA", etc.),
    // descomenta esta sección.

    auto variaciones = generarVariacionesCapitalizacion(patron);
    for (const auto& variante : variaciones) {
        if (variante.empty()) continue;

        int j = static_cast<int>(variante.size()) - 1;
        char ch = variante[j];

        if (!tabla_inicio_caracter.count(ch)) continue;

        int ini = tabla_inicio_caracter[ch];
        int fin2 = ini + tabla_ocurrencias[ch].back();

        while (j > 0 && ini < fin2) {
            j--;
            ch = variante[j];
            if (!tabla_inicio_caracter.count(ch)) {
                ini = fin2 = 0;
                break;
            }

            int nuevo_ini = tabla_inicio_caracter[ch] + (ini > 0 ? tabla_ocurrencias[ch][ini - 1] : 0);
            int nuevo_fin = tabla_inicio_caracter[ch] + tabla_ocurrencias[ch][fin2 - 1];

            ini = nuevo_ini;
            fin2 = nuevo_fin;
        }

        if (ini < fin2) {
            coincidencias += (fin2 - ini);
        }
    }
    */

    /*
    if (total_coincidencias > 0) {
        std::cout << AMARILLO << "Coincidencias exactas: " << coincidencias.coincidencias_exactas << RESET_COLOR << std::endl;
        std::cout << CIAN << "Coincidencias con mayusculas/minusculas: " << coincidencias.coincidencias_capitalizacion << RESET_COLOR << std::endl;
        std::cout << ROJO << "Total coincidencias: " << total_coincidencias << RESET_COLOR << std::endl;
    }
    */

    return coincidencias;
}