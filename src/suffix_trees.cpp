#include "../include/definiciones.hpp"
#include "../include/suffix_trees.hpp"

SuffixTrees::Node::Node() {
    ind = std::make_unique<std::list<int>>();
    children.resize(256);
}

void SuffixTrees::Node::insertSuffix(const std::string& texto, size_t posicion_texto, int index) {
    ind->push_back(index);
    if (posicion_texto < texto.size()) {
        unsigned char c = texto.at(posicion_texto);
        if (!children[c]) {
            children[c] = std::make_unique<Node>();
        }
        children[c]->insertSuffix(texto, posicion_texto + 1, index);
    }
}

const std::list<int>* SuffixTrees::Node::search(const std::string& patron, size_t posicion) const {
    if (patron.size() == posicion) return ind.get();
    
    unsigned char c = patron.at(posicion);
    return children[c] ? children[c]->search(patron, posicion + 1) : nullptr;
}

SuffixTrees::Node::~Node() {}

unsigned int SuffixTrees::buscar(const std::string& texto, const std::string& patron) {
    if (texto.empty() || patron.empty()) return 0;

    auto root = std::make_unique<Node>();
    for (size_t i = 0; i < texto.size(); ++i) {
        root->insertSuffix(texto, i, i);
    }

    const std::list<int>* ans = root->search(patron, 0);
    return ans ? static_cast<unsigned int>(ans->size()) : 0;
}