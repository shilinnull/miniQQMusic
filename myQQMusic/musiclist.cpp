#include "musiclist.h"


MusicList::MusicList()
{

}

void MusicList::addMusicByUrl(const QList<QUrl> &urls)
{
    for(auto musicUrl: urls)
    {
        // 筛选文件
        QMimeDatabase db;
        QMimeType mime = db.mimeTypeForFile(musicUrl.toLocalFile());
        if(mime.name() == "audio/mpeg" || mime.name() == "audio/flac" || mime.name() == "audio/wav")
        {
            // 构造一个music文件，然后进行管理
            Music music(musicUrl);
            musicList.push_back(music);
        }
    }
}
