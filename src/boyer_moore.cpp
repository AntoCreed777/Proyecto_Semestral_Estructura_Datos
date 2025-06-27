#include "../include/definiciones.hpp"
#include "../include/boyer_moore.hpp"
#include <string>
#include <iostream>

unsigned int BoyerMoore::buscar(const std::string& texto, const std::string& patron) {
    int tamanio_patron = patron.length(), tamanio_texto = texto.length();
    
    // Contador de aciertos
    unsigned int aciertos = 0;

    // Si no tiene largo el patron o el texto
    if(!tamanio_patron || !tamanio_texto) return 0;
    
    int desplazamiento = 0;
    
    while(desplazamiento <= tamanio_texto - tamanio_patron){
        // Ultimo elemento del patron
        int i = tamanio_patron - 1;
        
        // Si hay coincidencias, avanza al revés
        while(i >= 0 && patron[i] == texto[desplazamiento + i]){
            i--;
        }

        // Ahora comparamos si i llego a 0, entonces encontró el patron
        if(i < 0) aciertos++, desplazamiento += tamanio_patron;
        
        else {
            // Pillar similitudes menores
            int aux = tamanio_patron - 1;
            
            // Se compara desde la similitud, ahi comparamos los elementos
            while(aux >= 0 && texto[desplazamiento + i] != patron[aux]) aux--;
            
            // Tomar los cambios
            if(aux < 0) desplazamiento += tamanio_patron;

            // Avanzamos un poco hasta que encage con el patron
            else desplazamiento += std::max(1, i - aux);
        }
    }
    return aciertos;
}
