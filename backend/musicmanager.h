#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include <QObject>
#include <QStringList>
#include <QMediaPlayer>
#include <QAudioOutput>

#include "playlist.h"
#include "searchindex.h"
#include "bst.h"
#include "graph.h"
#include "queue.h"
#include "song.h"

class MusicManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList songs READ songs NOTIFY songsChanged)
    Q_PROPERTY(bool playing READ playing NOTIFY playingChanged)


    QString currentSongPath;
public:
    explicit MusicManager(QObject *parent = nullptr);
    bool playing() const;

    QStringList songs() const;

    Q_INVOKABLE void loadSongs();
    Q_INVOKABLE void playSong(const QString &title);
    Q_INVOKABLE void nextSong();
    Q_INVOKABLE void prevSong();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void resume();
    Q_INVOKABLE QStringList searchSongs(const QString &query);
    Q_INVOKABLE void shuffleSong();
    Q_INVOKABLE void addToQueue(const QString& displayText);
    Q_INVOKABLE QStringList viewSimilar(const QString& displayText);



signals:
    void songsChanged();
    void playingChanged();
        void currentSongChanged(const QString& displayText);

private:
    Node* findNode(const QString &title);
      void emitCurrentSong(Node* n);

    Playlist playlist;
    SearchIndex searchIndex;
    BST bst;
    Graph graph;
   SongQueue songQueue;

    QStringList m_songs;

    QMediaPlayer *player;
    QAudioOutput *audioOutput;
};

#endif
