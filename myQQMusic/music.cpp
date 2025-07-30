#include "music.h"


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
    // 音乐唯一id
    musicId = QUuid::createUuid().toString();
    // 解析歌曲元数据
    // 读取url对应的歌曲文件的信息，解析出元数据
    // 歌曲名称、歌曲作者、歌曲专辑、歌曲持续时长
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
    // 读取歌曲数据
    QMediaPlayer player;
    player.setMedia(musicUrl); // 不会等待整个的加载过程

    // 解析元数据，等待，让主继续处理
    while(!player.isMetaDataAvailable())
    {
        // 保持主窗口继续活动
        QCoreApplication::processEvents();
    }

    // 解析完成，进行提取
    if(player.isMetaDataAvailable())
    {
        musicName = player.metaData("Title").toString();
        singerName = player.metaData("Author").toString();
        albumName = player.metaData("AlbumTitle").toString();
        duration = player.duration();

        QString fileName = musicUrl.fileName();
        int index = fileName.indexOf('-');

        // musicName为""的处
        if(musicName.isEmpty())
        {
            if(index != -1)
            {
                // 找到-的位置
                musicName = fileName.mid(0, index).trimmed(); // 去除字符串前后空白字符
            }
            else
            {
                // 找到.的位置
                musicName = fileName.mid(0, fileName.indexOf('.')).trimmed();
            }
        }

        // 作者为空
        if(singerName.isEmpty())
        {
            if(index != -1)
            {
                // 从-后开始，到.前的位吧置
                singerName = fileName.mid(index + 1, fileName.indexOf('.') - index - 1).trimmed();
            }
            else
            {
                singerName = "未知歌手";
            }
        }

        // 专辑名为空
        if(albumName.isEmpty())
        {
            albumName = "未知专辑";
        }

        qDebug() << musicName << "" << singerName << "" << albumName << "" << duration;
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
    // 1. 检测是否在数据库存在
    QSqlQuery query;
    query.prepare("SELECT EXISTS (SELECT 1 FROM MusicInfo WHERE musicId = ?)");
    query.addBindValue(musicId);
    if(!query.exec())
    {
        qDebug()<<"查询失败: "<<query.lastError().text();
        return;
    }
    if(query.next())
    {
        bool isExists = query.value(0).toBool();
        if(isExists) // 存在
        {
            // 存在的话就不需要插入music对象，只需要更新isLike和isHistory属性
            query.prepare("UPDATE MusicInfo SET isLike = ?, isHistory = ? WHERE musicId = ?");
            query.addBindValue(isLike ? 1 : 0);
            query.addBindValue(isHistory ? 1 : 0);
            query.addBindValue(musicId);
            if(!query.exec())
            {
                qDebug()<<"更新失败: "<<query.lastError().text();
            }
            qDebug()<<"更新music信息: "<<musicName<<" "<<musicId;
        }
        else // 不存在的话直接将music的所有属性插入到数据库
        {
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
