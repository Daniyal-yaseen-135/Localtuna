#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <string>
#include "node.h"

class Graph {
public:
    // Map song title -> list of Node* recommendations
    std::unordered_map<std::string, std::vector<Node*>> adj;

    void connect(const std::string &title, Node* song);

    std::vector<Node*> recommend(const std::string &title) const;
};

#endif
