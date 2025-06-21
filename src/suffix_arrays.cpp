#include "../include/definiciones.hpp"
#include "../include/suffix_arrays.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

unsigned int SuffixArrays::buscar(const std::string& texto, const std::string& patron) {
    // Implementación del algoritmo Suffix Arrays
    std::vector<std::string> sufijos;
    
    // Aciertos
    unsigned int aciertos = 0;
    
    // String aux
    std::string texto_copy = texto;

    while(!texto_copy.empty()){
        sufijos.push_back(texto_copy);
        texto_copy.erase(0,1);
    }
    
    // Ordenamos el arreglo de sufijos
    std::sort(sufijos.begin(), sufijos.end());
    
    // Empezar a encontrar el rango de los elementos, devuelve puntero que apunta al sufijo
    auto it = std::lower_bound(sufijos.begin(), sufijos.end(), patron);
    
    // it es un iterador, entonces *it es el string (*i) y substr es para encontrar el substring que parte con patron
    while(it != sufijos.end() && it->substr(0, patron.size()) == patron) aciertos++, it++;
    
    return aciertos;
}
