#ifndef MUSIC_H
#define MUSIC_H

#include <QUrl>
#include <QSqlQuery>
#include <QSqlError>
#include <QUuid>
#include <QMediaPlayer>
#include <QCoreApplication>

/**
 * @brief 音乐数据模型类
 * 管理音乐元数据、播放状态及数据库交互
 */
class Music
{
public:
    /**
     * @brief 默认构造函数
     */
    Music();

    /**
     * @brief 通过音乐URL构造Music对象
     * @param url 音乐文件URL
     */
    Music(const QUrl& url);

    /**
     * @brief 设置音乐收藏状态
     * @param isLike 是否收藏
     */
    void setIsLike(bool isLike);

    /**
     * @brief 设置音乐历史播放状态
     * @param isHistory 是否为历史播放
     */
    void setIsHistory(bool isHistory);

    /**
     * @brief 设置音乐名称
     * @param musicName 音乐名称
     */
    void setMusicName(const QString& musicName);

    /**
     * @brief 设置歌手名称
     * @param singerName 歌手名称
     */
    void setSingerName(const QString& singerName);

    /**
     * @brief 设置专辑名称
     * @param albumName 专辑名称
     */
    void setAlbumName(const QString& albumName);

    /**
     * @brief 设置音乐时长
     * @param duration 时长(毫秒)
     */
    void setDuration(const qint64 duration);

    /**
     * @brief 设置音乐URL
     * @param url 音乐文件URL
     */
    void setMusicUrl(const QUrl& url);

    /**
     * @brief 设置音乐唯一ID
     * @param MusicId 音乐ID
     */
    void setMusicId(const QString& MusicId);

    /**
     * @brief 获取音乐收藏状态
     * @return 是否收藏
     */
    bool getIsLike()const;

    /**
     * @brief 获取音乐历史播放状态
     * @return 是否为历史播放
     */
    bool getIsHistory()const;

    /**
     * @brief 获取音乐名称
     * @return 音乐名称
     */
    QString getMusicName()const;

    /**
     * @brief 获取歌手名称
     * @return 歌手名称
     */
    QString getSingerName()const;

    /**
     * @brief 获取专辑名称
     * @return 专辑名称
     */
    QString getAlbumName()const;

    /**
     * @brief 获取音乐时长
     * @return 时长(毫秒)
     */
    qint64 getDuration()const;

    /**
     * @brief 获取音乐URL
     * @return 音乐文件URL
     */
    QUrl getMusicUrl()const;

    /**
     * @brief 获取音乐唯一ID
     * @return 音乐ID
     */
    QString getMusicId()const;

    /**
     * @brief 获取歌词文件路径
     * @return 歌词文件路径
     */
    QString getLrcFilePath() const;

    /**
     * @brief 将音乐信息插入数据库
     */
    void insertMusicToDB();

private:
    /**
     * @brief 解析音乐元数据
     * 从音乐文件中提取标题、歌手、专辑等信息
     */
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
