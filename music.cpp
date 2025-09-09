#include "music.h"

#include <QTime>

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

void Music::parseMediaMetaData()
{
    // 创建媒体播放器实例用于提取元数据
    QMediaPlayer player;
    player.setMedia(musicUrl);

    // 等待元数据可用，添加超时机制
    int timeout = 3000; // 3秒超时
    QTime startTime = QTime::currentTime();
    while(!player.isMetaDataAvailable() && startTime.msecsTo(QTime::currentTime()) < timeout)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    // 检查是否发生错误
    if (player.error() != QMediaPlayer::NoError) {
        qDebug() << "媒体播放器错误: " << player.errorString();
        return;
    }

    // 提取元数据
    if(player.isMetaDataAvailable())
    {
        musicName = player.metaData("Title").toString();
        singerName = player.metaData("Author").toString();
        albumName = player.metaData("AlbumTitle").toString();
        duration = player.duration();

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

void Music::insertMusicToDB()
{
    // 检测音乐是否已存在于数据库
    QSqlQuery query;
    query.prepare("SELECT EXISTS (SELECT 1 FROM MusicInfo WHERE musicId = ?)");
    query.addBindValue(musicId);
    
    if(!query.exec()) // 查询失败
        return;
    
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
            
            if(!query.exec()) // 更新失败
            {
                qDebug()<<"更新现有音乐失败: "<<query.lastError().text();
                return;
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
            qDebug()<<"插入music信息: " << musicName << " " << musicId;
        }
    }
}
