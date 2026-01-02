#ifndef NODE_H
#define NODE_H

#include "song.h"

struct Node {
    Song song;
    Node* next;
    Node* prev;

    Node(const Song& s) : song(s), next(nullptr), prev(nullptr) {}
};

#endif
