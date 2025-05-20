#ifndef MUSICLIST_H
#define MUSICLIST_H

#include <QVector>
#include <QUrl>
#include <QMimeDatabase>


#include "music.h"

class MusicList
{
public:
    MusicList();

    // 将myQQMusic页面中读取的音乐文件，检测是音乐文件后添加到musicList中
    void addMusicByUrl(const QList<QUrl>& urls);



private:
    QVector<Music> musicList;
};

#endif // MUSICLIST_H
