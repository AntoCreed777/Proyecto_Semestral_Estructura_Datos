#include "../include/definiciones.hpp"
#include "../include/suffix_trees.hpp"

SuffixTrees::Node::Node() {
    ind = std::make_unique<std::list<int>>();
    children.resize(256);
}

void SuffixTrees::Node::insertSuffix(const std::string& suffix, int index) {
    ind->push_back(index);
    if (!suffix.empty()) {
        unsigned char c = suffix.at(0);
        if (!children[c]) {
            children[c] = std::make_unique<Node>();
        }
        children[c]->insertSuffix(suffix.substr(1), index);
    }
}

const std::list<int>* SuffixTrees::Node::search(const std::string& patron) const {
    if (patron.empty()) {
        return ind.get();
    }
    unsigned char c = patron.at(0);
    if (children[c]) {
        return children[c]->search(patron.substr(1));
    }
    return nullptr;
}

SuffixTrees::Node::~Node() {}

unsigned int SuffixTrees::buscar(const std::string& texto, const std::string& patron) {
    if (texto.empty() || patron.empty()) return 0;

    auto root = std::make_unique<Node>();
    for (size_t i = 0; i < texto.size(); ++i) {
        root->insertSuffix(texto.substr(i), i);
    }

    const std::list<int>* ans = root->search(patron);
    return ans ? static_cast<unsigned int>(ans->size()) : 0;
}