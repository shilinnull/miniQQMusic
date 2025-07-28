#ifndef VOLUMETOOL_H
#define VOLUMETOOL_H

#include <QWidget>

namespace Ui {
class VolumeTool;
}

/**
 * @brief The VolumeTool class
 * 音量控制工具组件，提供音量调节滑块和静音功能
 * 支持鼠标拖动调节音量，具有自定义外观和阴影效果
 */
class VolumeTool : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief VolumeTool 构造函数
     * 初始化音量控制组件，设置默认音量和静音状态
     * @param parent 父窗口指针
     */
    explicit VolumeTool(QWidget *parent = nullptr);

    /**
     * @brief ~VolumeTool 析构函数
     * 释放UI资源
     */
    ~VolumeTool();

    /**
     * @brief onSilenceBtnClicked 静音按钮点击事件处理
     * 切换静音状态并更新UI显示
     */
    void onSilenceBtnClicked();

    /**
     * @brief setVolume 更新音量滑块位置
     * 根据鼠标位置计算音量比例并更新UI
     */
    void setVolume();

signals:
    /**
     * @brief setSilence 发送静音状态变更信号
     * @param muted 是否静音
     */
    void setSilence(bool muted);

    /**
     * @brief setMusicVolume 发送音量大小变更信号
     * @param ratio 音量比例（0-100）
     */
    void setMusicVolume(int ratio);

protected:
    /**
     * @brief paintEvent 绘制事件
     * 自定义绘制组件外观，包括三角形指示器
     * @param event 绘制事件对象
     */
    void paintEvent(QPaintEvent* event) override;

    /**
     * @brief eventFilter 事件过滤器
     * 处理音量调节区域的鼠标事件（按下、移动、释放）
     * @param object 被监视对象
     * @param event 事件对象
     * @return 是否处理事件
     */
    bool eventFilter(QObject* object, QEvent* event) override;

private:
    Ui::VolumeTool *ui;          ///< UI界面指针
    bool isMuted;                ///< 静音状态标志
    int volumeRatio;             ///< 音量比例（0-100）
};

#endif // VOLUMETOOL_H
