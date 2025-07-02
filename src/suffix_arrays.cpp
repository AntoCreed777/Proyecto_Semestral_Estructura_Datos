#include "../include/definiciones.hpp"
#include "../include/suffix_arrays.hpp"

SuffixArrays::SuffixArrays(const std::string& texto) {
    // String aux
    for (auto it = texto.begin(); it != texto.end(); ++it) {
        this->sufijos.emplace_back(it, texto.end());
    }

    // Ordenamos el arreglo de sufijos
    std::sort(this->sufijos.begin(), this->sufijos.end());
}

unsigned int SuffixArrays::buscar(const std::string& patron) const {
    // Aciertos
    unsigned int aciertos = 0;
           
    // Empezar a encontrar el rango de los elementos, devuelve puntero que apunta al sufijo
    auto it = std::lower_bound(this->sufijos.begin(), this->sufijos.end(), patron);
    
    // it es un iterador, entonces *it es el string (*i) y substr es para encontrar el substring que parte con patron
    while(it != this->sufijos.end() && it->compare(0, patron.size(), patron) == 0) aciertos++, it++;
    
    return aciertos;
}
