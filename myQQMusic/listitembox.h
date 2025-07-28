#ifndef LISTITEMBOX_H
#define LISTITEMBOX_H

#include <QWidget>

namespace Ui {
class ListItemBox;
}

/**
 * @brief The ListItemBox class
 * 音乐列表项自定义组件，用于在列表中显示单个音乐的信息
 * 包含音乐名称、歌手、专辑信息和喜欢按钮，支持鼠标悬停效果
 */
class ListItemBox : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief ListItemBox 构造函数
     * @param parent 父窗口指针
     */
    explicit ListItemBox(QWidget *parent = nullptr);

    /**
     * @brief ~ListItemBox 析构函数
     * 释放UI资源
     */
    ~ListItemBox();

    /**
     * @brief setMusicName 设置音乐名称
     * @param name 音乐名称字符串
     */
    void setMusicName(const QString& name);

    /**
     * @brief setSingerName 设置歌手名称
     * @param singer 歌手名称字符串
     */
    void setSingerName(const QString& singer);

    /**
     * @brief setAlbumName 设置专辑名称
     * @param albumName 专辑名称字符串
     */
    void setAlbumName(const QString& albumName);

    /**
     * @brief setLikeIcon 设置喜欢图标状态
     * @param like 是否喜欢该音乐
     */
    void setLikeIcon(bool like);

private slots:
    /**
     * @brief onLikeBtnClicked 喜欢按钮点击事件处理
     * 切换喜欢状态并更新UI
     */
    void onLikeBtnClicked();

signals:
    /**
     * @brief setIsLike 发送喜欢状态变更信号
     * @param isLike 新的喜欢状态
     */
    void setIsLike(bool isLike);

protected:
    /**
     * @brief enterEvent 鼠标进入事件
     * 实现悬停背景色效果
     * @param event 事件对象
     */
    void enterEvent(QEvent *event) override;

    /**
     * @brief leaveEvent 鼠标离开事件
     * 恢复背景色
     * @param event 事件对象
     */
    void leaveEvent(QEvent *event) override;

private:
    Ui::ListItemBox *ui;          ///< UI界面指针
    bool isLike;                  ///< 标记是否已收藏该音乐
};

#endif // LISTITEMBOX_H
