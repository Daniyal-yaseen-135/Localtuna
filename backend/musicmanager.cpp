#include "musicmanager.h"
#include <QDir>
#include <QFileInfo>
#include <QUrl>
#include <QDebug>
#include <QRandomGenerator>

MusicManager::MusicManager(QObject *parent)
    : QObject(parent)
{
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    connect(player, &QMediaPlayer::playbackStateChanged,
            this, &MusicManager::playingChanged);
}

QStringList MusicManager::songs() const
{
    return m_songs;
}

void MusicManager::loadSongs()
{
    QDir dir("D:/localtuna/songs"); // your folder
    QStringList files = dir.entryList(QStringList() << "*.mp3", QDir::Files);

    m_songs.clear();

    for (const QString &file : files) {
        QFileInfo info(file);
        QString base = info.completeBaseName();

        // Title-Artist-Genre-Rating.mp3
        QStringList parts = base.split("-");
        if (parts.size() < 4)
            continue;

        Song s;
        s.title  = parts[0].trimmed().toStdString();
        s.artist = parts[1].trimmed().toStdString();
        s.genre  = parts[2].trimmed().toStdString();
        s.rating = parts[3].trimmed().toFloat();
        s.path   = (dir.absoluteFilePath(file)).toStdString();

        playlist.addSong(s);
        searchIndex.add(playlist.tail);
        bst.insert(playlist.tail);

        m_songs << QString("%1|%2|%3")
            .arg(QString::fromStdString(s.title))
            .arg(QString::fromStdString(s.artist))
            .arg(QString::fromStdString(s.genre));

    }
    Node* a = playlist.first();
    while (a) {
        Node* b = playlist.first();
        while (b) {
            if (a != b) {
                if (a->song.artist == b->song.artist || a->song.genre == b->song.genre) {
                    // Connect using song title as key
                    graph.connect(a->song.title, b); // a->song.title is std::string, b is Node*

                }
            }
            b = b->next;
        }
        a = a->next;
    }
     emit songsChanged();
}

Node* MusicManager::findNode(const QString &title)
{
    auto res = searchIndex.search(title.toStdString());
    if (!res.empty())
        return res[0];
    return nullptr;
}



void MusicManager::nextSong()
{
    Node* n = nullptr;

    // 🎯 Priority queue first
    if (!songQueue.empty()) {
        n = songQueue.pop();
    } else {
        n = playlist.nextSong();
        if (!n) {
            n = playlist.first();
            playlist.current = n;
        }
    }

    if (!n) return;

    playlist.current = n;

    player->setSource(
        QUrl::fromLocalFile(QString::fromStdString(n->song.path))
        );
    player->play();
    emitCurrentSong(n);
}

bool MusicManager::playing() const {
    return player->playbackState() == QMediaPlayer::PlayingState;
}


void MusicManager::prevSong()
{
    Node* n = playlist.prevSong();
    if (!n) return;

    player->setSource(
        QUrl::fromLocalFile(QString::fromStdString(n->song.path))
        );
    player->play();
    emitCurrentSong(n);
}
void MusicManager::playSong(const QString &displayText)
{
     QString title = displayText.split("|")[0].trimmed();
    Node* n = findNode(title);
    if (!n) return;

    playlist.current = n;

    player->setSource(
        QUrl::fromLocalFile(QString::fromStdString(n->song.path))
        );
    player->play();
    emitCurrentSong(n);
}

void MusicManager::pause()
{
    if (player->playbackState() == QMediaPlayer::PlayingState)
        player->pause();
}

void MusicManager::resume()
{
    if (player->playbackState() == QMediaPlayer::PausedState)
        player->play();
}
QStringList MusicManager::searchSongs(const QString &query)
{
    QStringList results;
    auto nodes = searchIndex.search(query.toStdString());
    for (auto* n : nodes) {
        results << QString("%1|%2|%3")
        .arg(QString::fromStdString(n->song.title))
            .arg(QString::fromStdString(n->song.artist))
            .arg(QString::fromStdString(n->song.genre));
    }
    return results;
}
#include <QRandomGenerator>

void MusicManager::shuffleSong()
{
    int count = playlist.size();
    if (count == 0) return;

    int index = QRandomGenerator::global()->bounded(count);

    Node* n = playlist.first();
    for (int i = 0; i < index; ++i)
        n = n->next;

    if (!n) return;

    playlist.current = n;

    player->setSource(
        QUrl::fromLocalFile(QString::fromStdString(n->song.path))
        );
    player->play();
    emitCurrentSong(n);
}
void MusicManager::addToQueue(const QString& displayText)
{
    QString title = displayText.split("|")[0].trimmed();
    Node* n = findNode(title);
    if (!n) return;

    songQueue.add(n);

    qDebug() << "Added to queue:"
             << QString::fromStdString(n->song.title);
}
QStringList MusicManager::viewSimilar(const QString& displayText)
{
    QString title = displayText.split("|")[0].trimmed();
    Node* base = findNode(title);
    if (!base) return {};

    QStringList results;
    auto recommended = graph.recommend(title.toStdString());

    if (recommended.empty()) {
        qDebug() << "viewSimilar: no recommendations for:" << title;
    }

    for (Node* n : recommended) {
        results << QString("%1|%2|%3")
        .arg(QString::fromStdString(n->song.title))
            .arg(QString::fromStdString(n->song.artist))
            .arg(QString::fromStdString(n->song.genre));
        qDebug() << "viewSimilar result:" << QString::fromStdString(n->song.title);
    }

    return results;
}
void MusicManager::emitCurrentSong(Node* n)
{
    if (!n) return;

    emit currentSongChanged(
        QString("%1|%2|%3")
            .arg(QString::fromStdString(n->song.title))
            .arg(QString::fromStdString(n->song.artist))
            .arg(QString::fromStdString(n->song.genre))
        );
}

