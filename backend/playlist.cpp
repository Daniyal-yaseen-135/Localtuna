#include "playlist.h"

Playlist::Playlist() {
    head = tail = current = nullptr;
}

void Playlist::addSong(const Song& song) {
    Node* n = new Node(song);
    if (!head) {
        head = tail = current = n;
    } else {
        tail->next = n;
        n->prev = tail;
        tail = n;
    }
}

Node* Playlist::nextSong() {
    if (current->next){
        current = current->next;
        return current;
    }
    if (!current)
        return nullptr;
    return nullptr;
}

Node* Playlist::prevSong() {
    if (current && current->prev)
        current = current->prev;
    return current;
}
Node* Playlist::first() const
{
    return head;
}
Node* Playlist::last() const
{
    return tail;
}
int Playlist::size() const
{
    int count = 0;
    Node* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
         return count;
}
