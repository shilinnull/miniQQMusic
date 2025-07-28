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
namespace Ui { class myQQMusic; }
QT_END_NAMESPACE

/**
 * @brief 主窗口类，QQ音乐播放器的核心界面和逻辑控制器
 * 管理整体UI布局、媒体播放、页面切换和数据库交互
 */
class myQQMusic : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     */
    myQQMusic(QWidget *parent = nullptr);
    
    /**
     * @brief 析构函数
     */
    ~myQQMusic();

    /**
     * @brief 初始化用户界面
     * 设置窗口样式、阴影效果、托盘图标和各页面初始状态
     */
    void InitUi();

    /**
     * @brief 初始化媒体播放器
     * 创建QMediaPlayer和QMediaPlaylist实例，设置默认播放参数
     */
    void initPlayer();

    /**
     * @brief 初始化SQLite数据库
     * 创建数据库连接并初始化musicInfo表
     */
    void initSqlite();

    /**
     * @brief 初始化音乐列表
     * 从数据库加载音乐信息到内存
     */
    void initMusicList();

    /**
     * @brief 设置左侧导航按钮的图标、文本和页面ID
     */
    void setBtForm_IconTextPageId() const ;

    /**
     * @brief 导航按钮点击事件处理
     * @param pageid 目标页面ID
     */
    void onBtFormClick(int pageid) ;

    /**
     * @brief 连接所有信号与槽
     * 建立UI元素与业务逻辑之间的交互
     */
    void connectSignalAndSlot() const;

    /**
     * @brief 生成随机推荐图片数据
     * @return 包含随机图片信息的JSON数组
     */
    QJsonArray RandPicutre();

    /**
     * @brief 响应收藏状态变更
     * @param isLike 是否收藏
     * @param musicId 音乐ID
     */
    void onUpdateLikeMusic(bool isLike, const QString& musicId);

    /**
     * @brief 播放当前页面所有歌曲
     * @param page 当前页面指针
     * @param index 起始播放索引
     */
    void playAllOfCommonPage(CommonPage* page, int index);

    /**
     * @brief 通过索引播放音乐
     * @param page 当前页面指针
     * @param index 音乐索引
     */
    void playMusicByIndex(CommonPage* page, int index);

    /**
     * @brief 更新导航按钮动画状态
     * 根据当前选中页面切换按钮动画效果
     */
    void updateBtformAnimal();

    /**
     * @brief 退出应用程序
     * 清理资源并关闭主窗口
     */
    void quitQQMusic();

protected:
    /**
     * @brief 重写鼠标按下事件
     * 实现窗口拖拽功能
     * @param event 鼠标事件对象
     */
    void mousePressEvent(QMouseEvent* event) override;
    
    /**
     * @brief 重写鼠标移动事件
     * 实现窗口拖拽功能
     * @param event 鼠标事件对象
     */
    void mouseMoveEvent(QMouseEvent* event) override;

private slots:
    /**
     * @brief 退出按钮点击事件
     */
    void on_quit_clicked();

    /**
     * @brief 音量按钮点击事件
     */
    void on_volume_clicked();
    
    /**
     * @brief 设置静音状态
     * @param isMuted 是否静音
     */
    void setMusicSilence(bool isMuted);

    /**
     * @brief 添加本地音乐按钮点击事件
     */
    void on_addLocal_clicked();

    /**
     * @brief 最小化按钮点击事件
     */
    void on_min_clicked();

    /**
     * @brief 播放/暂停按钮点击事件
     */
    void onPlayClicked();
    
    /**
     * @brief 播放状态变化处理
     */
    void onPlayStateChanged();
    
    /**
     * @brief 上一曲按钮点击事件
     */
    void onPlayUpCliked();
    
    /**
     * @brief 下一曲按钮点击事件
     */
    void onPlayDownCliked();
    
    /**
     * @brief 播放模式按钮点击事件
     */
    void onPlaybackModeClicked();
    
    /**
     * @brief 播放模式变化时更新图标
     * @param playbackMode 新的播放模式
     */
    void onPlaybackModeChanged(QMediaPlaylist::PlaybackMode playbackMode);

    /**
     * @brief 播放全部按钮点击事件
     * @param pagetype 页面类型
     */
    void onPlayAll(PageType pagetype);

    /**
     * @brief 当前播放索引变化事件
     * 更新历史播放记录
     * @param index 新的播放索引
     */
    void onCurrentIndexChanged(int index);
    
    /**
     * @brief 设置播放器音量
     * @param volume 音量值(0-100)
     */
    void setPlayerVolume(int volume);
    
    /**
     * @brief 媒体总时长变化事件
     * @param duration 总时长(毫秒)
     */
    void onDurationChanged(qint64 duration);
    
    /**
     * @brief 播放位置变化事件
     * 更新进度条显示
     * @param duration 当前播放位置(毫秒)
     */
    void onPositionChanged(qint64 duration);
    
    /**
     * @brief 进度条拖动事件
     * @param value 拖动位置(0-1)
     */
    void onMusicSliderChanged(float value);
    
    /**
     * @brief 媒体元数据可用状态变化事件
     * @param available 是否可用
     */
    void onMetaDataAvailableChanged(bool available);
    
    /**
     * @brief 歌词显示按钮点击事件
     */
    void onLrcWordClicked();
    
    /**
     * @brief 皮肤按钮点击事件
     */
    void on_skin_clicked();

private:
    Ui::myQQMusic *ui;               // UI对象指针
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
