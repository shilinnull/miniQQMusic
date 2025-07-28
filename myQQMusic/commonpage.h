#ifndef COMMONPAGE_H
#define COMMONPAGE_H

#include <QWidget>
#include <qmediaplaylist.h>
#include "listitembox.h"
#include "musiclist.h"

namespace Ui {
class CommonPage;
}

/**
 * @brief 页面类型枚举
 * 区分不同的音乐列表页面
 */
enum PageType
{
    LIKE_PAGE,    // 我喜欢页面
    LOCAL_PAGE,   // 本地下载页面
    HISTORY_PAGE  // 最近播放页面
};

/**
 * @brief 通用音乐列表页面类
 * 用于展示不同类型的音乐列表，如喜欢、本地下载和最近播放页面
 */
class CommonPage : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     */
    explicit CommonPage(QWidget *parent = nullptr);
    /**
     * @brief 析构函数
     */
    ~CommonPage();

    /**
     * @brief 设置页面音乐列表类型
     * @param pagetype 页面类型枚举值
     */
    void setMusicListType(PageType pagetype);

    /**
     * @brief 设置封面图
     * @param pixmap 封面图片
     */
    void setMusicImage(QPixmap pixmap);

    /**
     * @brief 刷新音乐列表
     * @param musiclist 音乐列表数据
     */
    void reFresh(MusicList& musiclist);

    /**
     * @brief 设置页面UI元素
     * @param title 页面标题
     * @param imagePath 封面图片路径
     */
    void setCommonPageUi(const QString& title, const QString& imagePath);

    /**
     * @brief 添加音乐到播放器列表
     * @param musiclist 音乐列表数据
     * @param playList 媒体播放列表指针
     */
    void addMusictoPlayer(MusicList &musiclist, QMediaPlaylist *playList);

    /**
     * @brief 通过索引获取音乐ID
     * @param index 音乐索引
     * @return 音乐ID字符串
     */
    QString getMisicIdByIndex(int index) const;


signals:
    /**
     * @brief 更新喜欢音乐状态信号
     * @param isLike 是否喜欢
     * @param musicId 音乐ID
     */
    void updataLikeMusic(bool isLike, const QString& musicId);
    /**
     * @brief 播放全部按钮信号
     * @param pagetype 页面类型
     */
    void playAll(PageType pagetype);
    /**
     * @brief 通过索引播放音乐信号
     * @param page 当前页面指针
     * @param index 音乐索引
     */
    void playMusicByIndex(CommonPage*, int);

private:
    Ui::CommonPage *ui;               // UI对象指针
    QVector<QString> musicListOfPage; // 页面音乐ID列表
    PageType pageType;                // 页面类型标记

    /**
     * @brief 添加音乐到页面显示
     * @param musiclist 音乐列表数据
     */
    void addMusicToMusicPage(MusicList& musiclist);
};

#endif // COMMONPAGE_H
