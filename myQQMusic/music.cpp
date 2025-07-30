#include "music.h"
<<<<<<< HEAD

=======
>>>>>>> c765204f81f562b90e8f9ac3da79b36f5bd04213

/**
 * @brief Music 默认构造函数
 * 初始化收藏和历史状态为false
 */
Music::Music()
    :isLike(false)
    ,isHistory(false)
{
}
/**
 * @brief Music 构造函数
 * @param url 音乐文件URL
 * 初始化收藏和历史状态，生成唯一ID，并解析元数据
 */
Music::Music(const QUrl& url)
    :isLike(false)
    ,isHistory(false)
    ,musicUrl(url)
{
    // 生成音乐唯一ID
    musicId = QUuid::createUuid().toString();
    // 解析歌曲元数据
    parseMediaMetaData();
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

/**
 * @brief 解析音乐元数据
 * 从音乐文件中提取标题、歌手、专辑和时长信息
 * 当元数据不可用时，从文件名中提取信息作为 fallback
 */
void Music::parseMediaMetaData()
{
    // 创建媒体播放器实例用于提取元数据
    QMediaPlayer player;
    player.setMedia(musicUrl);

    // 等待元数据可用，处理事件以保持UI响应
    while(!player.isMetaDataAvailable())
    {
        QCoreApplication::processEvents();
    }

    // 提取元数据
    if(player.isMetaDataAvailable())
    {
        musicName = player.metaData("Title").toString();
        singerName = player.metaData("Author").toString();
        albumName = player.metaData("AlbumTitle").toString();
        duration = player.duration();

        // 从文件名提取信息作为元数据缺失时的 fallback
        QString fileName = musicUrl.fileName();
        int separatorIndex = fileName.indexOf('-');

        // 处理音乐名称
        if(musicName.isEmpty())
        {
            if(separatorIndex != -1)
            {
                musicName = fileName.mid(0, separatorIndex).trimmed();
            }
            else
            {
                musicName = fileName.mid(0, fileName.indexOf('.')).trimmed();
            }
        }

        // 处理歌手名称
        if(singerName.isEmpty())
        {
            if(separatorIndex != -1)
            {
                singerName = fileName.mid(separatorIndex + 1, fileName.indexOf('.') - separatorIndex - 1).trimmed();
            }
            else
            {
                singerName = "未知歌手";
            }
        }

        // 处理专辑名称
        if(albumName.isEmpty())
        {
            albumName = "未知专辑";
        }
    }
}

QString Music::getLrcFilePath() const
{
    QString path = musicUrl.toLocalFile();
    path.replace(".mp3", ".lrc");
    path.replace(".flac", ".lrc");
    path.replace(".mpga", ".lrc");

    return path;
}

/**
 * @brief 将音乐信息插入或更新到数据库
 * 检测音乐是否已存在，存在则更新状态，不存在则插入新记录
 */
void Music::insertMusicToDB()
{
    // 检测音乐是否已存在于数据库
    QSqlQuery query;
    query.prepare("SELECT EXISTS (SELECT 1 FROM MusicInfo WHERE musicId = ?)");
    query.addBindValue(musicId);
    
    if(!query.exec())
    {
        // 查询执行失败，可在此处添加错误日志
        return;
    }
    
    if(query.next())
    {
        bool isExists = query.value(0).toBool();
        
        if(isExists)
        {
            // 更新现有音乐的收藏和历史状态
            query.prepare("UPDATE MusicInfo SET isLike = ?, isHistory = ? WHERE musicId = ?");
            query.addBindValue(isLike ? 1 : 0);
            query.addBindValue(isHistory ? 1 : 0);
            query.addBindValue(musicId);
            
            if(!query.exec())
            {
                // 更新执行失败，可在此处添加错误日志
            }
        }
        else
        {
            // 插入新音乐记录
            query.prepare("INSERT INTO MusicInfo(musicId, musicName, musicSinger, albumName, musicUrl,\
                                                 duration, isLike, isHistory)\
                           VALUES(?,?,?,?,?,?,?,?)");
            query.addBindValue(musicId);
            query.addBindValue(musicName);
            query.addBindValue(singerName);
            query.addBindValue(albumName);
            query.addBindValue(musicUrl.toLocalFile());
            query.addBindValue(duration);
            query.addBindValue(isLike ? 1 : 0);
            query.addBindValue(isHistory ? 1 : 0);
            
            if(!query.exec())
            {
                qDebug()<<"插入失败: "<<query.lastError().text();
            }
            qDebug()<<"插入music信息: "<<musicName<<" "<<musicId;
        }
    }
}
