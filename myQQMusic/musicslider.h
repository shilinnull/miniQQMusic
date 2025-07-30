#ifndef MUSICSLIDER_H
#define MUSICSLIDER_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>

namespace Ui {
class MusicSlider;
}

/**
 * @brief The MusicSlider class
 * 音乐滑块组件，用于音乐进度或音量控制
 * 支持鼠标拖动和点击操作，提供位置反馈信号
 */
class MusicSlider : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief MusicSlider 构造函数
     * 初始化滑块组件，设置初始位置和最大宽度
     * @param parent 父窗口指针
     */
    explicit MusicSlider(QWidget *parent = nullptr);

    /**
     * @brief ~MusicSlider 析构函数
     * 释放UI资源
     */
    ~MusicSlider();

    /**
     * @brief moveSilder 更新滑块位置
     * 根据当前位置更新滑块UI显示
     */
    void moveSilder();

    /**
     * @brief setStep 设置滑块位置比例
     * 根据比例值计算并更新滑块位置
     * @param bf 位置比例（0.0-1.0）
     */
    void setStep(float bf);

signals:
    /**
     * @brief setMusicSliderPosition 发送滑块位置信号
     * 当滑块位置改变时发射，提供归一化的位置值
     * @param position 滑块位置（0.0-1.0）
     */
    void setMusicSliderPosition(float position);

protected:
    /**
     * @brief mousePressEvent 鼠标按下事件
     * 处理鼠标点击滑块的位置设置
     * @param event 鼠标事件对象
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief mouseMoveEvent 鼠标移动事件
     * 处理鼠标拖动滑块的位置更新
     * @param event 鼠标事件对象
     */
    void mouseMoveEvent(QMouseEvent *event) override;

    /**
     * @brief mouseReleaseEvent 鼠标释放事件
     * 处理鼠标释放时的位置确认和信号发射
     * @param event 鼠标事件对象
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::MusicSlider *ui;          ///< UI界面指针
    int currentPos;               ///< 当前滑块位置（像素）
    int maxWidth;                 ///< 滑块最大宽度（像素）
};

#endif // MUSICSLIDER_H
