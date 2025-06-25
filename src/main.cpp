#include "../include/definiciones.hpp"
#include "../include/utilities.hpp"
#include "../include/class_base.hpp"
#include "../include/boyer_moore.hpp"
#include "../include/fm_index.hpp"
#include "../include/knuth_morris_pratt.hpp"
#include "../include/robin_karp.hpp"
#include "../include/suffix_trees.hpp"
#include "../include/suffix_arrays.hpp"

#include <chrono>
#include <functional>

int main() {
    std::string texto, patron;

    input(texto, patron);

    if (texto.empty()) {
        imprimir(AMARILLO "No hay contenido en el archivo" RESET_COLOR);
        return 0;
    }

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
    > algoritmos_estructura = {
        /*
        {
            "FMIndex",
            [](const std::string& texto) -> std::unique_ptr<BaseStructure> { 
                return std::make_unique<FMIndex>(texto); 
            }
        },
        */
        {
            "SuffixArrays",
            [](const std::string& texto) -> std::unique_ptr<BaseStructure> { 
                return std::make_unique<SuffixArrays>(texto); 
            }
        },
        {
            "SuffixTrees", 
            [](const std::string& texto) -> std::unique_ptr<BaseStructure> { 
                return std::make_unique<SuffixTrees>(texto); 
            }
        }
    };

    for (const auto& alg : algoritmos) {
        imprimir("\nProbando algoritmo: " << AZUL << alg.first << RESET_COLOR);

        try {
            auto start = std::chrono::high_resolution_clock::now();
            unsigned int resultado = alg.second(texto, patron);
            auto end = std::chrono::high_resolution_clock::now();

            if (resultado > 0) imprimir(VERDE "Patron encontrado " BLANCO << resultado << " veces." RESET_COLOR);
            else imprimir(MAGENTA "Patron no encontrado." RESET_COLOR);

            // Tiempo en milisegundos
            auto duracion_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            imprimir(AMARILLO "Tiempo: " CIAN << duracion_ms << " ms" RESET_COLOR);
        }
        catch (const std::exception& e) {
            imprimir(ROJO "Error en " << alg.first << ": " RESET_COLOR << e.what());
        }
    }

    // Prueba con algoritmos de estructura
    for (const auto& alg : algoritmos_estructura) {
        imprimir("\nProbando estructura: " << AZUL << alg.first << RESET_COLOR);

        try {
            
            // Construcción
            auto start = std::chrono::high_resolution_clock::now();
            auto estructura = alg.second(texto);
            auto end = std::chrono::high_resolution_clock::now();

            imprimir(AMARILLO "Tiempo de construccion: " CIAN << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0 << " ms" RESET_COLOR);

            // Búsqueda
            start = std::chrono::high_resolution_clock::now();
            unsigned int resultado = estructura->buscar(patron);
            end = std::chrono::high_resolution_clock::now();

            if (resultado > 0) 
                imprimir(VERDE "Patron encontrado " BLANCO << resultado << " veces." RESET_COLOR);
            else 
                imprimir(MAGENTA "Patron no encontrado." RESET_COLOR);

            imprimir(ROJO "Tiempo de busqueda: " CIAN << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0 << " ms" RESET_COLOR);
        }
        catch (const std::exception& e) {
            imprimir(ROJO "Error en " << std::get<0>(alg) << ": " RESET_COLOR << e.what());
        }
    }
    
    return 0;
}