#ifndef MUSICLIST_H
#define MUSICLIST_H

#include <QVector>
#include <QUrl>
#include <QSet>
#include <QMimeDatabase>
#include <QMimeType>
#include "music.h"

class MusicList
{
    typedef typename QVector<Music>::iterator iterator;
public:
    MusicList();
    void addMusicByUrl(const QList<QUrl>& urls);
    iterator begin();
    iterator end();
    iterator findMusicByMusicid(const QString& musicId);
    void writeToDB();
    void readFromDB();

private:
    QVector<Music> musicList;
    QSet<QString> musicPaths; // 用于去重
};

#endif // MUSICLIST_H
