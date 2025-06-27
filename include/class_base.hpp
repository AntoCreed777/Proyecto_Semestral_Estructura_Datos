#pragma once

#include "definiciones.hpp"

// Clase base para estructuras de búsqueda
class BaseStructure {
    public:
        virtual ~BaseStructure() = default;
        virtual unsigned int buscar(const std::string& patron) const = 0;
};