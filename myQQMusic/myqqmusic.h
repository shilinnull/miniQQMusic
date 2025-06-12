#ifndef MYQQMUSIC_H
#define MYQQMUSIC_H

#include <QWidget>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QJsonArray>
#include <QJsonObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileDialog>
#include <QPixmap>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSystemTrayIcon>
#include <QMenu>

#include "volumetool.h"
#include "musiclist.h"
#include "commonpage.h"
#include "lrcpage.h"


QT_BEGIN_NAMESPACE
namespace Ui { class myQQMusic; }
QT_END_NAMESPACE

class myQQMusic : public QWidget
{
    Q_OBJECT

public:
    myQQMusic(QWidget *parent = nullptr);
    ~myQQMusic();

    // 初始化UI
    void InitUi();

    // 初始化媒体对象
    void initPlayer();

    // 初始化数据库
    void initSqlite();

    // 初始化musicList
    void initMusicList();

    // 初始化bodyLeft中6个btForm的信息
    void setBtForm_IconTextPageId() const ;

    // btForm点击槽函数
    void onBtFormClick(int pageid) ;

    // 处理信号槽函数
    void connectSignalAndSlot() const;

    // 随机图片
    QJsonArray RandPicutre();

    // 响应commonPage的信号
    void onUpdateLikeMusic(bool isLike, const QString& musicId);

    // 播放当前页面所有歌曲
    void playAllOfCommonPage(CommonPage* page, int index);

    // 通过下标播放音乐
    void playMusicByIndex(CommonPage* page, int index);

    // 更新btForm动画
    void updateBtformAnimal();

    // 退出QQMusic
    void quitQQMusic();

protected:
    // 重写QWidget类的⿏标单击和⿏标滚轮事件
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private slots:
    void on_quit_clicked();

    void on_volume_clicked();
    // 设置是否静音
    void setMusicSilence(bool isMuted);

    void on_addLocal_clicked();

    void on_min_clicked();

    // 播放控制
    void onPlayClicked();
    // 播放状态发⽣改变
    void onPlayStateChanged();
    // 上一曲
    void onPlayUpCliked();
    // 下一曲
    void onPlayDownCliked();
    // 播放模式设置
    void onPlaybackModeClicked();
    // 播放模式的图片切换
    void onPlaybackModeChanged(QMediaPlaylist::PlaybackMode playbackMode);

    // 播放所有按钮
    void onPlayAll(PageType pagetype);

    // 当前下标被更换，播放列表项发⽣改变，此时将播放⾳乐收藏到历史记录中
    void onCurrentIndexChanged(int index);
    // 设置音量大小
    void setPlayerVolume(int volume);
    // 设置播放媒体的总时⻓
    void onDurationChanged(qint64 duration);
    // 设置当前播放时长
    void onPositionChanged(qint64 duration);
    // 进度条变化
    void onMusicSliderChanged(float value);
    // 歌曲数据发生变化
    void onMetaDataAvailableChanged(bool available);
    // 歌词显示
    void onLrcWordClicked();
    void on_skin_clicked();

private:
    Ui::myQQMusic *ui;

    // 记录光标相对于窗口标题栏的相对距离
    QPoint dragPosition;

    // 窗口拖拽
    bool isDrag;

    // 添加音量弹出按钮
    VolumeTool* volumeTool;

    // 管理音乐
    MusicList musiclist;

    //////////////////////////////////////////////////////
    // 播放器相关
    QMediaPlayer *player;
    // 媒体列表
    QMediaPlaylist *playList;
    // 当前页面
    CommonPage* curPage;
    int currentIndex;

    // 当前歌曲总时长
    qint64 totalDuration;

    // 歌词
    LrcPage* lrcPage;
    // 点击歌词弹出动画
    QPropertyAnimation* lrcAnimation;

    // 数据库文件
    QSqlDatabase sqlite;

};
#endif // MYQQMUSIC_H
