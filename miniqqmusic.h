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
#include <QSystemTrayIcon>
#include <QMenu>

#include "volumetool.h"
#include "musiclist.h"
#include "commonpage.h"
#include "lrcpage.h"


QT_BEGIN_NAMESPACE
namespace Ui { class miniQQMusic; }
QT_END_NAMESPACE

class miniQQMusic : public QWidget
{
    Q_OBJECT

public:
    miniQQMusic(QWidget *parent = nullptr);
    
    ~miniQQMusic();

    void InitUi();                  // 初始化界面
    void initSqlite();              // 初始化数据库
    void initMusicList();           // 初始化音乐列表
    void initPlayer();              // 初始化播放列表
    void setBtForm_IconTextPageId() const ; // 设置侧边栏的按钮
    void onBtFormClick(int pageid) ;
    void connectSignalAndSlot() const;
    QJsonArray RandPicutre();
    void onUpdateLikeMusic(bool isLike, const QString& musicId);
    void playAllOfCommonPage(CommonPage* page, int index);
    void playMusicByIndex(CommonPage* page, int index);
    void updateBtformAnimal();
    void quitQQMusic();
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void on_quit_clicked();
    void onPlayerError(QMediaPlayer::Error error);
    void on_volume_clicked();
    void setMusicSilence(bool isMuted);
    void on_addLocal_clicked();
    void onPlayClicked();
    void onPlayStateChanged();
    void onPlayUpCliked();
    void onPlayDownCliked();
    void onPlaybackModeClicked();
    void onPlaybackModeChanged(QMediaPlaylist::PlaybackMode playbackMode);
    void onPlayAll(PageType pagetype);
    void onCurrentIndexChanged(int index);
    void setPlayerVolume(int volume);
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 duration);
    void onMusicSliderChanged(float value);
    void onMetaDataAvailableChanged(bool available);
    void onLrcWordClicked();
    void on_min_clicked();
    void on_skin_clicked();
    void on_max_clicked();

private:
    Ui::miniQQMusic *ui;
    QPoint dragPosition;             // 窗口拖拽起始位置
    bool isDrag;                     // 是否正在拖拽窗口
    VolumeTool* volumeTool;          // 音量调节窗口
    MusicList musiclist;             // 音乐列表管理
    QMediaPlayer *player;            // 媒体播放器
    QMediaPlaylist *playList;        // 播放列表
    CommonPage* curPage;             // 当前显示页面
    int currentIndex;                // 当前播放索引
    qint64 totalDuration;            // 当前歌曲总时长(毫秒)
    LrcPage* lrcPage;                // 歌词显示窗口
    QPropertyAnimation* lrcAnimation;// 歌词窗口动画
    QSqlDatabase sqlite;             // 数据库连接
};
#endif // MYQQMUSIC_H
