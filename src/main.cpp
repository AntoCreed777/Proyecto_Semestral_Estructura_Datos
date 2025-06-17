#include "../include/definiciones.hpp"
#include "../include/utilities.hpp"
#include "../include/boyer_moore.hpp"
#include "../include/fm_index.hpp"
#include "../include/knuth_morris_pratt.hpp"
#include "../include/robin_karp.hpp"
#include "../include/suffix_trees.hpp"
#include "../include/suffix_arrays.hpp"

int main() {
    fs::path nombre_archivo;
    std::string patron;

    input(nombre_archivo, patron);

    imprimir(nombre_archivo.string());
    imprimir(patron);

    // Vector de algoritmos de búsqueda de patrones a probar
    std::vector<std::pair<std::string, bool(*)(const fs::path&, const std::string&)>> algoritmos = {
        {"BoyerMoore", BoyerMoore::buscar},
        {"KnuthMorrisPratt", KnuthMorrisPratt::buscar},
        {"RobinKarp", RobinKarp::buscar},
        {"FMIndex", FMIndex::buscar},
        {"SuffixArrays", SuffixArrays::buscar},
        {"SuffixTrees", SuffixTrees::buscar},
        {"SuffixTrees VERSION 2", SuffixTrees_VERSION_2::buscar}
    };

    for (const auto& alg : algoritmos) {
        std::cout << "\nProbando algoritmo: " << AZUL << alg.first << RESET_COLOR << std::endl;
        try {
            if (alg.second(nombre_archivo, patron))
                std::cout << VERDE "Patrón encontrado." RESET_COLOR << std::endl;
            else
                std::cout << MAGENTA "Patrón no encontrado." RESET_COLOR << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << ROJO "Error en " << alg.first << ": " RESET_COLOR << e.what() << std::endl;
        }
    }
    
    return 0;
}