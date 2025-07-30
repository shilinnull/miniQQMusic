#ifndef BTFORM_H
#define BTFORM_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QMouseEvent>

namespace Ui {
class BtForm;
}

/**
 * @brief 自定义按钮组件，用于页面导航切换
 * 支持图标、文本显示，点击动画效果和状态切换
 */
class BtForm : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     */
    explicit BtForm(QWidget *parent = nullptr);
    
    /**
     * @brief 析构函数
     */
    ~BtForm();

    /**
     * @brief 设置按钮图标、文本和页面ID
     * @param btIcon 图标路径
     * @param text 显示文本
     * @param pageid 关联的页面ID
     */
    void setIconTextId(const QString& btIcon, const QString& text, int pageid);
    
    /**
     * @brief 获取当前按钮关联的页面ID
     * @return 页面ID
     */
    int getId();
    
    /**
     * @brief 清除按钮背景样式，恢复默认状态
     */
    void clearBg();

    /**
     * @brief 设置线条动画效果
     */
    void setline1Animal();
    
    /**
     * @brief 显示或隐藏动画效果
     * @param isShow 是否显示动画
     */
    void showAnimal(bool isShow);

signals:
    /**
     * @brief 按钮点击信号
     * @param id 关联的页面ID
     */
    void click(int id);

protected:
    /**
     * @brief 重写鼠标点击事件
     * @param event 鼠标事件对象
     */
    virtual void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::BtForm *ui;               // UI对象指针
    int pageId = 0;               // 关联的页面ID
    QPropertyAnimation *animationLine1; // 线条动画1
    QPropertyAnimation *animationLine2; // 线条动画2
    QPropertyAnimation *animationLine3; // 线条动画3
    QPropertyAnimation *animationLine4; // 线条动画4
};

#endif // BTFORM_H
