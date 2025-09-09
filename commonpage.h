#ifndef COMMONPAGE_H
#define COMMONPAGE_H

#include <QWidget>
#include <qmediaplaylist.h>
#include <QDebug>
#include <QPixmap>

#include "listitembox.h"
#include "musiclist.h"

namespace Ui {
class CommonPage;
}

enum PageType
{
    LIKE_PAGE,    // 我喜欢页面
    LOCAL_PAGE,   // 本地下载页面
    HISTORY_PAGE  // 最近播放页面
};

class CommonPage : public QWidget
{
    Q_OBJECT

public:

    explicit CommonPage(QWidget *parent = nullptr);

    ~CommonPage();

    void setMusicListType(PageType pagetype);

    void setMusicImage(QPixmap pixmap);
    void reFresh(MusicList& musiclist);
    void setCommonPageUi(const QString& title, const QString& imagePath);
    void addMusictoPlayer(MusicList &musiclist, QMediaPlaylist *playList);
    QString getMisicIdByIndex(int index) const;

signals:
    void updataLikeMusic(bool isLike, const QString& musicId);
    void playAll(PageType pagetype);
    void playMusicByIndex(CommonPage*, int);

private:
    void addMusicToMusicPage(MusicList& musiclist);

private:
    Ui::CommonPage *ui;               // UI对象指针
    QVector<QString> musicListOfPage; // 页面音乐ID列表
    PageType pageType;                // 页面类型标记
};

#endif // COMMONPAGE_H
