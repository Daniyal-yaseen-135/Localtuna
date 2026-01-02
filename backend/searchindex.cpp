#include "searchindex.h"

void SearchIndex::add(Node* node) {
    index[node->song.title].push_back(node);
    index[node->song.artist].push_back(node);
    index[node->song.genre].push_back(node);
}

std::vector<Node*> SearchIndex::search(std::string key) {
    return index[key];
}
