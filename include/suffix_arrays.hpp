#pragma once

#include "definiciones.hpp"
#include "class_base.hpp"

class SuffixArrays: public BaseStructure {
    public:
        SuffixArrays(const std::string& texto);
        
        /**
         * @brief Busca un patrón en un texto utilizando el algoritmo de Suffix Arrays.
         * 
         * @param patron Patrón a buscar en el texto.
         * @return cantidad de ocurrencias encontradas en el texto.
         */
        unsigned int buscar(const std::string& patron) const override;

    private:
        std::vector<std::string> sufijos;
};
