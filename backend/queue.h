#ifndef QUEUE_H
#define QUEUE_H

#include <queue>
#include "node.h"

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->song.rating < b->song.rating;
    }
};

class SongQueue {
public:
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;

    void add(Node* n);
    Node* pop();
      bool empty() const { return pq.empty(); }
};

#endif
