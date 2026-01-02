#ifndef SEARCHINDEX_H
#define SEARCHINDEX_H

#include <unordered_map>
#include <vector>
#include "node.h"

class SearchIndex {
public:
    std::unordered_map<std::string, std::vector<Node*>> index;

    void add(Node* node);
    std::vector<Node*> search(std::string key);
};

#endif
