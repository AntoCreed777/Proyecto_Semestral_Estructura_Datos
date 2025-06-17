#include "../include/definiciones.hpp"
#include "../include/suffix_trees.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

// --- SuffixTrees ---
bool SuffixTrees::buscar(const fs::path& nombre_archivo, const std::string& patron) {
    std::ifstream archivo(nombre_archivo, std::ios::in);
    if (!archivo.is_open()) {
        throw std::ios_base::failure("No se pudo abrir el archivo: " + nombre_archivo.string());
    }

    std::stringstream buffer;
    buffer << archivo.rdbuf();
    std::string contenido = buffer.str();

    Node *root = new Node();
    
    for (int i = 0; i < (int)contenido.length(); i++)
        root->insertSuffix(contenido.substr(i), i);

    std::list<int>* ans = root->search(patron);

    delete root;

    return ans != nullptr;
}

SuffixTrees::Node::Node() {
    ind = new std::list<int>;

    for (int i = 0; i < 256; i++) 
        children[i] = nullptr;
}

void SuffixTrees::Node::insertSuffix(const std::string& suffix, int index) {
    ind->push_back(index);

    if (!suffix.empty()) {
        unsigned char indice_caracter_inicial = (unsigned char)suffix.at(0);

        if (children[indice_caracter_inicial] == nullptr)
            children[indice_caracter_inicial] = new Node();
        
        children[indice_caracter_inicial]->insertSuffix(suffix.substr(1), index + 1);
    }
}

std::list<int>* SuffixTrees::Node::search(const std::string& patron) const {
    if (patron.empty()) return ind;

    unsigned char indice_caracter_inicial = (unsigned char)patron.at(0);

    if (children[indice_caracter_inicial] != nullptr)
        return children[indice_caracter_inicial]->search(patron.substr(1));
    else
        return nullptr;
}

SuffixTrees::Node::~Node() {
    for (int i = 0; i < 256; i++) 
        if (children[i] != nullptr) delete children[i];
    delete ind;
}
