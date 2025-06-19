#include "../include/definiciones.hpp"
#include "../include/boyer_moore.hpp"
#include <string>
#include <iostream>

int BoyerMoore::buscar(const std::string& nombre_archivo, const std::string& patron) {
    int tamanio_patron = patron.length(), tamanio_nombre_archivo = nombre_archivo.length();
    
    // Contador de aciertos
    int aciertos = 0;

    // Si no tiene largo el patron o el texto
    if(!tamanio_patron || !tamanio_nombre_archivo) return 0;
    
    int desplazamiento = 0;
    
    while(desplazamiento <= tamanio_nombre_archivo - tamanio_patron){
        // Ultimo elemento del patron
        int i = tamanio_patron - 1;
        
        // Si hay coincidencias, avanza al revés
        while(i >= 0 && patron[i] == nombre_archivo[desplazamiento + i]){
            i--;
        }

        // Ahora comparamos si i llego a 0, entonces encontró el patron
        if(i <= 0) aciertos++, desplazamiento += tamanio_patron;
        
        else {
            // Pillar similitudes menores
            int aux = tamanio_patron - 1;
            
            // Se compara desde la similitud, ahi comparamos los elementos
            while(aux >= 0 && nombre_archivo[desplazamiento + i] != patron[aux]) aux--;
            
            // Tomar los cambios
            if(aux <= 0) desplazamiento += tamanio_patron;

            // Avanzamos un poco hasta que encage con el patron
            else desplazamiento += aux;
        }
    }
    return aciertos;
}
