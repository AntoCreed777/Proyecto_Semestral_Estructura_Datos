#include "../include/definiciones.hpp"
#include "../include/utilities.hpp"
#include "../include/boyer_moore.hpp"
#include "../include/fm_index.hpp"
#include "../include/knuth_morris_pratt.hpp"
#include "../include/robin_karp.hpp"
#include "../include/suffix_trees.hpp"
#include "../include/suffix_arrays.hpp"

#include <chrono>

int main() {
    std::string texto, patron;

    input(texto, patron);

    // Vector de algoritmos de búsqueda de patrones a probar
    std::vector<std::pair<std::string, unsigned int(*)(const std::string&, const std::string&)>> algoritmos = {
        {"BoyerMoore", BoyerMoore::buscar},
        {"KnuthMorrisPratt", KnuthMorrisPratt::buscar},
        {"RobinKarp", RobinKarp::buscar},
        {"FMIndex", FMIndex::buscar},
        {"SuffixArrays", SuffixArrays::buscar},
        {"SuffixTrees", SuffixTrees::buscar}
    };

    for (const auto& alg : algoritmos) {
        imprimir("\nProbando algoritmo: " << AZUL << alg.first << RESET_COLOR);

        try {
            auto start = std::chrono::high_resolution_clock::now();
            unsigned int resultado = alg.second(texto, patron);
            auto end = std::chrono::high_resolution_clock::now();

            if (resultado > 0) imprimir(VERDE "Patrón encontrado " BLANCO << resultado << " veces." RESET_COLOR);
            else imprimir(MAGENTA "Patrón no encontrado." RESET_COLOR);
            
            imprimir("Tiempo: " CIAN << (end - start).count() / 1000 << " ms" RESET_COLOR);
        }
        catch (const std::exception& e) {
            imprimir(ROJO "Error en " << alg.first << ": " RESET_COLOR << e.what());
        }
    }
    
    return 0;
}