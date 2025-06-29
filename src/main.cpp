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

using json = nlohmann::json;

int main() {
    std::string texto, patron;

    input(texto, patron);

    if (texto.empty()) {
        imprimir(AMARILLO "No hay contenido en el archivo" RESET_COLOR);
        return 0;
    }

    std::vector<unsigned int> ocurrencias_totales;

    // Vector de algoritmos de búsqueda de patrones a probar
    std::vector<std::pair<std::string, unsigned int(*)(const std::string&, const std::string&)>> algoritmos = {
        {"BoyerMoore", BoyerMoore::buscar},
        {"KnuthMorrisPratt", KnuthMorrisPratt::buscar},
        {"RobinKarp", RobinKarp::buscar},
    };

    for (const auto& alg : algoritmos) {
        unsigned int ocurrencias = medir_algoritmo(alg.first, alg.second, texto, patron);
        ocurrencias_totales.push_back(ocurrencias);
    }

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

        for (const auto& est : estructuras) {
            unsigned int ocurrencias = medir_estructura(est.first, est.second, texto, patron);
            ocurrencias_totales.push_back(ocurrencias);
        }

    std::set<unsigned int> ocurrencias_unicas(ocurrencias_totales.begin(), ocurrencias_totales.end());

    size_t memoria_maxima_kb = obtener_memoria_maxima_kb();

    guardar_resultados_finales(
        patron,
        (ocurrencias_unicas.size() == 1) ? *ocurrencias_unicas.begin() : 0,
        memoria_maxima_kb
    );

    return 0;
}