#include "queue.h"

void SongQueue::add(Node* n) {
    pq.push(n);
}

Node* SongQueue::pop() {
    if (pq.empty()) return nullptr;
    Node* t = pq.top();
    pq.pop();
    return t;
}
