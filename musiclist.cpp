#include "musiclist.h"


MusicList::MusicList()
{
}

void MusicList::addMusicByUrl(const QList<QUrl> &urls)
{
    for(auto& musicUrl: urls)
    {
        QString musicPath = musicUrl.toLocalFile();

        // 如果存在就不添加了
        if(musicPaths.contains(musicPath))
            continue;

        // 不存在的话就添加到歌曲列表
        musicPaths.insert(musicPath);

        // 筛选文件
        QMimeDatabase db;
        QMimeType mime = db.mimeTypeForFile(musicPath); // url-->字符串

        //                      mp3                            无损音乐                        wav
        if(mime.name() == "audio/mpeg" || mime.name() == "audio/flac" || mime.name() == "audio/wav")
        {
            // 构造一个music文件，然后进行管理
            Music music(musicUrl);
            musicList.push_back(music);
        }
    }
}

MusicList::iterator MusicList::begin()
{
    return musicList.begin();
}

MusicList::iterator MusicList::end()
{
    return musicList.end();
}

MusicList::iterator MusicList::findMusicByMusicid(const QString &musicId)
{
    for(iterator it = begin(); it!= end(); ++it)
    {
        if(it->getMusicId() == musicId)
        {
            return it;
        }
    }
    return end();
}

void MusicList::writeToDB()
{
    for(auto &music : musicList)
    {
        music.insertMusicToDB();
    }
}

void MusicList::readFromDB()
{
    QString sql("SELECT musicId, musicName, musicSinger, albumName,\
                duration, musicUrl, isLike, isHistory\
                FROM musicInfo");
    QSqlQuery query;
    if(!query.exec(sql))
        return;
    while(query.next())
    {
        Music music;
        music.setMusicId(query.value(0).toString());
        music.setMusicName(query.value(1).toString());
        music.setSingerName(query.value(2).toString());
        music.setAlbumName(query.value(3).toString());
        music.setDuration(query.value(4).toLongLong());
        music.setMusicUrl("file:///" + query.value(5).toString());
        music.setIsLike(query.value(6).toBool());
        music.setIsHistory(query.value(7).toBool());
        musicList.push_back(music);

        // 将路径添加到musicPaths
        musicPaths.insert(music.getMusicUrl().toLocalFile());
    }
}
