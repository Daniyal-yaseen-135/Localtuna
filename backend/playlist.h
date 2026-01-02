#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "node.h"

class Playlist {
public:
    Node* head;
    Node* tail;
    Node* current;

    Playlist();

    void addSong(const Song& song);
    Node* nextSong();
    Node* prevSong();
    int size() const;
    Node* first() const;
    Node* last() const;
};

#endif
