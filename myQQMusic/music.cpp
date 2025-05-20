#include "music.h"
#include <QUuid>
#include <QMediaPlayer>

Music::Music()
    :isLike(false)
    ,isHistory(false)
{

}
Music::Music(const QUrl& url)
    :isLike(false)
    ,isHistory(false)
    ,musicUrl(url)
{
    // 读取url对应的歌曲文件的信息，解析出元数据
    // 歌曲名称、歌曲作者、歌曲专辑、歌曲持续时长
    musicId = QUuid::createUuid().toString();
//    parseMediaMetaMusic();
}

void Music::setIsLike(bool isLike)
{
    this->isLike = isLike;
}
void Music::setIsHistory(bool isHistory)
{
    this->isHistory = isHistory;
}
void Music::setMusicName(const QString& musicName)
{
    this->musicName = musicName;
}
void Music::setSingerName(const QString& singerName)
{
    this->singerName = singerName;
}
void Music::setAlbumName(const QString& albumName)
{
    this->albumName = albumName;
}
void Music::setDuration(const qint64 duration)
{
    this->duration = duration;
}
void Music::setMusicUrl(const QUrl& url)
{
    this->musicUrl = url;
}
void Music::setMusicId(const QString& MusicId)
{
    this->musicId = MusicId;
}

bool Music::getIsLike()const
{
    return isLike;
}
bool Music::getIsHistory()const
{
    return isHistory;
}
QString Music::getMusicName()const
{
    return musicName;
}
QString Music::getSingerName()const
{
    return singerName;
}
QString Music::getAlbumName()const
{
    return albumName;
}
qint64 Music::getDuration()const
{
    return duration;
}
QUrl Music::getMusicUrl()const
{
    return musicUrl;
}
QString Music::getMusicId()const
{
    return musicId;
}


