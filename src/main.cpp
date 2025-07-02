#include "../include/definiciones.hpp"
#include "../include/utilities.hpp"
#include "../include/class_base.hpp"
#include "../include/boyer_moore.hpp"
#include "../include/fm_index.hpp"
#include "../include/knuth_morris_pratt.hpp"
#include "../include/robin_karp.hpp"
#include "../include/suffix_trees.hpp"
#include "../include/suffix_arrays.hpp"
#include "../include/json.hpp"
#include "../include/medidor.hpp"

#include <set>
#include <functional>
#include <memory>
#include <sstream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

using json = nlohmann::json;

#define NOMBRE_CARPETA_TESTS fs::path("test/textos")
#define ITERACIONES 40

/**
 * @brief Función encargada de obtener todos los archivos .bin de una determinada carpeta
 * @return Retorna los nombres de los archivos 
 */
std::vector<fs::path> archivosEnCarpeta() {
    std::vector<fs::path> nombres_archivos;

    try {
        if (!std::filesystem::exists(NOMBRE_CARPETA_TESTS)) {
            throw std::runtime_error("La carpeta no existe: " + NOMBRE_CARPETA_TESTS.string());
        }

        if (!std::filesystem::is_directory(NOMBRE_CARPETA_TESTS)) {
            throw std::runtime_error("La ruta no es una carpeta: " + NOMBRE_CARPETA_TESTS.string());
        }

        for (const auto &entrada : std::filesystem::directory_iterator(NOMBRE_CARPETA_TESTS)) {
            if (std::filesystem::is_regular_file(entrada)) {
                if (entrada.path().extension() == ".txt") {
                    nombres_archivos.push_back(entrada.path().filename());
                }
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Error al listar archivos: " << e.what() << std::endl;
        return {}; // Vector vacio
    }

    return nombres_archivos;
}

int main() {    
    std::string texto, patron;
    solicitarPatron(patron);

    // Archivos en que se buscara el patron
    std::vector<fs::path> nombres_archivos = archivosEnCarpeta();

    // Vector de algoritmos de búsqueda de patrones a probar
    std::vector<std::pair<std::string, unsigned int(*)(const std::string&, const std::string&)>> algoritmos = {
        {"BoyerMoore", BoyerMoore::buscar},
        {"KnuthMorrisPratt", KnuthMorrisPratt::buscar},
        {"RobinKarp", RobinKarp::buscar},
    };

    std::vector<
        std::pair<
            std::string,
            std::function<std::unique_ptr<BaseStructure>(const std::string&)>
        >
    > estructuras = {
        {"FMIndex",      [](const std::string& texto) { return std::make_unique<FMIndex>(texto); }},
        {"SuffixArrays", [](const std::string& texto) { return std::make_unique<SuffixArrays>(texto); }},
        {"SuffixTrees",  [](const std::string& texto) { return std::make_unique<SuffixTrees>(texto); }},
    };

    for (auto nombre_archivo : nombres_archivos) {
        int contador = 0;
        while(contador < ITERACIONES){
            try{
                fs::path archivo_archivo_completo = NOMBRE_CARPETA_TESTS / nombre_archivo;

                // Carga del texto del archivo
                std::ifstream archivo(archivo_archivo_completo, std::ios::in);
                if (!archivo.is_open()) {
                    throw std::ios_base::failure("No se pudo abrir el archivo: " + archivo_archivo_completo.string());
                }
    
                std::stringstream buffer;
                buffer << archivo.rdbuf();
                texto = buffer.str();
            
                if (texto.empty()) {
                    imprimir(AMARILLO "No hay contenido en el archivo: " RESET_COLOR << archivo_archivo_completo.string());
                    continue;
                }
    
                // TEST
                std::vector<unsigned int> ocurrencias_totales;
    
                for (const auto& alg : algoritmos) {
                    unsigned int ocurrencias = medir_algoritmo(alg.first, alg.second, texto, patron);
                    ocurrencias_totales.push_back(ocurrencias);
                }
    
                for (const auto& est : estructuras) {
                    unsigned int ocurrencias = medir_estructura(est.first, est.second, texto, patron);
                    ocurrencias_totales.push_back(ocurrencias);
                }
    
                std::set<unsigned int> ocurrencias_unicas(ocurrencias_totales.begin(), ocurrencias_totales.end());
    
                size_t memoria_maxima_kb = obtener_memoria_maxima_kb();
                
                std::string nombre_final_json = nombre_archivo.stem().string() + "_" + std::to_string(contador);

                guardar_resultados_finales(
                    nombre_final_json,
                    patron,
                    (ocurrencias_unicas.size() == 1) ? *ocurrencias_unicas.begin() : 0,
                    memoria_maxima_kb
                ); 
                contador++;
            }
            catch (const std::exception &e) {
                std::cerr << "Error al realizar los tests: " << e.what() << std::endl;
            }
        }
    }

    return 0;
}
