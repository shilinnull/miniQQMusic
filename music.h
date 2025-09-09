#ifndef MUSIC_H
#define MUSIC_H

#include <QUrl>
#include <QSqlQuery>
#include <QSqlError>
#include <QUuid>
#include <QMediaPlayer>
#include <QCoreApplication>

class Music
{
public:
    Music();
    Music(const QUrl& url);
    void setIsLike(bool isLike);
    void setIsHistory(bool isHistory);
    void setMusicName(const QString& musicName);
    void setSingerName(const QString& singerName);
    void setAlbumName(const QString& albumName);
    void setDuration(const qint64 duration);
    void setMusicUrl(const QUrl& url);
    void setMusicId(const QString& MusicId);
    bool getIsLike()const;
    bool getIsHistory()const;
    QString getMusicName()const;
    QString getSingerName()const;
    QString getAlbumName()const;
    qint64 getDuration()const;
    QUrl getMusicUrl()const;
    QString getMusicId()const;
    QString getLrcFilePath() const;
    void insertMusicToDB(); // 插入音乐到数据库

private:
    void parseMediaMetaData();

private:
    bool isLike;          // 是否收藏
    bool isHistory;       // 是否历史播放
    QString musicName;    // 音乐名称
    QString singerName;   // 歌手名称
    QString albumName;    // 专辑名称
    qint64 duration;      // 音乐时长(毫秒)
    QString musicId;      // 音乐唯一ID
    QUrl musicUrl;        // 音乐文件URL
};

#endif // MUSIC_H
