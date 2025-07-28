#include "musiclist.h"


MusicList::MusicList()
{

}

/*! \brief 通过URL列表添加音乐到列表
 \param urls 音乐文件URL的列表
 \details 检查文件格式是否支持，避免重复添加，并从URL解析元数据创建Music对象 */
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

/*! \brief 返回音乐列表的起始迭代器
 \return 指向列表第一个元素的迭代器 */
MusicList::iterator MusicList::begin()
{
    return musicList.begin();
}

/*! \brief 返回音乐列表的结束迭代器
 \return 指向列表最后一个元素之后位置的迭代器 */
MusicList::iterator MusicList::end()
{
    return musicList.end();
}

/*! \brief 通过音乐ID查找音乐迭代器
 \param musicId 要查找的音乐ID
 \return 找到的音乐项迭代器，若未找到则返回end() */
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

/*! \brief 将音乐列表写入数据库
 \details 遍历音乐列表，对每个音乐项调用insertMusicToDB方法保存到数据库 */
void MusicList::writeToDB()
{
    for(auto music : musicList)
    {
        music.insertMusicToDB();
    }
}

/*! \brief 从数据库读取音乐列表
 \details 执行SQL查询获取所有音乐记录，重建音乐列表并恢复元数据 */
void MusicList::readFromDB()
{
    QString sql("SELECT musicId, musicName, musicSinger, albumName,\
                duration, musicUrl, isLike, isHistory\
                FROM musicInfo");
    QSqlQuery query;
    if(!query.exec(sql))
    {
        return;
    }
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
