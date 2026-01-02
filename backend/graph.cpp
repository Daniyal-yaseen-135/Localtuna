#include "graph.h"

void Graph::connect(const std::string &title, Node* song) {
    if (!song) return;

    auto &vec = adj[title];
    // Avoid duplicates
    for (auto* n : vec)
        if (n == song) return;

    vec.push_back(song);
}

std::vector<Node*> Graph::recommend(const std::string &title) const {
    auto it = adj.find(title);
    if (it != adj.end())
        return it->second;
    return {};
}
