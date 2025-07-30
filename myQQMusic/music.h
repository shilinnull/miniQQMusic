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

    // 获取歌词文件路径
    QString getLrcFilePath() const;
    // 插入每首音乐到数据库
    void insertMusicToDB();

private:
    // 解析数据
    void parseMediaMetaData();

private:
    bool isLike; // 标记是否我喜欢
    bool isHistory; // 标记音乐是否播放过

    // ⾳乐的基本信息有：歌曲名称、歌⼿名称、专辑名称、总时⻓
    QString musicName;
    QString singerName;
    QString albumName;
    qint64 duration;

    // 标记歌曲的唯一性
    QString musicId;

    // 音乐url
    QUrl musicUrl;
};

#endif // MUSIC_H
