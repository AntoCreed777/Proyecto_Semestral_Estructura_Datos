#include "../include/definiciones.hpp"
#include "../include/suffix_arrays.hpp"
#include <iostream>
#include <string>

bool SuffixArrays::buscar(const std::string& nombre_archivo, const std::string& patron) {
    // Implementación del algoritmo Suffix Arrays
    
}

int main(){
    std::string texto = "Hola quisiera comer helado de piña";
    std::string patron = "comer";

    std::string mensaje = SuffixArrays::buscar(texto,patron) ? "Exito" : "Fracaso";
    std::cout << mensaje << std::endl;

}
