#ifndef COMMONPAGE_H
#define COMMONPAGE_H

#include <QWidget>
#include "listitembox.h"
#include "musiclist.h"
#include "listitembox.h"

namespace Ui {
class CommonPage;
}


// 区分不同page页面
enum PageType
{
    LIKE_PAGE,    // 我喜欢页面
    LOCAL_PAGE,   // 本地下载页面
    HISTORY_PAGE   // 最近播放页面
};


class CommonPage : public QWidget
{
    Q_OBJECT

public:
    explicit CommonPage(QWidget *parent = nullptr);
    ~CommonPage();

    // 设置page属性
    void setMusicListType(PageType pagetype);

    // 添加
    void reFresh(MusicList& musiclist);

    void setCommonPageUi(const QString& title, const QString& imagePath);

private:
    // 添加音乐到音乐页面
    void addMusicToMusicPage(MusicList& musiclist);


private:
    // 具体某个⻚⾯的⾳乐，只需要存储⾳乐的id
    QVector<QString> musicListOfPage;

    // 标记属于likePage、localPage、recentPage哪个⻚⾯
    PageType pageType;

private:
    Ui::CommonPage *ui;
};

#endif // COMMONPAGE_H
