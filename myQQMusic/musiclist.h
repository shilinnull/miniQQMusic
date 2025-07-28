#ifndef MUSICLIST_H
#define MUSICLIST_H

#include <QVector>
#include <QUrl>
#include <QSet>
#include <QMimeDatabase>
#include <QMimeType>
#include "music.h"

/**
 * @brief The MusicList class
 * 音乐列表管理器，负责音乐数据的加载、存储、管理和数据库交互
 * 提供迭代器访问和音乐文件去重功能
 */
class MusicList
{
    typedef typename QVector<Music>::iterator iterator;
public:
    /**
     * @brief MusicList 构造函数
     * 初始化音乐列表容器和路径集合
     */
    MusicList();

    /**
     * @brief addMusicByUrl 通过URL列表添加音乐
     * 检查文件类型，仅添加支持的音乐格式，并自动去重
     * @param urls 音乐文件URL列表
     */
    void addMusicByUrl(const QList<QUrl>& urls);

    /**
     * @brief begin 获取音乐列表起始迭代器
     * @return 指向首个元素的迭代器
     */
    iterator begin();

    /**
     * @brief end 获取音乐列表结束迭代器
     * @return 指向末尾元素之后位置的迭代器
     */
    iterator end();

    /**
     * @brief findMusicByMusicid 根据音乐ID查找音乐
     * @param musicId 要查找的音乐ID
     * @return 找到的音乐元素迭代器，未找到则返回end()
     */
    iterator findMusicByMusicid(const QString& musicId);

    /**
     * @brief writeToDB 将音乐列表写入数据库
     * 遍历音乐列表，将每个音乐信息存储到SQLite数据库
     */
    void writeToDB();

    /**
     * @brief readFromDB 从数据库读取音乐列表
     * 从SQLite数据库加载音乐信息并重建音乐列表
     */
    void readFromDB();

private:
    QVector<Music> musicList;      ///< 存储音乐对象的容器
    QSet<QString> musicPaths;      ///< 用于去重的音乐路径集合
};

#endif // MUSICLIST_H
