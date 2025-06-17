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

// --- SuffixTrees - VERSION 2 ---
bool SuffixTrees_VERSION_2::buscar(const fs::path& nombre_archivo, const std::string& patron) {
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

    std::unique_ptr<std::list<int>> ans = root->search(patron);

    return ans != nullptr;
}

void SuffixTrees_VERSION_2::Node::insertSuffix(const std::string& suffix, int index) {
    size_t pos = 0;

    // Encontrar el punto de divergencia entre el contenido actual y el sufijo
    while (pos < contenido.size() && pos < suffix.size() && contenido[pos] == suffix[pos]) {
        pos++;
    }

    // Dividir nodo si el contenido actual no coincide completamente con el sufijo
    if (pos < contenido.size()) {
        dividirNodo(pos);
    }

    // Si todavía quedan caracteres en el sufijo, crear o delegar a un hijo
    if (pos < suffix.size()) {
        auto& hijo = children[suffix[pos]];
        if (!hijo) {
            hijo = std::make_unique<Node>();
            hijo->setContenido(suffix.substr(pos));
        }
        hijo->ind.push_back(index);
        hijo->insertSuffix(suffix.substr(pos + 1), index + 1);
    }
    // El sufijo coincide completamente con este nodo
    else ind.push_back(index);
}

std::unique_ptr<std::list<int>> SuffixTrees_VERSION_2::Node::search(const std::string& pat) const {
    size_t pos = 0;

    // Encontrar el punto de divergencia entre el patrón y el contenido actual
    while (pos < contenido.size() && pos < pat.size() && contenido[pos] == pat[pos]) {
        pos++;
    }

    // Si el patrón coincide completamente
    if (pos == pat.size()) {
        return std::make_unique<std::list<int>>(ind);
    }

    // Delegar la búsqueda al hijo correspondiente
    auto it = children.find(pat[pos]);
    if (it != children.end())
        return it->second->search(pat.substr(pos + 1));

    return nullptr;
}

void SuffixTrees_VERSION_2::Node::dividirNodo(size_t pos) {
    auto newChild = std::make_unique<Node>();
    newChild->setContenido(contenido.substr(pos));  // Parte restante del contenido actual
    newChild->moverIndices(std::move(ind));         // Transferir índices al nuevo hijo
    newChild->moverHijos(std::move(children));      // Transferir hijos al nuevo nodo

    contenido.resize(pos);                          // Recortar el contenido actual
    children[contenido[pos]] = std::move(newChild); // Añadir el nuevo hijo
}

SuffixTrees_VERSION_2::Node* SuffixTrees_VERSION_2::Node::encontrarHijo(char c) const {
    auto it = children.find(c);
    return (it != children.end()) ? it->second.get() : nullptr;
}   

void SuffixTrees_VERSION_2::Node::moverHijos(std::unordered_map<char, std::unique_ptr<Node>> nuevosHijos) {
    children = std::move(nuevosHijos);
}

void SuffixTrees_VERSION_2::Node::moverIndices(std::list<int> nuevosIndices) {
    ind = std::move(nuevosIndices);
}

char SuffixTrees_VERSION_2::Node::contenidoInicial() const {
    return contenido.empty() ? '\0' : contenido[0];
}

void SuffixTrees_VERSION_2::Node::setContenido(const std::string& nuevoContenido) {
    contenido = nuevoContenido;
}
