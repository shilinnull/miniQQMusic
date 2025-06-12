#ifndef MUSICLIST_H
#define MUSICLIST_H

#include <QVector>
#include <QUrl>
#include <QMimeDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSet>


#include "music.h"

class MusicList
{
    typedef typename QVector<Music>::iterator iterator;
public:
    MusicList();

    // 将myQQMusic页面中读取的音乐文件，检测是音乐文件后添加到musicList中
    void addMusicByUrl(const QList<QUrl>& urls);

    iterator begin();
    iterator end();
    iterator findMusicByMusicid(const QString& musicId);

    // 写数据
    void writeToDB();
    // 读数据
    void readFromDB();

private:
    QVector<Music> musicList;
    QSet<QString> musicPaths;
};

#endif // MUSICLIST_H
